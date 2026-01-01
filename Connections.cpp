#include <iostream>
#include <vector>
#include <cmath>
#include "Connections.hpp"

static void WriteConnection(
    const std::vector<double>& XYZ1,
    const std::vector<double>& XYZ2,
    int I1,
    int I2,
    double A,
    int S1)
{
    std::cout << "   In WriteConnection()\n";
    std::cout << "            COORDINATES                          END          NO. OF\n";
    std::cout << "   X           Y           Z        RADIUS       CONNECTION   SEGMENTS\n";

    std::cout << std::fixed;
    std::cout.precision(3);

    std::cout << XYZ1[1] << "\t" << XYZ1[2] << "\t" << XYZ1[3]
              << "\t\t" << I1 << "\n";

    std::cout << XYZ2[1] << "\t" << XYZ2[2] << "\t" << XYZ2[3]
              << "\t" << A << "\t" << I2 << "\t " << S1 << "\n\n";
}

// ======================================================================
// TRANSLATED FUNCTION
// ======================================================================

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
    int &I2)
{


    // Ensure J arrays allocated
    if ((int)J1a.size() < NW + 5)
        J1a.resize(NW + 5, 0);
    if ((int)J2a.size() < NW + 5)
        J2a.resize(NW + 5, std::vector<int>(3, 0));

    // Equivalent logic
    ELM[I][1] = XYZ1[1];
    ELM[I][2] = XYZ1[2];
    ELM[I][3] = XYZ1[3];

    ELM[I+NW][1] = XYZ2[1];
    ELM[I+NW][2] = XYZ2[2];
    ELM[I+NW][3] = XYZ2[3];

    int Gp = 0;
    I1 = 0;
    I2 = 0;

    J1a[I] = 0;

    J2a[I][1] = -I;
    J2a[I][2] = -I;

    // ======================================================================
    // CASE 1: FREE SPACE (G == 1)
    // ======================================================================

    if (G == 1) {

        if (I == 1) {
            WriteConnection(XYZ1, XYZ2, I1, I2, A[I], S1);
            return;
        }

        for (int J = 1; J <= I-1; ++J) {

            // END1 to END1
            if (XYZ1[1] == ELM[J][1] &&
                XYZ1[2] == ELM[J][2] &&
                XYZ1[3] == ELM[J][3])
            {
                I1 = -J;
                J2a[I][1] = J;
                if (J2a[J][1] == -J) J2a[J][1] = J;
                break;
            }

            // END1 to END2
            if (XYZ1[1] == ELM[J+NW][1] &&
                XYZ1[2] == ELM[J+NW][2] &&
                XYZ1[3] == ELM[J+NW][3])
            {
                I1 = J;
                J2a[I][1] = J;
                if (J2a[J][2] == -J) J2a[J][2] = J;
                break;
            }
        }

    }

    // ======================================================================
    // CASE 2: GROUND PLANE (G == -1)
    // ======================================================================

    else if (G == -1) {

        if (XYZ1[3] == 0) {
            I1 = -I;
            J1a[I] = -1;
        }
        else {
            if (XYZ2[3] == 0) {
                I2 = -I;
                J1a[I] = 1;
                Gp = 1;
            }
            if (I == 1) {
                WriteConnection(XYZ1, XYZ2, I1, I2, A[I], S1);
                return;
            }

            for (int J = 1; J <= I-1; ++J) {

                if (XYZ1[1] == ELM[J][1] &&
                    XYZ1[2] == ELM[J][2] &&
                    XYZ1[3] == ELM[J][3])
                {
                    I1 = -J;
                    J2a[I][1] = J;
                    if (J2a[J][1] == -J) J2a[J][1] = J;
                    break;
                }

                if (XYZ1[1] == ELM[J+NW][1] &&
                    XYZ1[2] == ELM[J+NW][2] &&
                    XYZ1[3] == ELM[J+NW][3])
                {
                    I1 = J;
                    J2a[I][1] = J;
                    if (J2a[J][2] == -J) J2a[J][2] = J;
                    break;
                }
            }
        }

    }

    // ======================================================================
    // ERROR CASE
    // ======================================================================
    else {
        std::cerr << "Erroneous Environment Variable!\n";
        return;
    }

    // ======================================================================
    // POST-GROUND-CASE OPTIONAL END2 CHECKS
    // ======================================================================

    if (Gp != 1) {

        if (I != 1) {
            for (int J = 1; J <= I-1; ++J) {

                if (XYZ2[1] == ELM[J+NW][1] &&
                    XYZ2[2] == ELM[J+NW][2] &&
                    XYZ2[3] == ELM[J+NW][3])
                {
                    I2 = -J;
                    J2a[I][2] = J;
                    if (J2a[J][2] == -J) J2a[J][2] = J;
                    break;
                }

                if (XYZ2[1] == ELM[J][1] &&
                    XYZ2[2] == ELM[J][2] &&
                    XYZ2[3] == ELM[J][3])
                {
                    I2 = J;
                    J2a[I][2] = J;
                    if (J2a[J][1] == -J) J2a[J][1] = J;
                    break;
                }
            }
        }
    }

    WriteConnection(XYZ1, XYZ2, I1, I2, A[I], S1);
}
