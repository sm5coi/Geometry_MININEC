#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP

#include <vector>

void Connections(
    int I,
    int NW,
    int G,
    const std::vector<double>& XYZ1,
    const std::vector<double>& XYZ2,
    const std::vector<double>& A,
    int S1,
    std::vector<std::vector<double>>& ELM,
    std::vector<int>& J1a,
    std::vector<std::vector<int>>& J2a,
    int &I1,
    int &I2);

#endif // CONNECTIONS_HPP
