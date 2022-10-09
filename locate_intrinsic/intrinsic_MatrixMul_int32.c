#include <riscv_vector.h>
#include <stdio.h>
#include <stdlib.h>

#define MLEN 3
#define KLEN 3
#define NLEN 3

void sgemm_vec_33_33(size_t size_m, size_t size_n, size_t size_k,
               const int *a, // m * k matrix
               size_t column_a,
               const int *b, // k * n matrix
               size_t column_b,
               int *c, // m * n matrix
               size_t column_c);
//void MatrixAdd33(int A[3][2], int B[3][2], int C[3][2]);///A[x][y],B[x][y]
void MatrixMul33_33(int a[3][3],int b[3][3],int res[3][3]);
void intrin_MatrixMul33_33(int a[3][3], int b[3][3], int res[3][3]);//a[x][z], b[z][y]

int a[9]={1,2,3,
          1,2,3,
          1,2,3};

int b[9]={1,1,1,
          1,1,1,
          1,1,1};

int c[9]={0};


int aa[3][3]={{1,2,3},{1,2,3},{1,2,3}};
int bb[3][3]={{1,1,1},{1,1,1},{1,1,1}};
int cc[3][3]={0};


int main (void) 
{ 
    sgemm_vec_33_33(MLEN, NLEN, KLEN, a, KLEN, b, NLEN, c, NLEN);
    //MatrixAdd33(aa,bb,cc);
    MatrixMul33_33(aa,bb,cc);
    intrin_MatrixMul33_33(aa,bb,cc);
    for (int i = 0; i < 9; i++)
      {   
        if(i%3==0){
          printf("\n");
        }        
        printf("%d\t", c[i]);
      }
    printf("\n\n");
    for (int i = 0; i < 3; i++)
    {   
      for (int j = 0; j < 3; j++)
      {
        printf("%d\t", cc[i][j]);
      }
      printf("\n");
    }

    return 0;
}

void sgemm_vec_33_33(size_t size_m, size_t size_n, size_t size_k,
               const int *a, // m * k matrix
               size_t column_a, //k
               const int *b, // k * n matrix
               size_t column_b, //n
               int *c, // m * n matrix
               size_t column_c) //n
{
  size_t vl;
  for (size_t m = 0; m < size_m; ++m) 
  {
    const int *b_n_ptr = b;
    int *c_n_ptr = c;
    for (size_t c_n_count = size_n; c_n_count>0; c_n_count -= vl) 
    {
      vl = vsetvl_e32m1(c_n_count);
      const int *a_k_ptr = a;
      const int *b_k_ptr = b_n_ptr;
      vint32m1_t acc = vle32_v_i32m1(c_n_ptr, vl);
      for (size_t k = 0; k < size_k; ++k) //a[0-lda]
      {
        vint32m1_t b_n_data = vle32_v_i32m1(b_k_ptr, vl);
        acc = vmacc_vx_i32m1(acc, *a_k_ptr, b_n_data, vl);//a[0] * b[0-ldb]//vint32m1_t vmacc_vx_i32m1 (vint32m1_t vd, int32_t rs1, vint32m1_t vs2, size_t vl);
        
        b_k_ptr += column_b;
        a_k_ptr++;
      }
      vse32_v_i32m1(c_n_ptr, acc, vl);
      c_n_ptr += vl;
      b_n_ptr += vl;
    }
    a += column_a;
    c += column_c;
  }
}

//void MatrixAdd33(int A[3][3], int B[3][3], int C[3][3])///A[x][y],B[x][y]
//{
//    size_t vlmax = vsetvlmax_e32m1();
//    
//        int n = 3*3;
//        int *ptr_a = &A[0][0];// *ptr_a = &A[0][0]
//        int *ptr_b = &B[0][0];
//        int *ptr_c = &C[0][0];
//        vint32m1_t vec_c = vmv_v_x_i32m1(0, vlmax);
//        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
//        {
//            vl = vsetvl_e32m1(n);
//            vint32m1_t vec_a = vle32_v_i32m1(ptr_a, vl);
//            vint32m1_t vec_b = vle32_v_i32m1(ptr_b, vl);
//
//            vec_c = vadd_vv_i32m1(vec_a, vec_b, vl);
//            vse32_v_i32m1(ptr_c, vec_c, vl);
//        } 
//}

void MatrixMul33_33(int a[3][3],int b[3][3],int res[3][3])
{
  // Iterate over the rows of the A matrix
   Row: for(int i = 0; i < 3; i++) {
      // Iterate over the columns of the B matrix
      Col: for(int j = 0; j < 3; j++) {
         res[i][j] = 0;
         // Do the inner product of a row of A and col of B
         Product: for(int k = 0; k < 3; k++) {
            res[i][j] += a[i][k] * b[k][j];
         }
      }
   }
}

void intrin_MatrixMul33_33(int a[3][3], int b[3][3], int res[3][3])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int *ptr_a = &a[i][0];
            int *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 3;
            vint32m1_t vec_s = vmv_v_x_i32m1(0, vlmax);
            vint32m1_t vec_zero = vmv_v_x_i32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vint32m1_t vec_a = vle32_v_i32m1(ptr_a, vl);
                vint32m1_t vec_b = vle32_v_i32m1(ptr_b, vl);

                vec_s = vmacc_vv_i32m1(vec_s, vec_a, vec_b, vl);
            }

            vint32m1_t vec_sum;
            vec_sum = vredsum_vs_i32m1_i32m1(vec_zero, vec_s, vec_zero, vlmax);
            int sum = vmv_x_s_i32m1_i32(vec_sum);
            res[i][j] = sum;
        }
    }
}