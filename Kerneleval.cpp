#include "KernelEval.hpp"
#include "EllipticIntegral.hpp"
#include <cmath>

// KernelEval: translation of NEC/MININEC core routine
void KernelEval(
    SimulationState& S,
    double X2, double Y2, double Z2,
    double V1, double V2, double V3,
    double T, double W,
    double SRM,
    double I6u,
    double Ap4,
    double& T3,
    double& T4
    )
{
    const double A2 = Ap4 * Ap4;

    // 27 REM ********** KERNEL EVALUATION OF INTEGRALS I2 & I3 **********
    double X3, Y3, Z3;

    // MATLAB: if K>=0 else branch
    if (S.K >= 0)                   // 28
    {
        X3 = X2 + T * (V1 - X2);    // 29
        Y3 = Y2 + T * (V2 - Y2);    // 30
        Z3 = Z2 + T * (V3 - Z2);    // 31
    }
    else
    {
        X3 = V1 + T * (X2 - V1);    // 33
        Y3 = V2 + T * (Y2 - V2);    // 34
        Z3 = V3 + T * (Z2 - V3);    // 35
    }

    double D3 = X3*X3 + Y3*Y3 + Z3*Z3;  // 36
    double D;

    // 37 REM ----- MOD FOR SMALL RADIUS TO WAVELENGTH RATIO
    // small-radius condition
    if (Ap4 <= SRM)         // 38
    {
        D = std::sqrt(D3);  // 38
    }
    else
    {
        D = D3 + A2;                    // 39
        if (D > 0.0) D = std::sqrt(D);  // 40

        // 41 REM ----- CRITERIA FOR USING REDUCED KERNEL
        if (I6u != 0.0)                 // 42
        {
            // Exact kernel: Elliptic integral
            // 43 REM ----- EXACT KERNEL CALCULATION WITH ELLIPTIC INTEGRAL
            double B = D3 / (D3 + 4.0*A2);      // 44

            double V0 = EllipticIntegral(B);    // 45, 46, 47
            V0 *= std::sqrt(1.0 - B);           // part of 47

            T3 += (V0 + std::log(D3/(64.0*A2))/2.0) / (M_PI * Ap4) - 1.0/D; // 48
        }
    }

    const double B1 = D * W;    // 49

    // exp(-j k r) / r
    // 50 REM ----- EXP(-J*K*R)/R
    T3 += std::cos(B1)/D;   // real part       // 51
    T4 -= std::sin(B1)/D;   // imaginary part  // 52
}
