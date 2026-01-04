#include "ImpedanceMatrixCalculation.hpp"
//#include "Gosub102.hpp"
#include "Beta_247_315.hpp"
//#include "MatSolve.hpp"
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
    for (S.I = 1; S.I <= g.N; ++S.I)                            // 211
    {
        int I1 = std::abs(g.Cp[S.I][1]);                     // 212
        int I2 = std::abs(g.Cp[S.I][2]);                     // 213

        double F4 = 0.0;
        double F5 = 0.0;

        if (I1 > 0)
            F4 = std::copysign(g.Sa[I1], g.Cp[S.I][1]);

        if (I2 > 0)
            F5 = std::copysign(g.Sa[I2], g.Cp[S.I][2]);

        double T5 = 0, T6 = 0, T7 = 0;

        if (I1 > 0) {
            T5 += F4 * g.CABG[I1][1];
            T6 += F4 * g.CABG[I1][2];
            T7 += F4 * g.CABG[I1][3];
        }
        if (I2 > 0) {
            T5 += F5 * g.CABG[I2][1];
            T6 += F5 * g.CABG[I2][2];
            T7 += F5 * g.CABG[I2][3];
        }


        if (g.Cp[S.I][1] == -g.Cp[S.I][2])
        {
            T7 = g.Sa[I1] * (g.CABG[I1][3] + g.CABG[I2 - 1][3]);
        }

        // =========================
        // COLUMN loop
        // =========================
        for (S.J = 1; S.J <= g.N; ++S.J)
        {
            int J1 = std::abs(g.Cp[S.J][1]);
            int J2 = std::abs(g.Cp[S.J][2]);

            bool J1_ground = (J1 == 0);
            bool J2_ground = (J2 == 0);


            int G = S.G;

            // K loop (image theory)
            for (S.K = 1; S.K >= G; S.K -= 2)
            {
                Beta_247_315(S, g, J1, J2, T5, T6, T7);
            }
        }
    }

    // ===================================
    // flatten ZR, ZI -> complex Z
    // ===================================
    S.Z.assign((g.N+1)*(g.N+1), std::complex<double>(0, 0));

    for (int i = 1; i <= g.N; ++i)
    {
        for (int j = 1; j <= g.N; ++j)
        {
            S.Z[i * g.N + j] = std::complex<double>(S.ZR[i][j], S.ZI[i][j]);
        }
    }

    // // ===================================
    // // solve Z * I = V
    // // ===================================

    // // std::vector<std::vector<std::complex<double>>> Zm(N, std::vector<std::complex<double>>(N));
    // // for (int i=0; i<N; i++)
    // //     for (int j=0; j<N; j++)
    // //         Zm[i][j] = S.Zat(i,j);

    // // S.CurrX = MatSolve(S.Z, S.b);




    // // ===================================
    // // source excitation & normalization
    // // ===================================

    // //SourceData(S, S.CurrX);

    // SourceData(S);
    // S.CurrX = MatSolve(S.Z_matrix, S.b);

    // build 2D impedance matrix
    std::vector<std::vector<std::complex<double>>> Zmat(g.N+1, std::vector<std::complex<double>>(g.N+1));

    for (int i = 0; i < g.N; ++i)
        for (int j = 0; j < g.N; ++j)
            Zmat[i][j] = S.Z[i * g.N + j];

    // build excitation (b)
    //SourceData(S);

    // solve currents
    //S.CurrX = MatSolve(Zmat, S.b);

    std::cout << "Size of S.CurrX: " << S.CurrX.size() << "\n";


}
