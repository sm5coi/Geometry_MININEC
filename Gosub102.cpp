#include "Gosub102.hpp"
#include "Gosub113.hpp"
#include "Gosub135.hpp"
#include <cmath>

void Gosub102(
    SimulationState& S,
    GeometryData g,
    double SRM,
    double P1, double P2, double P3,
    double& T1, double& T2,
    const std::vector<double>& Xa,
    const std::vector<double>& Ya,
    const std::vector<double>& Za,
    double W,
    double Ap4,
    double Sa4)
{
    // 100 REM ----- S(M) GOES IN (X1,Y1,Z1) FOR VECTOR POTENTIAL
    // 101 REM ----- MOD FOR SMALL RADIUS TO WAVE LENGTH RATIO

    // if ((S.I == 5) && (S.J == 5))
    // {
    //     int q0 = 1;
    // }

    int FVS = 0;            // 102

    if (S.K >= 1)           // 103
    {
        if (Ap4 < SRM)      // 104
        {
            if ((S.I == S.J) && (P3 - (P2 + 0.5)))  // 105
            {
                T1 = std::log(Sa4 / Ap4);           // 106
                T2 = -W * Sa4 / 2.0;                // 107
                return;
            }
        }
    }

    double X1 = Xa[(int)P1];    // 109
    double Y1 = Ya[(int)P1];    // 110
    double Z1 = Za[(int)P1];    // 111

    double X2, Y2, Z2;
    double V1, V2, V3;


    // 112 REM ----- S(U)-S(M) GOES IN (X2,Y2,Z2)
    Gosub113(
        S,
        P2, P3,
        Xa, Ya, Za,
        X1, Y1, Z1,
        X2, Y2, Z2,
        V1, V2, V3
        );

    Gosub135(
        S,
        X2, Y2, Z2,
        V1, V2, V3,
        P2, P3,
        S.CSd,
        g.J2a,
        g.Wp,
        SRM,
        FVS,
        W,
        Ap4,
        Sa4,
        T1,
        T2
        );

    int q1 = 1;
}
