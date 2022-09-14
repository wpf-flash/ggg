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
void MatrixMul33_33(data_type a[3][3], data_type b[3][3], data_type res[3][3])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 3;
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


