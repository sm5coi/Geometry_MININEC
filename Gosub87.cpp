#include "Gosub87.hpp"
#include "Gosub113.hpp"
#include "Gosub135.hpp"
#include <cmath>

void Gosub87(
    SimulationState& S,
    GeometryData g,
    double SRM,
    double P1, double P2, double P3,
    const std::vector<double>& Xa,
    const std::vector<double>& Ya,
    const std::vector<double>& Za,
    double W,
    double Ap4,
    double Sa4,
    double& T1,
    double& T2
    )
{
    // 84 REM ----- ENTRIES REQUIRED FOR IMPEDANCE MATRIX CALCULATION
    // 85 REM ----- S(M) GOES IN (X1,Y1,Z1) FOR SCALAR POTENTIAL
    // 86 REM ----- MOD FOR SMALL RADIUS TO WAVE LENGTH RATIO

    int FVS = 1;        // 87

    if (S.K >= 1)       // 88
    {
        if (Ap4 <= SRM) // 89
        {
            if ((P3 == P2 + 1.0) && (P1 == (P2 + P3) / 2.0)) // 90
            {
                T1 = 2.0 * std::log(Sa4 / Ap4); // 91
                T2 = -W * Sa4;                  // 92
                return;                         // 93
            }
        }
    }

    int I4 = static_cast<int>(std::floor(P1));  // 94
    int I5 = I4 + 1;                            // 95

    double X1 = (Xa[I4] + Xa[I5]) / 2.0;        // 96
    double Y1 = (Ya[I4] + Ya[I5]) / 2.0;        // 97
    double Z1 = (Za[I4] + Za[I5]) / 2.0;        // 98

    double X2, Y2, Z2;
    double V1, V2, V3;

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
}
