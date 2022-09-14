#include <riscv_vector.h>


void MatrixEqu33(data_type a[3][3],data_type b[3][3])
{
	for(char i=0;i<3;i++)
		for(char j=0;j<3;j++)
			b[i][j]=a[i][j];
}



///////////intrinsic函数
void MatrixEqu33(data_type a[3][3], data_type b[3][3])//A[x][y], B[x][y]
{
    for(int i=0; i<3; i++)
    {
        int n = 3;
        float *ptr_a = &a[i][0];
        float *ptr_b = &b[i][0];
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);

            vfloat32m1_t vec_b = vmv_v_v_f32m1(vec_a, vl);
            vse32_v_f32m1(*ptr_b, vec_b, vl);
        }
    }   
}