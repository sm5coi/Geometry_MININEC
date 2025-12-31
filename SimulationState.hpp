#ifndef SIMULATIONSTATE_HPP
#define SIMULATIONSTATE_HPP

//#include <vector>
//#include <complex>
//#include <array>
#include <string>
#include <cmath>

struct SimulationState
{
    int G = 1;  // Freespace G = 1; Ground Plane G = -1
    int FLG = 0;
    int MS = 150;
    int ML = 11;;
    int MA = 8;
    int MM = 6;
    int MP = 50;
    double P = M_PI;
    double P0 = M_PI / 180.0;;
    double G0 = 29.979221;
    std::string BSd = "********************";
    std:: string Os = "D";
    char CSd;
};

#endif // SIMULATIONSTATE_HPP

// // CONSTANTS / INITIALIZATION
// MS = 150;
// ML = 11;
// MA = 8;
// MM = 6;
// MP = 50;

// P = M_PI;
// P0 = M_PI / 180.0;

// BSd = "********************";
// G0 = 29.979221;
// Os = "D";
