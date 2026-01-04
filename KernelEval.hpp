#ifndef KERNELEVAL_HPP
#define KERNELEVAL_HPP

#include "SimulationState.hpp"

void KernelEval(
    SimulationState& S,
    //int K,
    double X2, double Y2, double Z2,
    double V1, double V2, double V3,
    double T,
    double W,
    double SRM,
    double I6u,
    double Ap4,
    double& T3,
    double& T4
    );




#endif
