#include "MatSolve.hpp"
#include "SimulationState.hpp"
#include "GeometryData.hpp"
#include <vector>
#include <complex>

void MatSolve(SimulationState& S, GeometryData g)
{

    S.CR.resize(50);
    S.CI.resize(50);

    // 426 REM ********** SOLVE **********
    // 427 REM ----- COMPUTE RIGHT HAND SIDE
    for (int I = 1; I <= g.N; ++I)    // 428 FOR I = 1 TO N
    {
        S.CR[I] = 0.0;      // 429 CR(I) = 0
        S.CI[I] = 0.0;      // 430 CI(I) = 0
    }  // 431 NEXT I

    for (int J = 1; J <= S.NS; ++J)     // 432 FOR J = 1 TO NS
    {
        double F2 = 1 / S.M;            // 433 F2 = 1 / M
        //   434 IF C%(E(J), 1) = -C%(E(J), 2) THEN F2 = 2 / M
        if (g.Cp[S.Ea[J]][1] == -g.Cp[S.Ea[J]][2])  F2 = 2.0/S.M;
        S.CR[S.Ea[J]] = -F2*S.Ma[J];       // 435 CR(E(J)) = F2 * M(J)
        S.CI[S.Ea[J]] = -F2*S.La[J];       //   436 CI(E(J)) = -F2 * L(J)
    }   //   437 NEXT J
    //   438 REM ----- PERMUTE EXCITATION
    for (int K = 1; K <= g.N -1; ++K)    //   439 FOR K = 1 TO N - 1
    {
        int I1 = S.Pa[K];       // 440 I1 = P(K)
        if (I1 != S.Pa[K])      // 441 IF I1 = K THEN 448
        {
            double T1 = S.CR[K];    // 442 T1 = CR(K)
            double T2 = S.CI[K];    // 443 T2 = CI(K)
            S.CR[K] = S.CR[I1];     // 444 CR(K) = CR(I1)
            S.CI[K] = S.CI[I1];     // 445 CI(K) = CI(I1)
            S.CR[I1] = T1;          // 446 CR(I1) = T1
            S.CI[I1] = T2;          // 447 CI(I1) = T2
        }
    }   // 448 NEXT K

    // 449 REM ----- FORWARD ELIMINATION
    for (int I = 2; I <= g.N; ++I)   // 450 FOR I = 2 TO N
    {
        double T1 = 0.0;    // 451 T1 = 0
        double T2 = 0.0;    // 452 T2 = 0
        for (int J = 1; J <= I-1; ++J)  // 453 FOR J = 1 TO I - 1
        {
            // 454 T1 = T1 + ZR(I, J) * CR(J) - ZI(I, J) * CI(J)
            T1 = T1 + S.ZR[I][J]*S.CR[J] - S.ZI[I][J]*S.CI[J];
            // 455 T2 = T2 + ZR(I, J) * CI(J) + ZI(I, J) * CR(J)
            T2 = T2 + S.ZR[I][J]*S.CI[J] + S.ZI[I][J]*S.CR[J];
        }   // 456 NEXT J
        S.CR[I] = S.CR[I] - T1;  // 457 CR(I) = CR(I) - T1
        S.CI[I] = S.CI[I] - T2; // 458 CI(I) = CI(I) - T2
    }   // 459 NEXT I

    // 460 REM ----- BACK SUBSTITUTION
    for (int I = g.N; I >= 1; --I)     // 461 FOR I = N TO 1 STEP -1
    {
        double T1 = 0.0;    // 462 T1 = 0
        double T2 = 0.0;    // 463 T2 = 0
        if (I != g.N)       // 464 IF I = N THEN 469
        {
            for (int J = I + 1; J <= g.N; ++J)    // 465 FOR J = I + 1 TO N
            {
                // 466 T1 = T1 + ZR(I, J) * CR(J) - ZI(I, J) * CI(J)
                T1 = T1 + S.ZR[I][J]*S.CR[J] - S.ZI[I][J]*S.CI[J];
                // 467 T2 = T2 + ZR(I, J) * CI(J) + ZI(I, J) * CR(J)
                T2 = T2 + S.ZR[I][J]*S.CI[J] + S.ZI[I][J]*S.CR[J];
            }   // 468 NEXT J
        }
        // 469 T = ZR(I, I) * ZR(I, I) + ZI(I, I) * ZI(I, I)
        double T = S.ZR[I][I] * S.ZR[I][I] + S.ZI[I][I]*S.ZI[I][I];
        T1 = S.CR[I] - T1;     // 470 T1 = CR(I) - T1
        T2 = S.CI[I] - T2;     // 471 T2 = CI(I) - T2
        // 472 CR(I) = (T1 * ZR(I, I) + T2 * ZI(I, I)) / T
        S.CR[I] = (T1*S.ZR[I][I] + T2*S.ZI[I][I])/T;
        // 473 CI(I) = (T2 * ZR(I, I) - T1 * ZI(I, I)) / T
        S.CI[I] = (T2 * S.ZR[I][I] - T1*S.ZI[I][I])/T;
    }           //   474 NEXT I

    //std::vector<std::complex<double>> CurrX;
    S.CurrX.resize(g.N + 1);

    // CurrX[1] = std::complex<double>(1.0, 2.0); // 1 + 2i

    // S.CurrX[0] =  std::complex<double>(0.0, 0.0);
    // S.CurrX[1] =  std::complex<double>(0.0010,  0.0015);
    // S.CurrX[2] =  std::complex<double>(0.0010, -0.0008);
    // S.CurrX[3] =  std::complex<double>(0.0009, -0.0022);
    // S.CurrX[4] =  std::complex<double>(0.0008, -0.0032);
    // S.CurrX[5] =  std::complex<double>(0.0006, -0.0039);
    // S.CurrX[6] =  std::complex<double>(0.0005, -0.0045);
    // S.CurrX[7] =  std::complex<double>(0.0004, -0.0045);
    // S.CurrX[8] =  std::complex<double>(0.0002, -0.0041);
    // S.CurrX[9] =  std::complex<double>(0.0001, -0.0032);
    // S.CurrX[10] = std::complex<double>(0.0000, -0.0019);

    for (int i = 1; i <= g.N; ++i)
    {
        S.CurrX[i] = std::complex<double>(S.CR[i], S.CI[i]);
    }


    S.FLG = 2; //   475 FLG = 2
}
