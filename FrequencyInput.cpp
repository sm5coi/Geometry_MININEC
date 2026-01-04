#include "FrequencyInput.hpp"
#include "SimulationState.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>

void FrequencyInput(SimulationState& S)
{
    double F = 299.8;               // MHz
    double lambda = 299.8 / F;      // wavelength in meters?

    S.S0  = 0.001 * lambda;
    S.M   = 4.77783352 * lambda;
    S.SRM = 0.0001 * lambda;

    std::cout << "    WAVE LENGTH = "
              << std::fixed << std::setprecision(3)
              << lambda
              << " METERS\n";

    S.W  = 2.0 * M_PI / lambda;
    S.W2 = S.W * S.W / 2.0;
}
