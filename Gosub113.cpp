#include "Gosub113.hpp"
#include <cmath>

void Gosub113(
    SimulationState& S,
    double P2, double P3,
    const std::vector<double>& Xa,
    const std::vector<double>& Ya,
    const std::vector<double>& Za,
    double X1, double Y1, double Z1,
    double& X2, double& Y2, double& Z2,
    double& V1, double& V2, double& V3
    )
{
    // ---- S(U) – S(M)
    int I4 = static_cast<int>(std::floor(P2));

    if (static_cast<double>(I4) != P2)
    {
        int I5 = I4 + 1;
        X2 = (Xa[I4] + Xa[I5]) / 2.0 - X1;
        Y2 = (Ya[I4] + Ya[I5]) / 2.0 - Y1;
        Z2 = S.K * (Za[I4] + Za[I5]) / 2.0 - Z1;
    }
    else
    {
        X2 = Xa[(int)P2] - X1;
        Y2 = Ya[(int)P2] - Y1;
        Z2 = S.K * Za[(int)P2] - Z1;
    }

    // ---- S(V) – S(M)
    I4 = static_cast<int>(std::floor(P3));

    if (static_cast<double>(I4) != P3)
    {
        int I5 = I4 + 1;
        V1 = (Xa[I4] + Xa[I5]) / 2.0 - X1;
        V2 = (Ya[I4] + Ya[I5]) / 2.0 - Y1;
        V3 = S.K * (Za[I4] + Za[I5]) / 2.0 - Z1;
    }
    else
    {
        V1 = Xa[(int)P3] - X1;
        V2 = Ya[(int)P3] - Y1;
        V3 = S.K * Za[(int)P3] - Z1;
    }
}
