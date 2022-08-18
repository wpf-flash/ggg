#include <stdio.h>
#include "top.h"
#include "read.h"
#include "test_data.h"
#define N 5
// const data_type data[72][3][3] = {
// 			#include"w_conv2.h"
// };
#define u32 unsigned int
//data_type HLS_Result_c[N] = {0};
struct imu_data imu_in;
struct imu_data imu_out;
struct gyr_bias Gyr_Bias;
data_type Value_limit;
_Bool ready;
struct position pos_out;
data_type adjust_angle;
struct imu_data imu_;
_Bool rst;
_Bool zupt_valid;
uint32 count_1;
uint32 count_0;

u32 x,y,z;

// nw_Seq gry_x;


int main(void)
{

	rst = 0;
	Gyr_Bias.x = 0;
	Gyr_Bias.y = 0;
	Gyr_Bias.z = 0.007;
	Value_limit = 0;
	adjust_angle = 0;
	zupt_valid = 0;

	// char *gryx_path = "data/test.txt";
    // char *gryy_path = "data/gry_y.txt"; 25378
	// char *gryz_path = "data/gry_z.txt";106168

	// nw_Seq gry_x = read_ngimu(gryx_path);
	// gry_y = read_ngimu(gryx_path);
	// gry_z = read_ngimu(gryx_path);

// for (int i = 0; i < 4; i++)
// {
// 	printf("the number is %c",gry_x.res[i]);
// }

	// float a[23400];
	// FILE * f=fopen("data/gry_x.txt","r");
	// fscanf(f,"%f",a);
	// fclose(f);
	// printf("the number is %f",a[0]);
	// printf("Checking Results:\r\n");


	for(int i=0;i<131601;i++)
	{

		imu_in.acc1 = ACC_X[i];
		imu_in.acc2 = ACC_Y[i];
		imu_in.acc3 = ACC_Z[i];
		imu_in.gyr1 = GYR_X[i];
		imu_in.gyr2 = GYR_Y[i];
		imu_in.gyr3 = GYR_Z[i];

		imu_.acc1 = ACC_X[i];
		imu_.acc2 = ACC_Y[i];
		imu_.acc3 = ACC_Z[i];
		imu_.gyr1 = GYR_X[i];
		imu_.gyr2 = GYR_Y[i];
		imu_.gyr3 = GYR_Z[i];



		if (ZUPT[i] == 1)
		{
			zupt_valid = 1;
		}else
		{
			zupt_valid = 0;
		}
		
		
		

		ready = 0;
		Locate(imu_in, &imu_out, Gyr_Bias,Value_limit,ready, &pos_out,adjust_angle,imu_, rst,zupt_valid,&count_1,&count_0);
		ready = 1;
		Locate(imu_in, &imu_out, Gyr_Bias,Value_limit,ready, &pos_out,adjust_angle,imu_, rst,zupt_valid,&count_1,&count_0);


		if(i%400==0)
			printf("x is %f, y is %f \n",pos_out.posx,pos_out.posy);

	}

	


	return 0;
}
