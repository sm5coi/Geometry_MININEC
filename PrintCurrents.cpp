#include "PrintCurrents.hpp"
// #include "ImpedanceMatrixCalculation.hpp"
#include "SimulationState.hpp"
#include "GeometryData.hpp"
#include <iostream>
#include <complex>
#include <iomanip>
// #include <cmath>
// #include <string>

/*
#include "PrintCurrents.hpp"
#include "ImpedanceMatrixCalculation.hpp"
#include "SimulationState.hpp"
#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>

static std::pair<std::complex<double>, char>
SortJunctionCurrents(const SimulationState& S, int Ep, int I, int C, int K)
{
    char Is = 'E';
    std::complex<double> IJu = 0;

    // if pulse not directly connected
    if (!(C == K || C == 0))
    {
        Is = 'J';
        IJu = S.CurrX[I-1];
    }

    for (int J = 1; J <= S.N; ++J)
    {
        if (J == K) continue;

        int L1 = S.J2a[J-1][0];
        int L2 = S.J2a[J-1][1];

        int CO = (Ep == 2) ? S.Cp[L2-1][1] : S.Cp[L1-1][0];
        int CT = (Ep == 2) ? S.Cp[L1-1][0] : S.Cp[L2-1][1];

        int L3 = (Ep == 2) ? L2 : L1;
        int L4 = (Ep == 2) ? L1 : L2;

        if (CO == -K)
        {
            IJu -= S.CurrX[L3-1];
            Is = 'J';
        }
        if (CT == K)
        {
            IJu += S.CurrX[L4-1];
            Is = 'J';
        }
    }
    return {IJu, Is};
}


static void PrintOutD(std::ostream &os, int i, std::complex<double> Cx)
{
    os << std::setw(3) << i
       << std::setw(15) << std::scientific << std::setprecision(6) << Cx.real()
       << std::setw(15) << Cx.imag()
       << std::setw(15) << std::abs(Cx)
       << std::setw(12) << (std::arg(Cx) * 180.0 / M_PI)
       << "\n";
}


static void PrintOutS(std::ostream &os, char s, std::complex<double> Cx)
{
    os << "  " << s
       << std::setw(15) << std::scientific << std::setprecision(6) << Cx.real()
       << std::setw(15) << Cx.imag()
       << std::setw(15) << std::abs(Cx)
       << std::setw(12) << (std::arg(Cx) * 180.0 / M_PI)
       << "\n";
}


void PrintCurrents(SimulationState& S)
{
    // compute impedance + currents
    ImpedanceMatrixCalculation(S);

    std::cout << "\n******************** CURRENT DATA ********************\n";

    for (int K = 1; K <= S.N; ++K)
    {
        std::cout << "\nWIRE NO. " << K << "\n";
        std::cout << "PULSE         REAL          IMAGINARY     MAGNITUDE     PHASE\n";
        std::cout << " NO.          (AMPS)        (AMPS)        (AMPS)        (DEGREES)\n";

        int N1 = S.J2a[K-1][0];
        int N2 = S.J2a[K-1][1];
        int I  = N1;

        int C = S.Cp[I-1][0];
        if (N1 == 0 && N2 == 0)
            C = K;

        // first junction
        {
            int Ep = 1;
            auto[currJ, Is] = SortJunctionCurrents(S, Ep, I, C, K);
            PrintOutS(std::cout, Is, currJ);
        }

        // print interior segments
        for (int seg = N1; seg <= N2 - 1; ++seg)
            PrintOutD(std::cout, seg, S.CurrX[seg-1]);

        // second junction
        {
            I = N2;
            C = S.Cp[I-1][1];
            int Ep = 2;
            auto[currJ, Is] = SortJunctionCurrents(S, Ep, I, C, K);
            PrintOutS(std::cout, Is, currJ);
        }
    }
}
*/

#include "PrintCurrents.hpp"
// #include "ImpedanceMatrixCalculation.hpp"
#include "SimulationState.hpp"
#include <iostream>
// #include <iomanip>
// #include <cmath>
// #include <string>

// // helper = direct BASIC ports
static void PrintOutD(std::ostream& os, int idx, std::complex<double> I)
{
    os << std::setw(4) << idx
       << std::setw(15) << std::scientific << I.real()
       << std::setw(15) << I.imag()
       << std::setw(15) << std::abs(I)
       << std::setw(12) << (std::arg(I) * 180.0 / M_PI)
       << "\n";
}

static void PrintOutS(std::ostream& os, char tag, std::complex<double> I)
{
    os << "  " << tag
       << std::setw(15) << std::scientific << I.real()
       << std::setw(15) << I.imag()
       << std::setw(15) << std::abs(I)
       << std::setw(12) << (std::arg(I) * 180.0 / M_PI)
       << "\n";
}

