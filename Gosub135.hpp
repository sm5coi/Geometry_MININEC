#ifndef GOSUB135_HPP
#define GOSUB135_HPP

#include "SimulationState.hpp"
#include <vector>
#include <array>

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
    double& T2
    );

#endif
