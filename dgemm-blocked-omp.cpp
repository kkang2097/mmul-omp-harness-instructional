#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include "likwid-stuff.h"

const char* dgemm_desc = "Blocked dgemm, OpenMP-enabled";


/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are n-by-n matrices stored in column-major format.
 * On exit, A and B maintain their input values. */
void square_dgemm_blocked(int n, int block_size, double* A, double* B, double* C)
{
   // insert your code here: implementation of blocked matrix multiply with copy optimization and OpenMP parallelism enabled

   // be sure to include LIKWID_MARKER_START(MY_MARKER_REGION_NAME) inside the block of parallel code,
   // but before your matrix multiply code, and then include LIKWID_MARKER_STOP(MY_MARKER_REGION_NAME)
   // after the matrix multiply code but before the end of the parallel code block.

   std::cout << "Insert your blocked matrix multiply with copy optimization, openmp-parallel edition here " << std::endl;

   #pragma omp parallel
    {
      LIKWID_MARKER_START(MY_MARKER_REGION_NAME)

      #pragma omp parallel for
         //Then add our triple for-loop
         for (int ii = 0; ii < n; ii+= block_size){
           for(int jj = 0; jj < n; jj+= block_size){
             //C[i*n + j] = 0;
             for(int kk = 0; kk < n; kk+= block_size){
               //
              //Row major order:
              //prod[i][j] += A[i][k] + B[k][j]
              //Column major order:
              //prod[i][j] += A[k][j] + B[i][k]
                //Block multiply
                //info src: https://netlib.org/utk/papers/autoblock/node2.html
                for (int i = ii; i < ii+block_size; i++){
                  for(int j = jj; j < jj+block_size; j++){
                    //C[i*n + j] = 0;
                    for(int k = kk; k < kk+block_size; k++){
                      C[i*n + j] = C[i*n + j] + A[k*n + j] * B[i*n + k];
                    }}}
             }}}
      LIKWID_MARKER_STOP(MY_MARKER_REGION_NAME)
    }
}
