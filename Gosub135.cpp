#include "Gosub135.hpp"
#include "KernelEval.hpp"
#include <cmath>

void Gosub135(
    SimulationState& S,
    double X2, double Y2, double Z2,
    double V1, double V2, double V3,
    double P2, double P3,
    char CSd,
    const std::vector<std::vector<int>> J2a,
    const std::vector<int>& Wp,
    double SRM,
    int FVS,
    double W,
    double Ap4,
    double Sa4,
    double& T1,
    double& T2)
{
    // Gaussian quadrature coefficients Q
    static const double Q[14] = {
        0.288675135, 0.5, 0.430568156, 0.173927423,
        0.169990522, 0.326072577, 0.480144928, 0.050614268,
        0.398333239, 0.111190517, 0.262766205, 0.156853323,
        0.091717321, 0.181341892
    };

    // Magnitudes
    double D0 = std::sqrt(X2*X2 + Y2*Y2 + Z2*Z2);
    double D3 = std::sqrt(V1*V1 + V2*V2 + V3*V3);

    double S4 = (P3 - P2) * Sa4;

    T1 = 0.0;
    T2 = 0.0;
    double I6u = 0.0;
    double F2 = 1.0;

    int L = 7;

    double T = (D0 + D3) / Sa4;

    // criteria for exact kernel
    if ((T > 1.1) || (CSd == 'N'))
    {
        if (T > 6)   L = 3;
        if (T > 10)  L = 1;
    }
    else
    {
        // Check J2a coincidence conditions
        bool cond =
            (J2a[Wp[S.I-1]][0] == J2a[Wp[S.J-1]][0]) ||
            (J2a[Wp[S.I-1]][0] == J2a[Wp[S.J-1]][1]) ||
            (J2a[Wp[S.I-1]][1] == J2a[Wp[S.J-1]][0]) ||
            (J2a[Wp[S.I-1]][1] == J2a[Wp[S.J-1]][1]);

        if (cond)
        {
            if (Ap4 <= SRM)
            {
                if (FVS == 1)
                {
                    T1 = 2 * std::log(Sa4 / Ap4);
                    T2 = -W * Sa4;
                    return;
                }
                else
                {
                    T1 = std::log(Sa4 / Ap4);
                    T2 = -W * Sa4 / 2.0;
                    return;
                }
            }

            F2 = 2 * (P3 - P2);
            I6u = (1 - std::log(S4 / F2 / 8.0 / Ap4)) / M_PI / Ap4;
        }
        else
        {
            if (T > 6)   L = 3;
            if (T > 10)  L = 1;
        }
    }

    int I5 = L + L;

    while (true)
    {
        double T3 = 0.0;
        double T4 = 0.0;

        double TT = (Q[L] + 0.5) / F2;
        KernelEval(S, X2, Y2, Z2, V1, V2, V3,
                   TT, W, SRM, I6u, Ap4,
                   T3, T4);


        TT = (0.5 - Q[L]) / F2;
        KernelEval(S, X2, Y2, Z2, V1, V2, V3,
                   TT, W, SRM, I6u, Ap4,
                   T3, T4);


        L++;
        T1 += Q[L] * T3;
        T2 += Q[L] * T4;
        L++;

        if (L >= I5)
            break;
    }

    T1 = S4 * (T1 + I6u);
    T2 = S4 * T2;
}
