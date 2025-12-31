#include <iostream>
#include <vector>
#include <iomanip>
#include "GeometryOutput.hpp"

std::vector<std::vector<int>> GeometryOutput(
    int N,
    const std::vector<int>& Wp,
    int NW,
    const std::vector<std::vector<int>>& Na,
    const std::vector<double>& X,
    const std::vector<double>& Y,
    const std::vector<double>& Z,
    const std::vector<double>& A,
    std::vector<std::vector<int>> Cp)
{
    //std::vector<std::vector<int>> Cp;

    int K = 1;
    int J = 0;

    std::cout << std::fixed << std::setprecision(4);

    for (int I = 1; I <= N; ++I)
    {
        int I1 = 2 * Wp[I] - 1 + I;

        if (K > NW || K == J)
        {
            std::cout << std::setw(8) << X[I1] << "\t"
                      << std::setw(8) << Y[I1] << "\t"
                      << std::setw(8) << Z[I1] << "\t"
                      << std::setw(8) << A[Wp[I]] << "\t"
                      << std::setw(4) << Cp[I][1] << "\t"
                      << std::setw(4) << Cp[I][2] << "\t"
                      << std::setw(4) << I << "\n";

            if (I == Na[K][2] ||
                Na[K][1] == Na[K][2] ||
                Cp[I][2] == 0)
            {
                K++;
            }

            if (Cp[I][1] == 0)
                Cp[I][1] = Wp[I];

            if (Cp[I][2] == 0)
                Cp[I][2] = Wp[I];

            if (!((K == NW) && (Na[K][1] == 0) && (Na[K][2] == 0)))
            {
                if (!((I == N) && (K < NW)))
                    continue;
            }
        }

        while (true)
        {
            J = K;

            std::cout << "WIRE NO."
                      << std::setw(3) << K
                      << "\t COORDINATES\t\t\t\t\t\t  CONNECTION\tPULSE\n";

            std::cout << "  X      Y      Z    RADIUS\tEND 1\tEND 2\t NO.\n";

            if (Na[K][1] != 0 || Na[K][2] != 0)
            {
                std::cout << std::setw(8) << X[I1] << "\t"
                          << std::setw(8) << Y[I1] << "\t"
                          << std::setw(8) << Z[I1] << "\t"
                          << std::setw(8) << A[Wp[I]] << "\t"
                          << std::setw(4) << Cp[I][1] << "\t"
                          << std::setw(4) << Cp[I][2] << "\t"
                          << std::setw(4) << I << "\n";

                if (I == Na[K][2] ||
                    Na[K][1] == Na[K][2] ||
                    Cp[I][2] == 0)
                {
                    K++;
                }

                if (Cp[I][1] == 0)
                    Cp[I][1] = Wp[I];

                if (Cp[I][2] == 0)
                    Cp[I][2] = Wp[I];

                if (!((K == NW) && (Na[K][1] == 0) && (Na[K][2] == 0)))
                {
                    if (!((I == N) && (K < NW)))
                        break;
                }
            }
            else
            {
                K++;

                if (K > NW)
                    break;
            }
        }
    }

    std::cout << "Leaving GeometryOutput. " << std::endl;

    return Cp;     // MATLAB: Cp = ...
}
