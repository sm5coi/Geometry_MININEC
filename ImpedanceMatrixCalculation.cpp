#include "ImpedanceMatrixCalculation.hpp"
#include "ImpedanceMatrixFactorization.hpp"
#include "Beta_247_315.hpp"
#include "MatSolve.hpp"
//#include "SourceData.hpp"
#include <cmath>
#include <iostream>

void ImpedanceMatrixCalculation(SimulationState& S, GeometryData g)
{
    // init real & imag Z parts
    S.ZR.assign(g.N+1, std::vector<double>(g.N+1, 0.0));
    S.ZI.assign(g.N+1, std::vector<double>(g.N+1, 0.0));

    // =========================
    // MAIN IMPEDANCE CALC LOOP
    // =========================

    // REM ----- COMPUTE ROW I OF MATRIX (OBSERVATION LOOP)
    for (S.I = 1; S.I <= g.N; ++S.I)                        // 211
    {
        int I1 = std::abs(g.Cp[S.I][1]);                    // 212
        int I2 = std::abs(g.Cp[S.I][2]);                    // 213

        double F4i = std::copysign(g.Sa[I1], g.Cp[S.I][1]);     // 214
        double F5i = std::copysign(g.Sa[I1], g.Cp[S.I][2]);     // 215

        // if (I1 > 0)
        //     F4 = std::copysign(g.Sa[I1], g.Cp[S.I][1]);

        // if (I2 > 0)
        //     F5 = std::copysign(g.Sa[I2], g.Cp[S.I][2]);

        //double T5 = 0, T6 = 0, T7 = 0;

        // 216 REM ----- R(M + 1/2) - R(M - 1/2) HAS COMPONENTS (T5,T6,T7)
        double T5 = F4i * g.CABG[I1][1] + F5i * g.CABG[I2][1];    // 217
        double T6 = F4i * g.CABG[I1][2] + F5i * g.CABG[I2][2];    // 218
        double T7 = F4i * g.CABG[I1][3] + F5i * g.CABG[I2][3];    // 219

        // if (I1 > 0) {
        //     T5 += F4 * g.CABG[I1][1];
        //     T6 += F4 * g.CABG[I1][2];
        //     T7 += F4 * g.CABG[I1][3];
        // }
        // if (I2 > 0) {
        //     T5 += F5 * g.CABG[I2][1];
        //     T6 += F5 * g.CABG[I2][2];
        //     T7 += F5 * g.CABG[I2][3];
        // }


        if (g.Cp[S.I][1] == -g.Cp[S.I][2])
        {
            T7 = g.Sa[I1] * (g.CABG[I1][3] + g.CABG[I2][3]);
        }

        // =========================
        // COLUMN loop
        // =========================

        // 221 REM ----- COMPUTE COLUMN J OF ROW I (SOURCE LOOP)
        for (S.J = 1; S.J <= g.N; ++S.J)
        {
            int J1 = std::abs(g.Cp[S.J][1]);            // 223
            int J2 = std::abs(g.Cp[S.J][2]);            // 224
            S.F4 = (int) copysign(1, g.Cp[S.J][1]);   // 225
            S.F5 = (int) copysign(1, g.Cp[S.J][2]);   // 226
            S.F6 = 1;                                 // 227
            S.F7 = 1;                                 // 228

            //bool J1_ground = (J1 == 0);
            //bool J2_ground = (J2 == 0);
            //int G = S.G;

            // K loop (image theory)

            // 229 REM ----- IMAGE LOOP
            for (S.K = 1; S.K >= S.G; S.K -= 2)         // 230
            {
                if (!(g.Cp[S.J][1] != -g.Cp[S.J][2]))   // 231
                {
                    if (S.K < 0) continue;              // 232
                    S.F6 = S.F4;                            // 233
                    S.F7 = S.F5;                            // 234
                }
                S.F8 = 0;                             // 235
                if (S.K < 0)                            // 236
                {
                    // COMPUTE PSI AND GRADIENT OF SCALAR POTENTIAL CONTRIBUTION
                    Beta_247_315(S, g, J1, J2, T5, T6, T7); // 247 - 315
                }
                else {
                    // REM ----- SET FLAG TO AVOID REDUNANT CALCULATIONS
                    bool L238 = (I1 != I2);
                    bool L239 = ((g.CABG[I1][1] + g.CABG[I1][2]) == 0);
                    bool L240 = (g.Cp[S.I][1] != g.Cp[S.I][2]);
                    bool L241 = (J1 != J2);
                    bool L242 = ((g.CABG[J1][1] + g.CABG[J1][2]) == 0);
                    bool L243 = (g.Cp[S.J][1] != g.Cp[S.J][2]);

                    //  Tested with http://electronics-course.com/boolean-algebra
                    if ((L239 || !L240) && (L242 || !L243) && !L238 && !L241 )
                    {
                        if (I1 == J1) S.F8 = 1;                                   // 244
                        if (S.I == S.J) S.F8 = 2;                                 // 245
                    }

                    if (S.ZR[S.I][S.J] == 0)                                    // 246
                    {
                        // COMPUTE PSI AND GRADIENT OF SCALAR POTENTIAL CONTRIBUTION
                        Beta_247_315(S, g, J1, J2, T5, T6, T7); // 247 - 315
                    }
                }
                // 316 REM ----- AVOID REDUNANT CALCULATIONS

                if (S.J < S.I) continue;            // 317
                if (S.F8 == 0) continue;              // 318
                S.ZR[S.J][S.I] = S.ZR[S.I][S.J];    // 319
                S.ZI[S.J][S.I] = S.ZI[S.I][S.J];    // 320

                // 321 REM ----- SEGMENTS ON SAME WIRE SAME DISTANCE APART HAVE SAME Z
                int P1 = S.J + 1;                   // 322
                if (P1 > g.N) continue;             // 323
                if (g.Cp[P1][1] != g.Cp[P1][2]) continue;   // 324
                if (!(g.Cp[P1][2] == g.Cp[S.J][2]))         // 325
                {
                    if (g.Cp[P1][2] != -g.Cp[S.J][2]) continue;         // 326
                    if ((g.CABG[J2][1] + g.CABG[J2][2]) != 0) continue; // 327
                }
                int P2 = S.I + 1;               // 328
                if (P2 > g.N) continue;         // 329
                S.ZR[P2][P1] = S.ZR[S.I][S.J];  // 330
                S.ZI[P2][P1] = S.ZI[S.I][S.J];  // 331
             } // Next K                        // 332
        } // Next J                             // 333
    } // Next I                                 // 336


    // AdditionOfLoads()

    ImpedanceMatrixFactorization(S, g);

    MatSolve(S,g);

    // SourceData()


    // // 337 REM ----- END MATRIX FILL TIME CALCULATION
    // // ===================================
    // // flatten ZR, ZI -> complex Z
    // // ===================================
    // S.Z.assign((g.N+1)*(g.N+1), std::complex<double>(0, 0));

    // for (int i = 1; i <= g.N; ++i)
    // {
    //     for (int j = 1; j <= g.N; ++j)
    //     {
    //         S.Z[i * g.N + j] = std::complex<double>(S.ZR[i][j], S.ZI[i][j]);
    //     }
    // }

    // // // ===================================
    // // // solve Z * I = V
    // // // ===================================

    // // // std::vector<std::vector<std::complex<double>>> Zm(N, std::vector<std::complex<double>>(N));
    // // // for (int i=0; i<N; i++)
    // // //     for (int j=0; j<N; j++)
    // // //         Zm[i][j] = S.Zat(i,j);

    // // // S.CurrX = MatSolve(S.Z, S.b);




    // // // ===================================
    // // // source excitation & normalization
    // // // ===================================

    // // //SourceData(S, S.CurrX);

    // // SourceData(S);
    // // S.CurrX = MatSolve(S.Z_matrix, S.b);

    // // build 2D impedance matrix
    // std::vector<std::vector<std::complex<double>>> Zmat(g.N+1, std::vector<std::complex<double>>(g.N+1));

    // for (int i = 0; i < g.N; ++i)
    //     for (int j = 0; j < g.N; ++j)
    //         Zmat[i][j] = S.Z[i * g.N + j];

    // // build excitation (b)
    // //SourceData(S);

    // // solve currents
    // //S.CurrX = MatSolve(Zmat, S.b);

    std::cout << "Size of S.CurrX: " << S.CurrX.size() << "\n";


}
