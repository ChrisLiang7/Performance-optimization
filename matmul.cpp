#include <stdlib.h>
#include "matmul.h"

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A 
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

/* You'll need to modify this function such that matrix B is accessed
 * correctly once you change the memory layout to column-major. */
void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{
  
  //original code
  for (unsigned int i = 0; i < hA; ++i)
    for (unsigned int j = 0; j < wB; ++j) {
      double sum = 0;
      for (unsigned int k = 0; k < wA; ++k) {
        double a = A[i * wA + k];
        double b = B[k * wB + j];
        sum += a * b;
      }
      C[i * wB + j] = (float)sum;
    }
/*
  //Loop Unrolling only:
  //Unroll each of the outer loops in the matmul function by a factor of two, 
  //a factor of two, such that the inner-most loop is computing four values of Matrix C on 
  //each iteration: C[i][j], C[i][j+1], C[i+1][j], and C[i+1][j+1].
    for (unsigned int i = 0; i < hA; i += 2)
      for (unsigned int j = 0; j < wB; j += 2) {
        double sum, sum1, sum2, sum3; 
        sum = sum1 = sum2 = sum3 = 0;
        for (unsigned int k = 0; k < wA; ++k) {
          double a, a1, b, b1;
          a = A[i * wA + k];
          a1 = A[(i + 1) * wA + k];
          b = B[k * wB + j];
          b1 = B[k * wB + (j + 1)];
          sum += a * b; //C[i][j]
          sum1 += a * b1; //C[i][j+1]
          sum2 += a1 * b; //C[i+1][j]
          sum3 += a1 * b1; //C[i+1][j+1]
        }
        C[i * wB + j] = (float)sum;
        C[i * wB + (j+1)] = (float)sum1;
        C[(i+1) * wB + j] = (float)sum2;
        C[(i+1) * wB + (j+1)] = (float)sum3;
      }
*/
/* 
  //column-major only
  for (unsigned int i = 0; i < hA; ++i)
    for (unsigned int j = 0; j < hA; ++j) {
      double sum = 0;
      for (unsigned int k = 0; k < wA; ++k) {
        double a = A[i * wA + k];
        double b = B[j * wB + k];
        sum += a * b;
      }
      C[i * wB + j] = (float)sum;
    }
  */


  //column and unrolling
  for (unsigned int i = 0; i < hA; i += 2)
      for (unsigned int j = 0; j < hA; j += 2) {
        double sum, sum1, sum2, sum3; 
        sum = sum1 = sum2 = sum3 = 0;
        for (unsigned int k = 0; k < wA; ++k) {
          double a, a1, b, b1;
          a = A[i * wA + k];
          a1 = A[(i + 1) * wA + k];
          b = B[j * wB + k];
          b1 = B[(j+1) * wB + k];
          sum += a * b; //C[i][j]
          sum1 += a * b1; //C[i][j+1]
          sum2 += a1 * b; //C[i+1][j]
          sum3 += a1 * b1; //C[i+1][j+1]
        }
        C[i * wB + j] = (float)sum;   
        C[i * wB + (j+1)] = (float)sum1;
        C[(i+1) * wB + j] = (float)sum2;
        C[(i+1) * wB + (j+1)] = (float)sum3;
      }
}

// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;

  M.elements = (float*) malloc(size*sizeof(float));

  /* This is a row-major allocation and initialization.
   * You need to modify this function which is only called
   * for Matrix B such that a column-major ordering is
   * performed.
   * Hint: a nested for-loop is probably needed. */
  /*
  //row-major ordering
  for(unsigned int i = 0; i < M.height * M.width; i++)
  {
    M.elements[i] = (rand() / (float)RAND_MAX);
  }
  return M;
  */

    
  //column-major ordering 
  for(unsigned int i = 0; i < M.height; i++)
  {
    for(unsigned int j = 0; j < M.width; j++)
    {
      M.elements[i+j * M.width] = (rand() / (float)RAND_MAX);
    }
  }
  return M;
   
}	

