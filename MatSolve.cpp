#include "MatSolve.hpp"
#include <vector>
#include <complex>

std::vector<std::complex<double>>
MatSolve(
    const std::vector<std::vector<std::complex<double>>>& Z,
    const std::vector<std::complex<double>>& b
    )
{
    int N = b.size();

    // working copy
    std::vector<std::vector<std::complex<double>>> A = Z;
    std::vector<std::complex<double>> x = b;

    // forward elimination
    for (int i = 0; i < N; ++i)
    {
        auto pivot = A[i][i];

        for (int j = i + 1; j < N; ++j)
        {
            auto factor = A[j][i] / pivot;

            for (int k = i; k < N; ++k)
                A[j][k] -= factor * A[i][k];

            x[j] -= factor * x[i];
        }
    }

    // back substitute
    std::vector<std::complex<double>> result(N);

    for (int i = N - 1; i >= 0; --i)
    {
        std::complex<double> sum = 0.0;

        for (int j = i + 1; j < N; ++j)
            sum += A[i][j] * result[j];

        result[i] = (x[i] - sum) / A[i][i];
    }

    return result;
}
