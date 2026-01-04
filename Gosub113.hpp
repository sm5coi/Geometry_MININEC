#ifndef GOSUB113_HPP
#define GOSUB113_HPP

#include "SimulationState.hpp"
#include <vector>

void Gosub113(
    SimulationState& S,
    double P2, double P3,
    const std::vector<double>& Xa,
    const std::vector<double>& Ya,
    const std::vector<double>& Za,
    double X1, double Y1, double Z1,
    double& X2, double& Y2, double& Z2,
    double& V1, double& V2, double& V3
    );

#endif
