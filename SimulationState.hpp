#ifndef SIMULATIONSTATE_HPP
#define SIMULATIONSTATE_HPP

#include <vector>
#include <complex>
//#include <array>
#include <string>
#include <cmath>

struct SimulationState
{
    // State variabled due to Common in MININEC3
    int G = 1;  // Freespace G = 1; Ground Plane G = -1
    int FLG = 0;
    int MS = 150;   // Maximum number of segments (Pulses + 2 * Wires) = 150
    int MW = 50;    // Maximum number of wires = 50
    int ML = 11;;   // Maximum number of loads = 11
    int MA = 8;     // Maximum order of S-paramer loads = 8
    int MM = 6;     // Maximum number of media = 6
    int MP = 50;    // Maximum number of pulses = 50
    double P = M_PI;
    double P0 = M_PI / 180.0;;
    double G0 = 29.979221;  // Intrinsic impedance of free space divided by 2*pi
    std::string BSd = "********************";
    std:: string Os = "D";
    char CSd;

    // State variables due to PrintCurrents()
    std::vector<std::complex<double>> CurrX;

    // impedance
    std::vector<std::vector<double>> ZR;
    std::vector<std::vector<double>> ZI;
    std::vector<std::complex<double>> Z;

    // =================== BASIC frequency globals =====================
    // Converted from global common block in MININEC
    double S0 = 0.0;
    double M  = 0.0;
    double SRM = 0.0;
    double W = 0.0;
    double W2 = 0.0;

    // =================== impedance calc flags ========================
    double F5 = 0.0;
    double F8 = 0.0;

    // loop variabels in ImpedanceMatrixCalculation ad it subs
    int I;
    int J;
    int K;


};

#endif // SIMULATIONSTATE_HPP

