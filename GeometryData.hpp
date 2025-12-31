#ifndef GEOMETRYDATA_HPP
#define GEOMETRYDATA_HPP

#include <vector>

struct GeometryData
{
    int N;
    int NW;
    std::vector<std::vector<double>> CABG;
    std::vector<double> Sa;
    std::vector<std::vector<int>> Na;
    std::vector<std::vector<int>> Cp;
    std::vector<double> A;
    std::vector<int> Wp;
    std::vector<double> Xa;
    std::vector<double> Ya;
    std::vector<double> Za;
    std::vector<std::vector<double>> ELM;
    std::vector<int> J1a;
    std::vector<std::vector<int>> J2a;
};

#endif // GEOMETRYDATA_HPP
