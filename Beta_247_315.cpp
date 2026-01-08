#include "Beta_247_315.hpp"
#include "Gosub102.hpp"
#include "Sub_273_312.hpp"
#include <cmath>

void Beta_247_315(
    SimulationState& S,
    GeometryData g,
    int J1,
    int J2,
    double T5,
    double T6,
    double T7
    )
{


    // 247 REM ----- COMPUTE PSI(M,N,N+1/2)
    S.P1 = 2 * g.Wp[S.I] + S.I - 1;     // 248
    S.P2 = 2 * g.Wp[S.J] + S.J - 1;     // 249
    S.P3 = S.P2 + 0.5;                    // 250
    S.P4 = J2;                          // 251

    double T1, T2;

    Gosub102(                           // 252
        S,
        g,
        S.SRM,
        S.P1, S.P2, S.P3,
        T1, T2,
        g.Xa, g.Ya, g.Za,
        S.W,
        g.A[S.P4],
        g.Sa[S.P4]
        );

    double U1 = S.F5 * T1;                  // 253
    double U2 = S.F5 * T2;                  // 254

    // 255 REM ----- COMPUTE PSI(M,N-1/2,N)
    S.P3 = S.P2;                            // 256
    S.P2 -= 0.5;                            // 257
    S.P4 = J1;                              // 258
    if (S.F8 < 2)                           // 259
    {
        Gosub102(
            S,
            g,
            S.SRM,
            S.P1, S.P2, S.P3,
            T1, T2,
            g.Xa, g.Ya, g.Za,
            S.W,
            g.A[S.P4],
            g.Sa[S.P4]
            );
    }

    double V1 = S.F4 * T1;    // 260
    double V2 = S.F4 * T2;    // 261

    // S.F6 = S.F5;
    // S.F7 = S.F5;

    // 262 REM ----- S(N+1/2)*PSI(M,N,N+1/2) + S(N-1/2)*PSI(M,N-1/2,N)
    double X3 = U1 * g.CABG[J2][1] + V1 * g.CABG[J1][1];                // 263
    double Y3 = U1 * g.CABG[J2][2] + V1 * g.CABG[J1][2];                // 264
    double Z3 = (S.F7*U1*g.CABG[J2][3] + S.F6*V1*g.CABG[J1][3])*S.K;    // 265

    // // 266 REM ----- REAL PART OF VECTOR POTENTIAL CONTRIBUTION
    double D1 = S.W2 * (X3*T5 + Y3*T6 + Z3*T7);                         // 267

    X3 = U2 * g.CABG[J2][1] + V2 * g.CABG[J1][1];                       // 268
    Y3 = U2 * g.CABG[J2][2] + V2 * g.CABG[J1][2];                       // 269
    Z3 = (S.F7*U2*g.CABG[J2][3] + S.F6*V2*g.CABG[J1][3])*S.K;           // 270

    // 271 REM ----- IMAGINARY PART OF VECTOR POTENTIAL CONTRIBUTION
    double D2 = S.W2 * (X3*T5 + Y3*T6 + Z3*T7);                         // 272



    Sub_273_312(
        S,
        g,
        J1, J2,
        T1, T2,
        U1, U2
        );

    // 313 REM ----- SUM INTO IMPEDANCE MATRIX
    S.ZR[S.I][S.J] += S.K * (D1 + U1);                                  // 314
    S.ZI[S.I][S.J] += S.K * (D2 + U2);                                  // 315
}
