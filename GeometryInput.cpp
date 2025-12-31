#include <iostream>
#include <fstream>
#include <cmath>
#include "GeometryInput.hpp"
#include "GeometryOutput.hpp"
#include "Connections.hpp"

int FLG;  // global (as in MATLAB)

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
GeometryData GeometryInput( int G)
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

    g_.N = 0;  // 1162

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

    for (int I = 1; I <= g_.NW; I++) {   // 1163

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

        // 1184
        Connections(I, g_.NW, G, XYZ1, XYZ2, g_.A, S1, g_.ELM, g_.J1a, g_.J2a, I1, I2);

        // direction cosines
        std::vector<double> XYZ3(3);
        for (int k=0; k<3; ++k)          // 1190 - 1192
            XYZ3[k] = XYZ2[k] - XYZ1[k];

        double D = std::sqrt(XYZ3[0]*XYZ3[0] + XYZ3[1]*XYZ3[1] + XYZ3[2]*XYZ3[2]); // 1193

        g_.CABG[I][0] = XYZ3[0]/D;  // 1194
        g_.CABG[I][1] = XYZ3[1]/D;  // 1195
        g_.CABG[I][2] = XYZ3[2]/D;  // 1196

        g_.Sa[I] = (D / S1);        // 1197

        // Compute connectivity data (Pulse N1 to N)
        int N1 = g_.N + 1;          // 1199
        g_.Na[I][0] = N1;           // 1200

        if (S1 == 1 && I1 == 0)     // 1201
            g_.Na[I][0] = 0;

        g_.N = N1 + S1;             // 1202

        if (I1 == 0) g_.N--;        // 1203
        if (I2 == 0) g_.N--;        // 1204

        g_.Na[I][1] = g_.N;         // 1206

        if (S1 == 1 && I2 == 0)     // 1207
            g_.Na[I][1] = 0;

            // Fill Cp and Wp
        if (g_.N >= N1) {           // 1208

            for (int J = N1; J <= g_.N; ++J) {  // 1209 - 1213
                g_.Cp[J][0] = I;
                g_.Cp[J][1] = I;
                g_.Wp[J] = I;
            }

            g_.Cp[N1][0] = I1;      // 1214
            g_.Cp[g_.N][1] = I2;    // 1215

            // Compute coordinates of break points
            int I1idx = N1 + 2*(I-1);   //1217
            int I3 = I1idx;             // 1218

            g_.Xa[I1idx] = XYZ1[0];     // 1219
            g_.Ya[I1idx] = XYZ1[1];     // 1220
            g_.Za[I1idx] = XYZ1[2];     // 1221

            if (g_.Cp[N1][0] != 0) {    // 1222
                int II = std::abs(g_.Cp[N1][0]);                        // 1223
                double F3 = (g_.Cp[N1][0] > 0 ? 1 : -1) * g_.Sa[II];    // 1224

                g_.Xa[I1idx] -= F3 * g_.CABG[II][0];                    // 1225
                g_.Ya[I1idx] -= F3 * g_.CABG[II][1];                    // 1226
                // 1227 IF (C%(N1,1)=-I THEN F3 = -F3
                g_.Za[I1idx] -= F3 * g_.CABG[II][2];                    // 1228

                I3++;                                                   // 1229
            }

            int I6 = g_.N + 2*I;                                        // 1230

            for (int I4 = I1idx+1; I4 <= I6; ++I4) {                    // 1231
                int J = I4 - I3;                                        // 1232
                g_.Xa[I4] = XYZ1[0] + J*XYZ3[0]/S1;                     // 1233
                g_.Ya[I4] = XYZ1[1] + J*XYZ3[1]/S1;                     // 1234
                g_.Za[I4] = XYZ1[2] + J*XYZ3[2]/S1;                     // 1235
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
            // single segment  0 pulse case
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

    FLG = 0;

    return g_;
}
