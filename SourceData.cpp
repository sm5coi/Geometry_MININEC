#include "SourceData.hpp"
#include "GeometryData.hpp"
#include <complex>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

void SourceData(SimulationState& S, GeometryData g)
{
    // global NS Ea Ma La BSd PWR fidPsi
    // 476 REM ********** SOURCE DATA **********

    cout << endl << S.BSd << " SOURCE DATA " << S.BSd << endl;

    double PWR = 0;            // 479
    for (int I = 1; I <= S.NS; I++)
    {
        double cR = real(S.CurrX[S.Ea[I]]);
        double cI = imag(S.CurrX[S.Ea[I]]);
        double T = cR*cR + cI*cI;
        double T1 = (S.La[I]*cR + S.Ma[I]*cI)/T;
        double T2 = (S.Ma[I]*cR - S.La[I]*cI)/T;
        double O2 = (S.La[I]*cR + S.Ma[I]*cI)/2;
        PWR = PWR + O2;

        cout << "PULSE " << S.Ea[I] << " VOLTAGE = "
             << std::fixed << std::setprecision(1) << S.La[I]
             << " , " << S.Ma[I] <<"j" << endl; // Ea(I), La(I),Ma(I));

        cout << "CURRENT = " << std::scientific << std::setprecision(5) << cR
             << " , " << cI << "j" << endl;

        cout << "IMPEDANCE = " << T1 << " , " << T2 << "j" << endl;

        cout << "POWER = " << std::fixed << std::setprecision(8) << O2 << " WATTS" << endl;

        cout << std::setprecision(5);
    }

    // end
    // if NS > 1
    // fprintf('\n TOTAL POWER = %e WATTS\n', PWR);
    // fprintf( fidPsi, '\n TOTAL POWER = %e WATTS\n', PWR);
    // end
}
