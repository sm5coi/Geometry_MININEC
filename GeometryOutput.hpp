#ifndef GEOMETRYOUTPUT_HPP
#define GEOMETRYOUTPUT_HPP

#include <vector>

std::vector<std::vector<int>> GeometryOutput(
    int N,
    const std::vector<int>& Wp,
    int NW,
    const std::vector<std::vector<int>>& Na,
    const std::vector<double>& X,
    const std::vector<double>& Y,
    const std::vector<double>& Z,
    const std::vector<double>& A,
    std::vector<std::vector<int>> Cp);

#endif // GEOMETRYOUTPUT_HPP
