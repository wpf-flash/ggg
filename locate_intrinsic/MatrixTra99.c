#include <riscv_vector.h>


void MatrixTra99(data_type a[9][9],data_type b[9][9])
{
	for(char i=0;i<9;i++)
		for(char j=0;j<9;j++)
		b[j][i]=a[i][j];
}

////////////intrinsic函数
void MatrixTra99(data_type a[9][9],data_type b[9][9])///a[x][y], b[y][x]
{
	for(int i=0; i<9; i++)
    {
        int n = 9;
        float *ptr_a = &A[i][0];
        float *ptr_b = &B[0][i];
		for(size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);

            vfloat32m1_t vec_b = vmv_v_v_f32m1(vec_a, vl);
            vse32_v_f32m1(ptr_b, vec_b, vl);
        }
    }
}