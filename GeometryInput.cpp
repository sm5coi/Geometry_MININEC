#include <iostream>
#include <fstream>
#include <cmath>
#include "GeometryInput.hpp"
#include "GeometryOutput.hpp"
#include "Connections.hpp"
#include "SimulationState.hpp"

//int FLG;  // global (as in MATLAB)

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
    XYZ1 = {0.0, L[1], L[2], L[3]};
    XYZ2 = {0.0, L[4], L[5], L[6]};
    A = L[7];
}


// === MAIN FUNCTION ===
GeometryData GeometryInput( SimulationState& S)
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
    g_.A.resize(S.MW+1);

    g_.Sa.resize(S.MW+1);
    g_.CABG.resize(S.MW+1, std::vector<double>(4, 0.0));

    //ELM.resize(4, std::vector<double>(3, 0.0));
    g_.ELM.assign(S.MW+S.MP, std::vector<double>(4, 0.0));

    // make Cp, Wp, Na large enough for pulses
    g_.Cp.resize(S.MP+1, std::vector<int>(3, 0));
    g_.Wp.resize(S.MP+1, 0);
    g_.Na.resize(S.MW+1, std::vector<int>(3, 0));

    g_.Xa.resize(S.MS+1);               // 6
    g_.Ya.resize(S.MS+1);               // 6
    g_.Za.resize(S.MS+1);               // 6

    for (int I = 1; I <= g_.NW; I++) {   // 1163

        int S1 = 0;
        std::vector<double> XYZ1(4), XYZ2(4);

        if (INFILE) {
            double rad;
            ReadInfile(fid, S1, XYZ1, XYZ2, rad);
           g_.A[I] = rad;
        }

        // MATLAB: [ELM,I1,I2] = Connections(...)
        int I1 = 0;
        int I2 = 0;

        // 1184
        Connections(I, g_.NW, S.G, XYZ1, XYZ2, g_.A, S1, g_.ELM, g_.J1a, g_.J2a, I1, I2);

        // direction cosines
        std::vector<double> XYZ3(4);

        XYZ3[1] = XYZ2[1] - XYZ1[1];    // 1190
        XYZ3[2] = XYZ2[2] - XYZ1[2];    // 1191
        XYZ3[3] = XYZ2[3] - XYZ1[3];    // 1192

        double D = std::sqrt(XYZ3[1]*XYZ3[1] + XYZ3[2]*XYZ3[2] + XYZ3[3]*XYZ3[3]); // 1193

        g_.CABG[I][1] = XYZ3[1]/D;  // 1194
        g_.CABG[I][2] = XYZ3[2]/D;  // 1195
        g_.CABG[I][3] = XYZ3[3]/D;  // 1196

        g_.Sa[I] = (D / S1);        // 1197

        // Compute connectivity data (Pulse N1 to N)
        int N1 = g_.N + 1;          // 1199
        g_.Na[I][1] = N1;           // 1200

        if (S1 == 1 && I1 == 0)     // 1201
            g_.Na[I][1] = 0;

        g_.N = N1 + S1;             // 1202

        if (I1 == 0) g_.N--;        // 1203
        if (I2 == 0) g_.N--;        // 1204

        g_.Na[I][2] = g_.N;         // 1206

        if (S1 == 1 && I2 == 0)     // 1207
            g_.Na[I][2] = 0;

            // Fill Cp and Wp
        if (g_.N >= N1) {           // 1208

            for (int J = N1; J <= g_.N; ++J) {  // 1209 - 1213
                g_.Cp[J][1] = I;
                g_.Cp[J][2] = I;
                g_.Wp[J] = I;
            }

            g_.Cp[N1][1] = I1;      // 1214
            g_.Cp[g_.N][2] = I2;    // 1215

            // Compute coordinates of break points
            int I1idx = N1 + 2*(I-1);   //1217
            int I3 = I1idx;             // 1218

            g_.Xa[I1idx] = XYZ1[1];     // 1219
            g_.Ya[I1idx] = XYZ1[2];     // 1220
            g_.Za[I1idx] = XYZ1[3];     // 1221

            if (g_.Cp[N1][1] != 0) {    // 1222
                int II = std::abs(g_.Cp[N1][1]);                        // 1223
                double F3 = (g_.Cp[N1][1] > 0 ? 1 : -1) * g_.Sa[II];    // 1224

                g_.Xa[I1idx] -= F3 * g_.CABG[II][1];                    // 1225
                g_.Ya[I1idx] -= F3 * g_.CABG[II][2];                    // 1226
                // 1227 IF (C%(N1,1)=-I THEN F3 = -F3
                // if Cp(N1,1)== -I, F3 = -F3; end
                g_.Za[I1idx] -= F3 * g_.CABG[II][3];                    // 1228

                I3++;                                                   // 1229
            }

            int I6 = g_.N + 2*I;                                        // 1230

            for (int I4 = I1idx+1; I4 <= I6; ++I4) {                    // 1231
                int J = I4 - I3;                                        // 1232
                g_.Xa[I4] = XYZ1[1] + J*XYZ3[1]/S1;                     // 1233
                g_.Ya[I4] = XYZ1[2] + J*XYZ3[2]/S1;                     // 1234
                g_.Za[I4] = XYZ1[3] + J*XYZ3[3]/S1;                     // 1235
            }

            if (g_.Cp[g_.N][2] != 0) {                                  // 1237
                int II = std::abs(g_.Cp[g_.N][2]);                      // 1238
                double F3 = (g_.Cp[g_.N][2] > 0 ? 1 : -1) * g_.Sa[II];  // 1239

                int I3x = I6 - 1;                                       // 1240
                g_.Xa[I6] = g_.Xa[I3x] + F3*g_.CABG[II][1];             // 1241
                g_.Ya[I6] = g_.Ya[I3x] + F3*g_.CABG[II][2];             // 1242
                // 1243 IF I=-C%(N,2) THEN F3=-F3
                // if I == -Cp(N,2), F3 = -F3; end
                g_.Za[I6] = g_.Za[I3x] + F3*g_.CABG[II][3];             // 1244
            }
        }
        else {
            // single segment  0 pulse case
            int I1idx = N1 + 2*(I-1);           // 1247

            g_.Xa[I1idx]   = XYZ1[1];           // 1248
            g_.Ya[I1idx]   = XYZ1[2];           // 1249
            g_.Za[I1idx]   = XYZ1[3];           // 1250

            g_.Xa[I1idx+1] = XYZ2[1];           // 1252
            g_.Ya[I1idx+1] = XYZ2[2];           // 1253
            g_.Za[I1idx+1] = XYZ2[3];           // 1254
        }

    } // end FOR

    //   GEOMETRY OUTPUT
    g_.Cp = GeometryOutput(g_.N, g_.Wp, g_.NW, g_.Na, g_.Xa, g_.Ya, g_.Za, g_.A, g_.Cp);

    S.FLG = 99;

    return g_;
}
