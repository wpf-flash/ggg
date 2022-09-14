#include <stdio.h>
#include <riscv_vector.h>

//void MatrixMul33_33(float a[3][3], float b[3][3], float res[3][3]);
void MatrixAdd33(float a[3][3], float b[3][3], float res[3][3]);///A[x][y],B[x][y]

float A[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
float B[3][3] = {{1,1,1},{1,1,1},{1,1,1}};
float C[3][3] = {0};

int main (void)
{
    MatrixAdd33(A, B, C);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f\t", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/*
void MatrixMul33_33(float a[3][3], float b[3][3], float res[3][3])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];
            int n = 3;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}
*/

void MatrixAdd33(float A[3][3],float B[3][3],float c[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			c[i][j]=A[i][j]+B[i][j];
		}
	}
}

/*
void MatrixAdd33(float A[3][3], float B[3][3], float C[3][3])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    
        int n = 3*3;
        float *ptr_a = &A[0][0];// *ptr_a = &A[0][0]
        float *ptr_b = &B[0][0];
        float *ptr_c = &C[0][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfadd_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(ptr_c, vec_c, vl);
        } 
}
*/