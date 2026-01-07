#include "SourceData.hpp"
#include "GeometryData.hpp"
#include <complex>
#include <vector>
#include <iostream>

using namespace std;

void SourceData(SimulationState& S, GeometryData g)
{
    // global NS Ea Ma La BSd PWR fidPsi
    // 476 REM ********** SOURCE DATA **********
    // fprintf('\n%s SOURCE DATA %s\n', BSd, BSd);
    cout << endl << S.BSd << " SOURCE DATA " << S.BSd << endl;

    // fprintf( fidPsi, '\n%s SOURCE DATA  %s\n', BSd, BSd);


    double PWR = 0;            // 479
    for (int I = 1; I <= S.NS; I++)
    {
    // cR = real(CurrX(Ea(I)));
    // cI = imag(CurrX(Ea(I)));
    // T = cR*cR + cI*cI;
    // T1 = (La(I)*cR + Ma(I)*cI)/T;
    // T2 = (Ma(I)*cR - La(I)*cI)/T;
    // O2 = (La(I)*cR+Ma(I)*cI)/2;
    // PWR = PWR + O2;
    // fprintf('PULSE %d VOLTAGE = %5.1f%+5.1fj\n', Ea(I), La(I),Ma(I));
    // fprintf( fidPsi, 'PULSE %d VOLTAGE = %5.1f%+5.1fj\n', Ea(I), La(I),Ma(I));
    // fprintf('CURRENT = (%e %+ej)\n', cR, cI);
    // fprintf( fidPsi, 'CURRENT = (%e %+ej)\n', cR, cI);
    // fprintf('IMPEDANCE = (%e %+ej)\n',T1, T2);
    // fprintf( fidPsi, 'IMPEDANCE = (%e %+ej)\n',T1, T2);
    // fprintf('POWER = %e WATTS\n\n', O2);
    // fprintf( fidPsi, 'POWER = %e WATTS\n\n', O2);
    // end
    // if NS > 1
    // fprintf('\n TOTAL POWER = %e WATTS\n', PWR);
    // fprintf( fidPsi, '\n TOTAL POWER = %e WATTS\n', PWR);
    // end
    }
    return;
}




    // // init b-vector: size N
    // S.b.assign(g.N, std::complex<double>(0.0, 0.0));

    // // ---- MININEC DEFAULT EXCITATION ----
    // // BASIC places excitation on the center of wire 1
    // // MATLAB version does same if EX not specified

    // if (g.N == 0)
    // {
    //     std::cout << "SourceData ERROR: N=0, no segments.\n";
    //     return;
    // }

    // // pick a default excitation segment:
    // // choose middle segment of wire 1

    // int seg_start = g.Na[1][0];
    // int seg_stop  = g.Na[1][1];

    // int excite_idx = 0;

    // if (seg_start > 0 && seg_stop >= seg_start)
    //     excite_idx = (seg_start + seg_stop) / 2 - 1;

    // // bounds
    // if (excite_idx < 0 || excite_idx >= g.N)
    //     excite_idx = 0;


    // if (excite_idx < 0 || excite_idx >= g.N)
    //     excite_idx = 0;

    // // set unit voltage
    // S.b[excite_idx] = std::complex<double>(1.0, 0.0);

    // //S.ExciteIndex = excite_idx;

    // std::cout << "SourceData: excitation applied at segment "
    //           << (excite_idx + 1) << "\n";

