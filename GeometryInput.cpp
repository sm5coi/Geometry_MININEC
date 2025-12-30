#include "GeometryInput.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include "GeometryOutput.hpp"
#include "Connections.hpp"

int FLG;  // global (as in MATLAB)

// === Forward declarations of external MATLAB functions ===
void Connections(int I, int NW, double G,
                 const std::vector<double>& XYZ1,
                 const std::vector<double>& XYZ2,
                 const std::vector<double>& A,
                 int S1,
                 std::vector<std::vector<double>>& ELM,
                 int &I1,
                 int &I2);

void ExcitationInput(int n);
void LoadsInput();


// === Helper function: ReadInfile ===
void ReadInfile(std::ifstream &fid,
                int &S1,
                std::vector<double>& XYZ1,
                std::vector<double>& XYZ2,
                double &A)
{
    double L[8];
    for (int i=0; i<8; i++) {
        fid >> L[i];
    }

    S1 = static_cast<int>(L[0]);
    XYZ1 = {L[1], L[2], L[3]};
    XYZ2 = {L[4], L[5], L[6]};
    A = L[7];
}


// === MAIN FUNCTION ===
GeometryData GeometryInput( double G)
{
    GeometryData g_;

    int INFILE = 1;

    std::ifstream fid;
    if (INFILE) {
        fid.open("MININEC.INP");
        if (!fid) {
            std::cerr << "ERROR: Cannot open MININEC_chatgpt.INP\n";
            exit(1);
        }
    }

    //NW = 2;
    g_.NW = 2;

    g_.N = 0;

    // resize arrays generously
    g_.A.resize(g_.NW+5);

    g_.Sa.resize(g_.NW+5);
    g_.CABG.resize(g_.NW+5, std::vector<double>(3, 0.0));

    //ELM.resize(4, std::vector<double>(3, 0.0));
    g_.ELM.assign(2 * g_.NW + 2, std::vector<double>(3, 0.0));


    // make Cp, Wp, Na large enough for pulses
    g_.Cp.resize(200, std::vector<int>(2, 0));
    g_.Wp.resize(200, 0);
    g_.Na.resize(g_.NW+5, std::vector<int>(2, 0));

    g_.Xa.resize(500);
    g_.Ya.resize(500);
    g_.Za.resize(500);

    for (int I = 1; I <= g_.NW; I++) {

        int S1 = 0;
        std::vector<double> XYZ1(3), XYZ2(3);

        if (INFILE) {
            double rad;
            ReadInfile(fid, S1, XYZ1, XYZ2, rad);
           g_.A[I] = rad;
        }

        // MATLAB: [ELM,I1,I2] = Connections(...)
        int I1 = 0;
        int I2 = 0;

        Connections(I, g_.NW, G, XYZ1, XYZ2, g_.A, S1, g_.ELM, I1, I2);

        // direction cosines
        std::vector<double> XYZ3(3);
        for (int k=0; k<3; ++k)
            XYZ3[k] = XYZ2[k] - XYZ1[k];

        double D = std::sqrt(XYZ3[0]*XYZ3[0] + XYZ3[1]*XYZ3[1] + XYZ3[2]*XYZ3[2]);

        g_.CABG[I][0] = XYZ3[0]/D;
        g_.CABG[I][1] = XYZ3[1]/D;
        g_.CABG[I][2] = XYZ3[2]/D;

        g_.Sa[I] = static_cast<int>(D / S1);

        int N1 = g_.N + 1;
        g_.Na[I][0] = N1;

        if (S1 == 1 && I1 == 0)
            g_.Na[I][0] = 0;

        g_.N = N1 + S1;

        if (I1 == 0) g_.N--;
        if (I2 == 0) g_.N--;

        g_.Na[I][1] = g_.N;

        if (S1 == 1 && I2 == 0)
            g_.Na[I][1] = 0;

        // Fill Cp and Wp
        if (g_.N >= N1) {

            for (int J = N1; J <= g_.N; ++J) {
                g_.Cp[J][0] = I;
                g_.Cp[J][1] = I;
                g_.Wp[J] = I;
            }

            g_.Cp[N1][0] = I1;
            g_.Cp[g_.N][1] = I2;

            int I1idx = N1 + 2*(I-1);
            int I3 = I1idx;

            g_.Xa[I1idx] = XYZ1[0];
            g_.Ya[I1idx] = XYZ1[1];
            g_.Za[I1idx] = XYZ1[2];

            if (g_.Cp[N1][0] != 0) {
                int II = std::abs(g_.Cp[N1][0]);
                double F3 = (g_.Cp[N1][0] > 0 ? 1 : -1) * g_.Sa[II];

                g_.Xa[I1idx] -= F3 * g_.CABG[II][0];
                g_.Ya[I1idx] -= F3 * g_.CABG[II][1];
                g_.Za[I1idx] -= F3 * g_.CABG[II][2];

                I3++;
            }

            int I6 = g_.N + 2*I;

            for (int I4 = I1idx+1; I4 <= I6; ++I4) {
                int J = I4 - I3;
                g_.Xa[I4] = XYZ1[0] + J*XYZ3[0]/S1;
                g_.Ya[I4] = XYZ1[1] + J*XYZ3[1]/S1;
                g_.Za[I4] = XYZ1[2] + J*XYZ3[2]/S1;
            }

            if (g_.Cp[g_.N][1] != 0) {
                int II = std::abs(g_.Cp[g_.N][1]);
                double F3 = (g_.Cp[g_.N][1] > 0 ? 1 : -1) * g_.Sa[II];

                int I3x = I6 - 1;
                g_.Xa[I6] = g_.Xa[I3x] + F3*g_.CABG[II][0];
                g_.Ya[I6] = g_.Ya[I3x] + F3*g_.CABG[II][1];
                g_.Za[I6] = g_.Za[I3x] + F3*g_.CABG[II][2];
            }
        }
        else {
            // single segment case
            int I1idx = N1 + 2*(I-1);

            g_.Xa[I1idx]   = XYZ1[0];
            g_.Ya[I1idx]   = XYZ1[1];
            g_.Za[I1idx]   = XYZ1[2];

            g_.Xa[I1idx+1] = XYZ2[0];
            g_.Ya[I1idx+1] = XYZ2[1];
            g_.Za[I1idx+1] = XYZ2[2];
        }

    } // end FOR

    // OUTPUT & other calls
    g_.Cp = GeometryOutput(g_.N, g_.Wp, g_.NW, g_.Na, g_.Xa, g_.Ya, g_.Za, g_.A, g_.Cp);

    //ExcitationInput(10);
    //LoadsInput();

    FLG = 0;

    return g_;
}
