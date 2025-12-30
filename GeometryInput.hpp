#ifndef GEOMETRY_INPUT_HPP
#define GEOMETRY_INPUT_HPP

#include <vector>

struct GeometryData
{
    int N;
    int NW;
    std::vector<std::vector<double>> CABG;
    std::vector<int> Sa;
    std::vector<std::vector<int>> Na;
    std::vector<std::vector<int>> Cp;
    std::vector<double> A;
    std::vector<int> Wp;
    std::vector<double> Xa;
    std::vector<double> Ya;
    std::vector<double> Za;
    std::vector<std::vector<double>> ELM;
};

// forward declaration of the function
GeometryData GeometryInput( double G);

#endif // GEOMETRYINPUT_HPP
