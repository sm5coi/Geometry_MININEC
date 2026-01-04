#ifndef GOSUB102_HPP
#define GOSUB102_HPP

#include "SimulationState.hpp"
#include "GeometryData.hpp"
#include <vector>
#include <array>

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
    double Sa4
    );

#endif
