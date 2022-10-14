#include <iostream>
#include <omp.h>
#include "likwid-stuff.h"
#include <vector>
#include <algorithm>
#include <random>
#include <omp.h>
#include <unistd.h>

const char* dgemm_desc = "Basic implementation, OpenMP-enabled, three-loop dgemm.";

/*
 * This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are n-by-n matrices stored in column-major format.
 * On exit, A and B maintain their input values.
 */
void square_dgemm(int n, double* A, double* B, double* C)
{
   // insert your code here: implementation of basic matrix multiply with OpenMP parallelism enabled

   // be sure to include LIKWID_MARKER_START(MY_MARKER_REGION_NAME) inside the block of parallel code,
   // but before your matrix multiply code, and then include LIKWID_MARKER_STOP(MY_MARKER_REGION_NAME)
   // after the matrix multiply code but before the end of the parallel code block.
   int sleep_duration_sec = 2;

   std::cout << "Insert your basic matrix multiply, openmp-parallel edition here " << std::endl;

   #pragma omp parallel
    {
      #ifdef LIKWID_PERFMON
            LIKWID_MARKER_START(MY_MARKER_REGION_NAME);
      #endif

      #pragma omp parallel for collapse(2)
      //Then add our triple for-loop
       for (int i = 0; i < n; i++){
         for(int j = 0; j < n; j++){
           //C[i*n + j] = 0;
           for(int k = 0; k < n; k++){
             //
            //Row major order:
            //prod[i][j] += A[i][k] + B[k][j]
            //Column major order:
            //prod[i][j] += A[k][j] + B[i][k]
            #pragma omp critical
            C[i*n + j] = C[i*n + j] + A[k*n + j] * B[i*n + k];
           }
         }
       }
       #ifdef LIKWID_PERFMON
             LIKWID_MARKER_STOP(MY_MARKER_REGION_NAME);
       #endif
    }

}
