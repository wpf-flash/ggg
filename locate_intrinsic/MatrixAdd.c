#include <riscv_vector.h>

void MatrixAdd33(data_type A[3][3],data_type B[3][3],data_type c[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			c[i][j]=A[i][j]+B[i][j];
		}
	}
}



////////////intrinsic函数
void MatrixAdd(data_type **A, data_type **B, data_type **C, int x, int y)///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < x; i++)
    {
        int n = y;
        float *ptr_a = &A[i][0];
        float *ptr_b = &B[i][0];
        float *ptr_c = &C[i][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfadd_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(*ptr_c, vec_c, vl);
        }
    }   
}

///////////另一种二阶数组intrinsic函数??????
void MatrixAdd(data_type **A, data_type **B, data_type **C, int x, int y)///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    
        int n = x*y;
        float *ptr_a = A;// *ptr_a = &A[0][0]
        float *ptr_b = B;
        float *ptr_c = C;
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfadd_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(*ptr_c, vec_c, vl);
        } 
}
