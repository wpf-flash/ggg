#include <riscv_vector.h>

void Reset()
{
	int i=0,j=0;
	state=0;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
		{
			C[i][j]=0;
			acc_lf[i][j]=0;
		}
	for(i=0;i<3;i++)
		for(j=0;j<5;j++)
			gyr_lf[i][j]=0;
	gyr_lf_count=0;
	acc_lf_count=0;
	gyr_count=4;
	acc_count=2;
	for(i=0;i<3;i++)
	{
		a_last[i]=0;
		v_last[i]=0;
		pos_last[i]=0;
	}
	a_last[2]=g;
	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			P[i][j]=0;
}



/////////intrinsic函数
void Reset()
{
    state=0;
    for (int i = 0; i < 3; i++)
    {
        int n = 3;
       
        float *ptr_c = &C[i][0];
        float *ptr_acc_lf = &acc_lf[i][0];
        for (size_t vl; n > 0; n -= vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);

            vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vl);
            vfloat32m1_t vec_acc_lf= vfmv_v_f_f32m1(0, vl);

            vse32_v_f32m1(*ptr_c, vec_c, vl);
            vse32_v_f32m1(*ptr_acc_lf, vec_acc_lf, vl);
        }
    } 
    for (int i = 0; i < 3; i++)
    {
        int m = 5;
        float *ptr_gyr_lf = &gyr_lf[i][0];
        for (size_t vl; m > 0; m -= vl, ptr_gyr_lf += vl)
        {
            vl = vsetvl_e32m1(m);

            vfloat32m1_t vec_gyr_lf = vfmv_v_f_f32m1(0, vl);

            vse32_v_f32m1(*ptr_gyr_lf, vec_gyr_lf, vl);
        }
    }
    gyr_lf_count=0;
	acc_lf_count=0;
	gyr_count=4;
	acc_count=2;

    int z = 3;
    float *ptr_a_last = &a_last[0];
    float *ptr_v_last = &v_last[0];
    float *ptr_pos_last = &pos_last[0];
    for(size_t vl; z>0; z -= vl, ptr_a_last += vl, ptr_v_last += vl, ptr_pos_last += vl,)
	{
		vl = vsetvl_e32m1(z);

        vfloat32m1_t vec_a_last = vfmv_v_f_f32m1(0, vl);
        vfloat32m1_t vec_v_last = vfmv_v_f_f32m1(0, vl);
        vfloat32m1_t vec_pos_last = vfmv_v_f_f32m1(0, vl);

        vse32_v_f32m1(*ptr_a_last, vec_a_last, vl);
        vse32_v_f32m1(*ptr_v_last, vec_v_last, vl);
        vse32_v_f32m1(*ptr_pos_last, vec_pos_last, vl);
	}
    a_last[2]=g;
    for (int i = 0; i < 9; i++)
    {
        int w = 9;
        float *ptr_P = &P[i][0];
        for (size_t vl; w > 0; w -= vl, ptr_P += vl)
        {
            vl = vsetvl_e32m1(w);

            vfloat32m1_t vec_P = vfmv_v_f_f32m1(0, vl);
            
            vse32_v_f32m1(*ptr_P, vec_P, vl);
        }
    } 
}








