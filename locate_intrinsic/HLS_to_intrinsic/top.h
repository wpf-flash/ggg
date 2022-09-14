#ifndef __TOP_H_
#define __TOP_H_

// #include <ap_cint.h>
//#include "ap_int.h"
#include "math.h"
#include <tgmath.h>
#include <stdbool.h>
#include <stdint.h>
typedef float data_type;
typedef uint32_t uint32;
struct position
{
	data_type posx;
	data_type posy;
	data_type posz;
};
//position pos_out;
struct imu_data
{
	data_type gyr1,gyr2,gyr3;
	data_type acc1,acc2,acc3;
};

struct gyr_bias
{
	data_type x,y,z;  //0,0,0.07
};

//void Locate(data_type gyr1,data_type gyr2,data_type gyr3,data_type acc1,data_type acc2,data_type acc3,struct position pos_out);
void Locate(struct imu_data imu_in,struct imu_data* imu_out,struct gyr_bias Gyr_Bias,data_type Value_limit,_Bool ready,struct position *pos_out,data_type adjust_angle,struct imu_data imu_, _Bool rst, _Bool zupt_valid,uint32* count_1,uint32* count_0);
#endif
