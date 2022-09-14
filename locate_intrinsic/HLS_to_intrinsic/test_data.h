#ifndef __TESTDATA_H__
#define __TESTDATA_H__
#include "top.h"


float GYR_X[]={
		#include "gyr_x.h"
};
float GYR_Y[]={
		#include "gyr_y.h"
};
float GYR_Z[]={
		#include "gyr_z.h"
};


float ACC_X[]={
		#include "acc_x.h"
};
float ACC_Y[]={
		#include "acc_y.h"
};
float ACC_Z[]={
		#include "acc_z.h"
};

_Bool ZUPT[]={
		#include "zupt.h"
};

#endif
