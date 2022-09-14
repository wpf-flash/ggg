#include <riscv_vector.h>

void MatrixLiner3(data_type A[3][3],data_type k,data_type res[3][3])
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			res[i][j]=A[i][j]*k;
}

///////////intrinsic函数
void MatrixLiner3(data_type A[3][3], data_type k, data_type res[3][3])//A[x][y]
{
    for(int i=0; i<3; i++)
     {
        int n = 3;
        float *ptr_a = &A[i][0];
        float *ptr_res = &res[i][0];
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_res += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);

            vfloat32m1_t vec_res = vfmul_vf_f32m1(vec_a, k, vl);
            vse32_v_f32m1(*ptr_res, vec_res, vl);
        }
    }   
}
