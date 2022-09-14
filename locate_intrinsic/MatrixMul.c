#include <riscv_vector.h>

//////////////原函数
void MatrixMul33_33(data_type a[3][3],data_type b[3][3],data_type res[3][3])
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


//////////////intrinsic函数
void MatrixMul(data_type **a, data_type **b, data_type **res, int x, int y, int z)//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];
            int n = z;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(*ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(*ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}


