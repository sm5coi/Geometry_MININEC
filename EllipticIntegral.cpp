#include "EllipticIntegral.hpp"
#include <cmath>

double EllipticIntegral(double B)
{
    // Abramowitz & Stegun constants
    const double C0 = 1.38629436112;
    const double C1 = 0.09666344259;
    const double C2 = 0.03590092383;
    const double C3 = 0.03742563713;
    const double C4 = 0.01451196212;
    const double C5 = 0.5;
    const double C6 = 0.12498593397;
    const double C7 = 0.06880248576;
    const double C8 = 0.0332835346;
    const double C9 = 0.00441787012;

    // avoid log(0)
    if (B <= 0.0)
        return 0.0;

    // W0 = C0 + B*(C1 + B*(C2 + B*(C3 + B*C4)));
    double W0 = C0 + B * ( C1 + B * ( C2 + B * ( C3 + B * C4 ) ) );

    // W1 = C5 + B*(C6 + B*(C7 + B*(C8 + B*C9)));
    double W1 = C5 + B * ( C6 + B * ( C7 + B * ( C8 + B * C9 ) ) );

    // V0 = (W0 - W1 * log(B))
    double V0 = W0 - W1 * std::log(B);

    return V0;
}