// // 572 / 607 logic collapsed into helper
static std::pair<std::complex<double>, char>
SortJunction(int Ep, int I, int C, int K, const SimulationState& S, const GeometryData g)
{
    // BASIC: I$ = "E" or "J"
    char Is = 'E';

    // Start with current at I (BASIC CR(I),CI(I))
    std::complex<double> IJu = S.CurrX[I];

    // loop wires 1..NW
    for (int J = 1; J <= g.NW; ++J)
    {
        if (J == K) continue;

        int L1 = g.Na[J][1];
        int L2 = g.Na[J][2];

        int CO = (Ep == 2) ? g.Cp[L2][2] : g.Cp[L1][1];
        int CT = (Ep == 2) ? g.Cp[L1][1] : g.Cp[L2][2];

        if (CO == -K) {
            IJu -= S.CurrX[(Ep == 2) ? L2 : L1];
            Is = 'J';
        }
        if (CT == K) {
            IJu += S.CurrX[(Ep == 2) ? L1 : L2];
            Is = 'J';
        }
    }

    // if C != K, this is a junction
    if (!(C == K || C == 0))
        Is = 'J';

    return {IJu, Is};
}

void PrintCurrents(SimulationState& S, const GeometryData g)
{
    std::cout << "Entry of PrintCurrents" << std::endl;
    // BASIC line 497
    // compute impedances + currents
    // ImpedanceMatrixCalculation(S);
    //std::vector<std::complex<double>> CurrX;
    S.CurrX.resize(11);

    // CurrX[1] = std::complex<double>(1.0, 2.0); // 1 + 2i

    S.CurrX[0] =  std::complex<double>(0.0, 0.0);
    S.CurrX[1] =  std::complex<double>(0.0010,  0.0015);
    S.CurrX[2] =  std::complex<double>(0.0010, -0.0008);
    S.CurrX[3] =  std::complex<double>(0.0009, -0.0022);
    S.CurrX[4] =  std::complex<double>(0.0008, -0.0032);
    S.CurrX[5] =  std::complex<double>(0.0006, -0.0039);
    S.CurrX[6] =  std::complex<double>(0.0005, -0.0045);
    S.CurrX[7] =  std::complex<double>(0.0004, -0.0045);
    S.CurrX[8] =  std::complex<double>(0.0002, -0.0041);
    S.CurrX[9] =  std::complex<double>(0.0001, -0.0032);
    S.CurrX[10] = std::complex<double>(0.0000, -0.0019);

    // BASIC line 498
    char Sflag = 'N';

    std::cout << "\n\n************ CURRENT DATA ************\n";

    for (int K = 1; K <= g.NW; ++K)
    {
        if (Sflag != 'Y')
        {
            std::cout << "\nWIRE NO. " << K << "\n";
            std::cout << "PULSE        REAL         IMAGINARY     MAGNITUDE     PHASE\n";
            std::cout << " NO.         (AMPS)       (AMPS)        (AMPS)        (DEGREES)\n";
        }

        int N1 = g.Na[K][1];
        int N2 = g.Na[K][2];
        int I = N1;

        int C = g.Cp[I][1];
        if (N1 == 0 && N2 == 0) C = K;

        // BASIC 512-514 ground logic
        if (S.G != 1 && g.J1a[K] == -1 && N1 > N2)
            N2 = N1;


        if (!(g.J1a[K] == -1) || S.G == 1)
        {
            int Ep = 1;
            auto [Iju, Is] = SortJunction(Ep, I, C, K, S, g);

            PrintOutS(std::cout, Is, Iju);

            if (!(N1 == 0))
            {
                if (C == K)
                {
                    // nothing
                }
                else if (Is == 'J')
                {
                    N1++;
                }

                for (int seg = N1; seg <= N2 - 1; ++seg)
                    PrintOutD(std::cout, seg, S.CurrX[seg]);
            }
        }
        else
        {
            for (int seg = N1; seg <= N2 - 1; ++seg)
                PrintOutD(std::cout, seg, S.CurrX[seg]);
        }

        I = N2;
        C = g.Cp[I][2];
        if (N1 == 0 && N2 == 0) C = K;

        if (S.G == 1 || !(g.J1a[K] == 1))
        {
            int Ep = 2;
            auto [Iju, Is] = SortJunction(Ep, I, C, K, S, g);

            if ((N1 == 0 && N2 == 0) || (N1 > N2))
            {
                PrintOutS(std::cout, Is, Iju);
            }
            else
            {
                if (C == K)
                {
                    PrintOutD(std::cout, N2, S.CurrX[N2]);
                    PrintOutS(std::cout, Is, Iju);
                }
                else if (Is == 'J')
                {
                    PrintOutS(std::cout, Is, Iju);
                }
                else
                {
                    PrintOutD(std::cout, N2, S.CurrX[N2]);
                    PrintOutS(std::cout, Is, Iju);
                }
            }
        }
        else
        {
            PrintOutD(std::cout, N2, S.CurrX[N2]);
        }
    }
    std::cout << "Exit of PrintCurrents" << std::endl;
}
