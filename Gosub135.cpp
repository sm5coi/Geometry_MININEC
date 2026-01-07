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
    static const double Q[15] = {0.0,
        0.288675135, 0.5, 0.430568156, 0.173927423,
        0.169990522, 0.326072577, 0.480144928, 0.050614268,
        0.398333239, 0.111190517, 0.262766205, 0.156853323,
        0.091717321, 0.181341892
    };

    // Magnitudes
    // 134 REM ----- MAGNITUDE OF S(U) - S(M)
    double D0 = std::sqrt(X2*X2 + Y2*Y2 + Z2*Z2);   // 135, 137
    // 136 REM ----- MAGNITUDE OF S(V) - S(M)
    double D3 = std::sqrt(V1*V1 + V2*V2 + V3*V3);   // 138, 139

    // 140 REM ----- SQUARE OF WIRE RADIUS
    // 141 A2 = A(P4) * A(P4)
    // 142 REM ----- MAGNITUDE OF S(V) - S(U)

    double S4 = (P3 - P2) * Sa4;        // 143

    // 144 REM ----- ORDER OF INTEGRATION
    // 145 REM ----- LTH ORDER GAUSSIAN QUADRATURE

    T1 = 0.0;                           // 146
    T2 = 0.0;                           // 147
    double I6u = 0.0;                   // 148
    double F2 = 1.0;                    // 149

    int L = 7;                          // 150

    double T = (D0 + D3) / Sa4;         // 151

    // criteria for exact kernel
    // 152 REM ----- CRITERIA FOR EXACT KERNEL
    if ((T > 1.1) || (CSd == 'N'))      // 153, 154
    {
        if (T > 6)   L = 3;             // 165
        if (T > 10)  L = 1;             // 166
    }
    else
    {
        // Check J2a coincidence conditions
        bool cond =
            (J2a[Wp[S.I]][1] == J2a[Wp[S.J]][1]) || // 155
            (J2a[Wp[S.I]][1] == J2a[Wp[S.J]][2]) || // 156
            (J2a[Wp[S.I]][2] == J2a[Wp[S.J]][1]) || // 157
            (J2a[Wp[S.I]][2] == J2a[Wp[S.J]][2]);   // 158

        if (cond)
        {
            if (Ap4 <= SRM)                         // 160
            {
                if (FVS == 1)                       // 161
                {
                    T1 = 2 * std::log(Sa4 / Ap4);   // 91
                    T2 = -W * Sa4;                  // 92
                    return;                         // 93
                }
                else
                {
                    T1 = std::log(Sa4 / Ap4);       // 106
                    T2 = -W * Sa4 / 2.0;            // 107
                    return;                         // 108
                }
            }

            F2 = 2 * (P3 - P2);                                     // 162
            I6u = (1 - std::log(S4 / F2 / 8.0 / Ap4)) / M_PI / Ap4; // 163
        }
        else                        // 159
        {
            if (T > 6)   L = 3;     // 165
            if (T > 10)  L = 1;     // 166
        }
    }

    int I5 = L + L;                 // 167

    while (true)
    {
        double T3 = 0.0;            // 168
        double T4 = 0.0;            // 169

        double TT = (Q[L] + 0.5) / F2;          // 170
        KernelEval(S, X2, Y2, Z2, V1, V2, V3,   // 171
                   TT, W, SRM, I6u, Ap4,
                   T3, T4);



        TT = (0.5 - Q[L]) / F2;                 // 172
        KernelEval(S, X2, Y2, Z2, V1, V2, V3,   // 173
                   TT, W, SRM, I6u, Ap4,
                   T3, T4);


        L++;                // 174
        T1 += Q[L] * T3;    // 175
        T2 += Q[L] * T4;    // 176
        L++;                // 177

        if (L >= I5) break; // 178
    }

    T1 = S4 * (T1 + I6u);   // 179
    T2 = S4 * T2;           // 180
}
