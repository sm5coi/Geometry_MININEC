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
    int P1 = 2 * g.Wp[S.I] + S.I - 1;   // 248
    int P2 = 2 * g.Wp[S.J] + S.J - 1;   // 249
    double P3 = P2 + 0.5;           // 250
    int P4 = J2;

    double T1, T2;

    Gosub102(                    // 252
        S,
         g,
        //I, J, K,
        S.SRM,
        P1, P2, P3,
        T1, T2,
        g.Xa, g.Ya, g.Za,
        S.W,
        g.A[J2],
        g.Sa[J2]
        );


    double U1 = g.Cp[S.I][2] * T1;    // ?? jmfr 253
    double U2 = g.Cp[S.I][2] * T2;    // ?? jmfr 254

    P3 = P2;            // 256
    P2 -= 0.5;          // 257

    if (S.F8 < 2)       // 259
    {
        Gosub102(
            S,
            g,
            //I, J, K,
            S.SRM,
            P1, P2, P3,
            T1, T2,
            g.Xa, g.Ya, g.Za,
            S.W,
            g.A[J2],
            g.Sa[J2]
            );

    }

    double V1 = g.Cp[S.I][1] * T1;    // 260
    double V2 = g.Cp[S.I][1] * T2;    // 261

    double F6 = S.F5;
    double F7 = S.F5;

    double X3 = U1 * g.CABG[J2][1] + V1 * g.CABG[J1][1];            // 263
    double Y3 = U1 * g.CABG[J2][2] + V1 * g.CABG[J1][2];            // 264
    double Z3 = (F7*U1*g.CABG[J2][3] + F6*V1*g.CABG[J1][3])*S.K;    // 265

    double D1 = S.W2 * (X3*T5 + Y3*T6 + Z3*T7);                     // 272

    X3 = U2 * g.CABG[J2][1] + V2 * g.CABG[J1][1];
    Y3 = U2 * g.CABG[J2][2] + V2 * g.CABG[J1][2];
    Z3 = (F7*U2*g.CABG[J2][3] + F6*V2*g.CABG[J1][3])*S.K;

    double D2 = S.W2 * (X3*T5 + Y3*T6 + Z3*T7);

    Sub_273_312(
        S,
        g,
        //I, J, K,
        J1, J2,
        T1, T2,
        U1, U2,
        P1, P3
        );

    S.ZR[S.I][S.J] += S.K * (D1 + U1);
    S.ZI[S.I][S.J] += S.K * (D2 + U2);
}
