#ifndef GOSUB87_HPP
#define GOSUB87_HPP

#include <vector>
#include "SimulationState.hpp"
#include "GeometryData.hpp"
void Gosub87(
    SimulationState& S,
    //int I, int J, int K,
    double SRM,
    double P1, double P2, double P3,
    const std::vector<double>& Xa,
    const std::vector<double>& Ya,
    const std::vector<double>& Za,
    double W,
    double Ap4,
    double Sa4,
    double& T1,
    double& T2
    );

#endif
