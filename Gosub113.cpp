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
    // 112 REM ----- S(U)-S(M) GOES IN (X2,Y2,Z2)
    int I4 = static_cast<int>(std::floor(P2));  // 113

    if (static_cast<double>(I4) != P2)          // 114
    {
        int I5 = I4 + 1;                        // 115
        X2 = (Xa[I4] + Xa[I5]) / 2.0 - X1;      // 116
        Y2 = (Ya[I4] + Ya[I5]) / 2.0 - Y1;      // 117
        Z2 = S.K * (Za[I4] + Za[I5]) / 2.0 - Z1;// 118
    }
    else
    {
        X2 = Xa[(int)P2] - X1;                  // 120
        Y2 = Ya[(int)P2] - Y1;                  // 121
        Z2 = S.K * Za[(int)P2] - Z1;            // 122
    }

    // ---- S(V) – S(M)
    // 123 REM ----- S(V)-S(M) GOES IN (V1,V2,V3)
    I4 = static_cast<int>(std::floor(P3));      // 124

    if (static_cast<double>(I4) != P3)          // 125
    {
        int I5 = I4 + 1;                        // 126
        V1 = (Xa[I4] + Xa[I5]) / 2.0 - X1;      // 127
        V2 = (Ya[I4] + Ya[I5]) / 2.0 - Y1;      // 128
        V3 = S.K * (Za[I4] + Za[I5]) / 2.0 - Z1;// 129
    }
    else
    {
        V1 = Xa[(int)P3] - X1;                  // 131
        V2 = Ya[(int)P3] - Y1;                  // 132
        V3 = S.K * Za[(int)P3] - Z1;            // 133
    }
}
