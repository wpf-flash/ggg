#ifndef __PARAGRAMS_H__
#define __PARAGRAMS_H__
#include "top.h"

//#define samplerate 400

//#define gyrBias 0.01

//#define g 9.8065

//#define segma_omega 0.01
//#define segma_a 0.01

const data_type pi=3.1415926;
const data_type fs=256;
//#define fs 250
const data_type ts=0.004;//0.0025
const data_type half_ts=0.002;

//#define g 9.8065
const data_type half_g=4.90325;

data_type eye3_2[3][3]={{2,0,0},{0,2,0},{0,0,2}};
data_type eye3_2fs[3][3]={{512,0,0},{0,512,0},{0,0,512}};//{{2*fs,0,0},{0,2*fs,0},{0,0,2*fs}}
const data_type G[3]={0,0,9.8065};
data_type Q[9][9]={
		#include "Q.h"
};
data_type F[9][9]={
		#include "F.h"
};
data_type H[5][9]={
		#include "H.h"
};
data_type R[5][5]={
		#include "R.h"
};

#endif
