#include "ImpedanceMatrixFactorization.hpp"

void ImpedanceMatrixFactorization(SimulationState S, GeometryData g)
{

    S.Pa.resize(50);

    // 381 X = N
    // 382 PCTN = X * (X - 1) * (X + X - 1)
    for (int K =1; K <= (g.N-1); K++)     // 383 FOR K = 1 TO N - 1
    {
        // 384 REM ----- SEARCH FOR PIVOT
        // 385 T = ZR(K, K) * ZR(K, K) + ZI(K, K) * ZI(K, K)
        double T = S.ZR[K][K]*S.ZR[K][K] + S.ZI[K][K]*S.ZI[K][K];
        int I1 = K;
        // 386 I1 = K
        for (int I = K+1; I <= g.N; I++)   // 387 FOR I = K + 1 TO N
        {
            double T1 = S.ZR[I][K]*S.ZR[I][K] + S.ZI[I][K]*S.ZI[I][K]; // 388 T1 = ZR(I, K) * ZR(I, K) + ZI(I, K) * ZI(I, K)
            if (T1 < T) continue;  // 389 IF T1 < T THEN 392
            I1 = I;     // 390 I1 = I
            T = T1;     // 391 T = T1
        }               // 392 NEXT I
        // 393 REM ----- EXCHANGE ROWS K AND I1
        if (I1 != K)    // 394 IF I1 = K THEN 403
        {
            for (int J = 1; J <= g.N; J++)  // 395 FOR J = 1 TO N
            {
                double T1 = S.ZR[K][J];         // 396 T1 = ZR(K, J)
                double T2 = S.ZI[K][J];         // 397 T2 = ZI(K, J)
                S.ZR[K][J] = S.ZR[I1][J];       // 398 ZR(K, J) = ZR(I1, J)
                S.ZI[K][J] = S.ZI[I1][J];       // 399 ZI(K, J) = ZI(I1, J)
                S.ZR[I1][J] = T1;               // 400 ZR(I1, J) = T1
                S.ZI[I1][J] = T2 ;              // 401 ZI(I1, J) = T2
            }  // 402 NEXT J
        }
        S.Pa[K] = I1;               // 403 P(K) = I1
        //   404 REM ----- SUBTRACT ROW K FROM ROWS K+1 TO N
        for (int I = K+1; I <= g.N; I++)    //   405 FOR I = K + 1 TO N
        {
            //   406 REM ----- COMPUTE MULTIPLIER L(I,K)
            //   407 T1 = (ZR(I, K) * ZR(K, K) + ZI(I, K) * ZI(K, K)) / T
            double T1 = (S.ZR[I][K]*S.ZR[K][K] + S.ZI[I][K]*S.ZI[K][K])/T;
            //   408 T2 = (ZI(I, K) * ZR(K, K) - ZR(I, K) * ZI(K, K)) / T
            double T2 = (S.ZI[I][K]*S.ZR[K][K] - S.ZR[I][K]*S.ZI[K][K])/T;
            S.ZR[I][K] = T1;        // 409 ZR(I, K) = T1
            S.ZI[I][K] = T2;        // 410 ZI(I, K) = T2
            // 411 REM ----- SUBTRACT ROW K FROM ROW I
            for (int J = K+1; J <= g.N; J++)   // 412 FOR J = K + 1 TO N
            {
                //   413 ZR(I, J) = ZR(I, J) - (ZR(K, J) * T1 - ZI(K, J) * T2)
                S.ZR[I][J] = S.ZR[I][J] - (S.ZR[K][J]*T1 - S.ZI[K][J]*T2);

                //   414 ZI(I, J) = ZI(I, J) - (ZR(K, J) * T2 + ZI(K, J) * T1)
                S.ZI[I][J] = S.ZI[I][J] - (S.ZR[K][J] * T2 + S.ZI[K][J] * T1);

            }           //   415 NEXT J
        }           //   416 NEXT I
        //   417 X = N - K
        //   418 PCT = 1 - X * (X - 1) * (X + X - 1) / PCTN
        //           419 GOSUB 1599
    }           //  420 NEXT K






}
