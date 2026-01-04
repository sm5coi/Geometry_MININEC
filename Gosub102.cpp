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
    int FVS = 0;

    if (S.K >= 1)
    {
        if (Ap4 < SRM)
        {
            if ((S.I == S.J) && (fabs(P3 - (P2 + 0.5)) < 1e-12))
            {
                T1 = std::log(Sa4 / Ap4);
                T2 = -W * Sa4 / 2.0;
                return;
            }
        }
    }

    double X1 = Xa[(int)P1 - 1];
    double Y1 = Ya[(int)P1 - 1];
    double Z1 = Za[(int)P1 - 1];

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
