#include "SimulationState.hpp"

void ExcitationInput(SimulationState& S, int N)

// global MP P0 FLG Ea La Ma NS
{
    S.Ea.resize(2);
    S.La.resize(2);
    S.Ma.resize(2);


    // % 1429 REM ********** EXCITATION INPUT **********
    // while 1
    //     NS = 1;
    //     if NS < 1, NS = 1; end
    //     if NS <= MP, break, end
    //     fprintf('NO. OF SOURCES EXCEEDS DIMENSION ...\n')
    // end
    // %
    // for I = 1:NS
    //     while 1
    // res = [1,1,0] PULSE NO., VOLTAGE MAGNITUDE, PHASE (DEGREES) [E V P]

    int EM = 1;  //res(1);
    double VM = 1.0;    //res(2);
    double VP = 0.0; //res(3);


    //if EM <= N, break, end
    //         fprintf('PULSE NUMBER EXCEEDS NUMBER OF PULSES...\n')
    //     end
    //     %
    S.NS = 1;
    S.Ea[1] = EM;
    S.La[1] = VM*std::cos(VP*S.P0);
    S.Ma[1] = VM*std::sin(VP*S.P0);
    // end
    if (S.FLG == 2) S.FLG = 1;

    return;
}
