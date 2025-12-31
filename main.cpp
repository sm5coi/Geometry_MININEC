#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>

#include "SimulationState.hpp"
#include "GeometryInput.hpp"

using namespace std;

// std::vector<std::vector<double>> CABG;
// std::vector<int> Sa;
// std::vector<std::vector<int>> Na;
// std::vector<std::vector<int>> Cp;
// std::vector<int> Wp;
// std::vector<double> Xa, Ya, Za, A;
// std::vector<std::vector<double>> ELM;

// File streams
std::ofstream fidPsi;
std::ofstream fidGau;
std::ofstream fidZRZI;

// ===== PLACEHOLDER FUNCTIONS =====
// (These must be implemented separately later)

void FrequencyInput() {
    // TODO: Implement
}

int EnvironmentInput() {
    // TODO: Implement
    return -1; // -1 => Ground Plane, for the MININEC.INP standard test-example
}

// void GeometryInput(double G) {
//     // TODO: Implement
// }

void FarFieldCalculation() {
    // TODO: Implement
}

void PrintCurrents() {
    // TODO: Implement
}

void NearField() {
    // TODO: Implement
}

// =================================
// ========== MAIN PROGRAM =========
// =================================
int main() {
    system("chcp 65001 > nul");

    SimulationState S;

    std::cout << S.BSd << S.BSd << std::endl;

    FrequencyInput();
    S.G = EnvironmentInput();

    GeometryData g = GeometryInput( S);

    // Open output files
    fidPsi.open("PSI_DATA.dat");
    fidGau.open("GAUSS_DATA.dat");
    fidZRZI.open("Impedans.dat");

    if(!fidPsi || !fidGau || !fidZRZI) {
        std::cerr << "Error opening output files.\n";
        return 1;
    }    

     do {
        std::cout << std::endl;
        std::cout << "   G - CHANGE GEOMETRY     C - COMPUTE/DISPLAY CURRENTS\n";
        std::cout << "   E - CHANGE ENVIRONMENT  P - COMPUTE FAR-FIELD PATTERNS\n";
        std::cout << "   X - CHANGE EXCITATION   N - COMPUTE NEAR-FIELDS\n";
        std::cout << "   L - CHANGE LOADS\n";
        std::cout << "   F - CHANGE FREQUENCY    Q - QUIT\n\n";

        std::cout << "   COMMAND ";
        std::cin >> S.CSd;

        S.CSd = std::toupper(S.CSd);

        switch (S.CSd) {
        case 'A':
            cout << "Du valde A: Hej!\n";
            break;

        case 'B':
            cout << "Du valde B: Talet är 42.\n";
            break;
        case 'C':
            cout << "COMPUTE/DISPLAY CURRENTS\n";

            break;
        case 'Q':
            cout << "Programmet avslutas.\n";
            break;

        default:
            cout << "Ogiltigt val, försök igen.\n";
        }

    } while (S.CSd != 'Q');

    // Close files
    fidPsi.close();
    fidGau.close();
    fidZRZI.close();

    return 0;
}
