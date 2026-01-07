#ifndef MATSOLVE_HPP
#define MATSOLVE_HPP

#include <vector>
#include <complex>

// Gauss elimination
std::vector<std::complex<double>>
MatSolve(
    const std::vector<std::vector<std::complex<double>>>& Z,
    const std::vector<std::complex<double>>& b
    );

#endif
