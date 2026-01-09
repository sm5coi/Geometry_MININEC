#include "PrintCurrents.hpp"
#include "ImpedanceMatrixCalculation.hpp"
#include "SimulationState.hpp"
#include "GeometryData.hpp"
#include <iostream>
#include <complex>
#include <iomanip>

// // helper = direct BASIC ports
static void PrintOutD(std::ostream& os, int idx, std::complex<double> I)
{
    os << std::setw(4) << idx
       << std::setw(15) << std::scientific << I.real()
       << std::setw(15) << I.imag()
       << std::setw(15) << std::abs(I) << "  " << std::fixed
       << std::setw(12) << (std::arg(I) * 180.0 / M_PI)
       << "\n";
}

static void PrintOutS(std::ostream& os, char tag, std::complex<double> I)
{
    os << "   " << tag
       << std::setw(15) << std::scientific << I.real()
       << std::setw(15) << I.imag()
       << std::setw(15) << std::abs(I) << "  " << std::fixed
       << std::setw(12) << (std::arg(I) * 180.0 / M_PI)
       << "\n";
}


static void fAlfa_2( int j1aK, int N2, std::complex<double> Cx,std::complex<double>IJu, char Is)
{
    //global J1a dForm cForm fidPsi
    // PrintOutD(std::cout, seg, S.CurrX[seg]);

    PrintOutD(std::cout, N2, Cx);
    if (!(j1aK == 1)) PrintOutS(std::cout, Is, IJu);
}

// // 572 / 607 logic collapsed into helper
//static std::pair<std::complex<double>, char>
void SortJunction(int Ep, int I, int C, int K, const SimulationState& S, const GeometryData g,
             std::complex<double>& IJu, char& Is)
{
    // BASIC: I$ = "E" or "J"
    Is = 'E';
    int CO;
    int CT;
    int L1;
    int L2;
    int L3;
    int L4;

    // Start with current at I (BASIC CR(I),CI(I))
    IJu = std::complex<double> (0.0,0.0);

    if (!((C == K) || (C == 0)))
    {
        Is = 'J';
        IJu = S.CurrX[I];
    }
    // 579 REM ----- CHECK FOR OTHER OVERLAPPING WIRES
    // loop wires 1..NW
    for (int J = 1; J <= g.NW; ++J)     // 588
    {
        if (J == K) continue;           // 581

        L1 = g.Na[J][1];            // 582
        L2 = g.Na[J][2];            // 583

        if (Ep == 2)                    // 584
        {
            CO = g.Cp[L2][2];       // 590
            CT = g.Cp[L1][1];       // 591
            L3 = L2;                // 592
            L4 = L1;                // 593
        }
        else
        {
            CO = g.Cp[L1][1];       // 585
            CT = g.Cp[L2][2];       // 586
            L3 = L1;                // 587
            L4 = L2;                // 588
        }

        if (CO == -K) {             // 594
            IJu = IJu - S.CurrX[L3];// 596, 597
            Is = 'J';               // 598
        }
        if (!(CT == K))             // 599
        {
            continue;               // 600
        }
        else
        {
            IJu = IJu + S.CurrX[L4];// 601, 602
            Is = 'J';               // 603
        }
    }                               // 604
}

void PrintCurrents(SimulationState& S, const GeometryData g)
{
    std::cout << "Entry of PrintCurrents" << std::endl;

    std::complex<double>Iju;
    char Is;

    ImpedanceMatrixCalculation(S,g);    // 497

    char Sflag = 'N';                   // 498

    std::cout << "\n\n************ CURRENT DATA ************\n";    // 499, 500

    for (int K = 1; K <= g.NW; ++K)     // 501
    {
        if (Sflag != 'Y')               // 502
        {
            std::cout << "\nWIRE NO. " << K << "\n";                                            // 504
            std::cout << "PULSE        REAL         IMAGINARY     MAGNITUDE     PHASE\n";       // 505
            std::cout << " NO.         (AMPS)       (AMPS)        (AMPS)        (DEGREES)\n";   // 506
        }

        int N1 = g.Na[K][1];                        // 507
        int N2 = g.Na[K][2];                        // 508
        int I = N1;                                 // 509

        int C = g.Cp[I][1];                         // 510
        if (N1 == 0 && N2 == 0) C = K;              // 511

        // BASIC 512-514 ground logic
        if (S.G != 1 && g.J1a[K] == -1 && N1 > N2)  //
            N2 = N1;                                // 513


        if (!(g.J1a[K] == -1) || S.G == 1)
        {
            int Ep = 1;                             // 515
            SortJunction(Ep, I, C, K, S, g, Iju, Is);   // 516

            PrintOutS(std::cout, Is, Iju);

            if (!(N1 == 0))                         // 522
            {
                if (!(C == K))                         // 523
                {
                    if (Is == 'J') N1 = N1 +1;                           // 524
                }

                for (int seg = N1; seg <= N2 - 1; ++seg)        // 525
                    PrintOutD(std::cout, seg, S.CurrX[seg]);
            }
        }
        else
        {
            for (int seg = N1; seg <= N2 - 1; ++seg)
                PrintOutD(std::cout, seg, S.CurrX[seg]);
        }

        I = N2;                                     // 532
        C = g.Cp[I][2];                             // 533
        if (N1 == 0 && N2 == 0) C = K;              // 534

        if (S.G == 1 || !(g.J1a[K] == 1))           // 535 & 536
        {
            int Ep = 2;                             // 537
            SortJunction(Ep, I, C, K, S, g, Iju, Is);   // 538

            if ((N1 == 0 && N2 == 0) || (N1 > N2))  // 539 & 540
            {
                PrintOutS(std::cout, Is, Iju);
            }
            else
            {
                if (C == K)                         // 541
                {
                    fAlfa_2(g.J1a[K], N2, S.CurrX[N2], Iju, Is); //
                }
                else
                {
                    if (Is == 'J')      // 542
                    {
                        PrintOutS(std::cout, Is, Iju);  // 551
                    }
                    else
                    {
                        fAlfa_2(g.J1a[K], N2, S.CurrX[N2], Iju, Is);
                    }
                }
            }
        }
        else if (g.J1a[K] == 1)
        {
            fAlfa_2(g.J1a[K], N2, S.CurrX[N2], Iju, Is);
        }

    }  // 555 (NEXT K)

    std::cout << "Exit of PrintCurrents" << std::endl;
}


