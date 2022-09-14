#include "paragrams.h"
#include "stdbool.h"
#include "top.h"
#include "math.h"
#include <riscv_vector.h>

///////////////////////////////////////Sub Function//////////////////////////////////////////////
void MatrixMul(data_type **a, data_type **b, data_type **res, int x, int y, int z)//a[x][z], b[z][y]
void MatrixAdd(data_type **A, data_type **B, data_type **C, int x, int y)///A[x][y],B[x][y]
void MatrixSub(data_type **A, data_type **B, data_type **C, int x, int y)///A[x][y],B[x][y]
void MatrixTra(data_type **a, data_type **b, int x, int y)///a[x][y], b[y][x]
void MatrixLiner(data_type **A, data_type k, data_type **res, int x, int y)//A[x][y]
void MatrixEqu(data_type **a, data_type **b, int x, int y)//A[x][y], B[x][y]

void MatrixInv3(data_type A[3][3],data_type B[3][3]);
void SubMatrix4(char M,char N,data_type A[4][4],data_type B[3][3]);
void SubMatrix5(char M,char N,data_type A[5][5],data_type B[4][4]);
data_type MatrixDet3(data_type A[3][3]);
data_type MatrixDet4(data_type A[4][4]);
data_type MatrixDet5(data_type A[5][5]);
void MatrixInv5(data_type A[5][5],data_type B[5][5]);
///////////////////////////////////////////////////////////////////////////////////////////////////////

int shift_count=0;
_Bool shift_ready=0;
char state=0;
char count=0;
const data_type g=9.8065;
data_type pitch_theta,pitch_theta_cos,pitch_theta_sin;
data_type roll_fai,roll_fai_sin,roll_fai_cos;
data_type yaw_psai_sin=0,yaw_psai_cos=1;
data_type value=0;
data_type C[3][3]={0};
data_type P[9][9]={0};
data_type pos[3]={0},pos_last[3]={0},v[3]={0},v_last[3]={0},a[3]={0},a_last[3]={0,0,9.8065};//a_last[3]={0,0,g}
data_type K[9][5];
data_type delta_x[9]={0},delta_angle[3][3]={0};

data_type acc_lf[3][3]={0};
data_type gyr_lf[3][5]={0};
data_type omega[3][3];
data_type tmp5_1[5]={0};
data_type tmp33_1[3][3],tmp33_2[3][3],tmp33_3[3][3];
data_type tmp99_1[9][9],tmp99_2[9][9];
data_type tmp95_1[9][5],tmp95_2[9][5];
data_type tmp55_1[5][5],tmp55_2[5][5];
char gyr_count=4;
char acc_count=2;
char gyr_lf_count=0;
char acc_lf_count=0;
char threshold_count=9;
char threshold_lf_count=0;
_Bool ready_last=0;
struct gyr_bias Gyrbias={0,0,0};
data_type value_limit=1;
data_type angle_cos,angle_sin;
uint32 cnt1=0,cnt2=0;
////////////////////////////////////////////////////////////////////////////////////

void Reset();
void Locate(struct imu_data imu_in,struct imu_data* imu_out,
		struct gyr_bias Gyr_Bias,data_type Value_limit,_Bool ready,
		struct position *pos_out,data_type adjust_angle,struct imu_data imu_,
		_Bool rst,_Bool zupt_valid,uint32* count_1,uint32* count_0)
{




    
}
