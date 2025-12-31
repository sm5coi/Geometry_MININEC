#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>

#include "GeometryInput.hpp"

using namespace std;

// ===== GLOBAL VARIABLES =====
// ===== GLOBAL VARIABLES =====
int MS, ML, MA, MM, MP;
double P, P0, G0;
std::string BSd, Os;
char CSd;

// int N = 0;
// int NW = 0;

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
    return -1;
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


    // // CONSTANTS / INITIALIZATION
    // MS = 150;
    // ML = 11;
    // MA = 8;
    // MM = 6;
    // MP = 50;

    P = M_PI;
    // P0 = M_PI / 180.0;

    // BSd = "********************";
    // G0 = 29.979221;
    // Os = "D";

    // std::cout << BSd << BSd << std::endl;

    FrequencyInput();
    int G = EnvironmentInput();

    GeometryData g = GeometryInput(G);

    // Open output files
    fidPsi.open("PSI_DATA.dat");
    fidGau.open("GAUSS_DATA.dat");
    fidZRZI.open("Impedans.dat");

    if(!fidPsi || !fidGau || !fidZRZI) {
        std::cerr << "Error opening output files.\n";
        return 1;
    }

    // // MENU LOOP
    // while (true) {
    //     std::cout << "   G - CHANGE GEOMETRY     C - COMPUTE/DISPLAY CURRENTS\n";
    //     std::cout << "   E - CHANGE ENVIRONMENT  P - COMPUTE FAR-FIELD PATTERNS\n";
    //     std::cout << "   X - CHANGE EXCITATION   N - COMPUTE NEAR-FIELDS\n";
    //     std::cout << "   L - CHANGE LOADS\n";
    //     std::cout << "   F - CHANGE FREQUENCY    Q - QUIT\n\n";

    //     std::cout << "   COMMAND ";
    //     std::cin >> CSd;

    //     CSd = std::toupper(CSd);

    //     if (CSd == 'P') FarFieldCalculation();
    //     else if (CSd == 'C') PrintCurrents();
    //     else if (CSd == 'N') NearField();
    //     else if (CSd == 'Q') break;
    //     // The remaining commands (G,E,X,L,F) not implemented here yet
    //     break;
    // }


    char val;

    do {
        cout << "\n===== MENY =====\n";
        cout << "A) Skriv hej\n";
        cout << "B) Visa ett tal\n";
        cout << "C) Avsluta\n";
        cout << "Välj ett alternativ: ";
        cin >> val;

        // gör om bokstaven till versal så att a/A fungerar
        val = toupper(val);

        switch (val) {
        case 'A':
            cout << "Du valde A: Hej!\n";
            break;

        case 'B':
            cout << "Du valde B: Talet är 42.\n";
            break;

        case 'C':
            cout << "Programmet avslutas.\n";
            break;

        default:
            cout << "Ogiltigt val, försök igen.\n";
        }

    } while (val != 'C');

    // Close files
    fidPsi.close();
    fidGau.close();
    fidZRZI.close();

    return 0;
}
