#include "paragrams.h"
#include "stdbool.h"
#include "top.h"
#include "math.h"


///////////////////////////////////////Sub Function//////////////////////////////////////////////
void data_shift(struct imu_data imu_in);
void MatrixMul33_33(data_type a[3][3],data_type b[3][3],data_type res[3][3]);
void MatrixMul55_55(data_type a[5][5],data_type b[5][5],data_type res[5][5]);
void MatrixMul99_99(data_type a[9][9],data_type b[9][9],data_type res[9][9]);
void MatrixMul99_95(data_type a[9][9],data_type b[9][5],data_type res[9][5]);
void MatrixMul95_55(data_type a[9][5],data_type b[5][5],data_type res[9][5]);
void MatrixMul95_59(data_type a[9][5],data_type b[5][9],data_type res[9][9]);
void MatrixMul59_95(data_type a[5][9],data_type b[9][5],data_type res[5][5]);
void MatrixMul95_5(data_type a[9][5],data_type b[5],data_type res[9]);
void MatrixInv3(data_type A[3][3],data_type B[3][3]);
void SubMatrix4(char M,char N,data_type A[4][4],data_type B[3][3]);
void SubMatrix5(char M,char N,data_type A[5][5],data_type B[4][4]);
data_type MatrixDet3(data_type A[3][3]);
data_type MatrixDet4(data_type A[4][4]);
data_type MatrixDet5(data_type A[5][5]);
void MatrixInv5(data_type A[5][5],data_type B[5][5]);
void MatrixAdd33(data_type A[3][3],data_type B[3][3],data_type c[3][3]);
void MatrixSub33(data_type A[3][3],data_type B[3][3],data_type c[3][3]);
void MatrixAdd55(data_type A[5][5],data_type B[5][5],data_type c[5][5]);
void MatrixSub55(data_type A[5][5],data_type B[5][5],data_type c[5][5]);
void MatrixAdd99(data_type A[9][9],data_type B[9][9],data_type c[9][9]);
void MatrixSub99(data_type A[9][9],data_type B[9][9],data_type c[9][9]);
void MatrixLiner3(data_type A[3][3],data_type k,data_type res[3][3]);
void MatrixTra99(data_type a[9][9],data_type b[9][9]);
void MatrixTra59(data_type a[5][9],data_type b[9][5]);
void MatrixEqu33(data_type a[3][3],data_type b[3][3]);
void MatrixEqu99(data_type a[9][9],data_type b[9][9]);
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
void Reset();
void Locate(struct imu_data imu_in,struct imu_data* imu_out,struct gyr_bias Gyr_Bias,data_type Value_limit,_Bool ready,struct position *pos_out,data_type adjust_angle,struct imu_data imu_, _Bool rst,_Bool zupt_valid,uint32* count_1,uint32* count_0)
{
	data_type gyr[3];
	data_type acc[3];
	data_type tmp1,tmp2=0;
	if(rst==1)
	{
		Reset();
		ready_last=1;
		pos_out->posx=0;
		pos_out->posy=0;
	}
	else{

		if(ready==1&&ready_last==0)
		{
			imu_out->acc1=imu_.acc1;
			imu_out->acc2=imu_.acc2;
			imu_out->acc3=imu_.acc3;
			imu_out->gyr1=imu_.gyr1;
			imu_out->gyr2=imu_.gyr2;
			imu_out->gyr3=imu_.gyr3;
			if(state==0)
			{
				if(count>53)
				{
					Gyrbias.x=Gyr_Bias.x;
					Gyrbias.y=Gyr_Bias.y;
					Gyrbias.z=Gyr_Bias.z;
					value_limit=Value_limit;
					angle_cos=cosf(adjust_angle);
					angle_sin=sinf(adjust_angle);
					pitch_theta_sin= -imu_in.acc1/g;           ///ï¿½ï¿½g  xxxxxxxx
					pitch_theta_cos=sqrtf(1-pitch_theta_sin*pitch_theta_sin);
					roll_fai_sin=imu_in.acc2/sqrtf(imu_in.acc2*imu_in.acc2+imu_in.acc3*imu_in.acc3);
					roll_fai_cos=imu_in.acc3/sqrtf(imu_in.acc2*imu_in.acc2+imu_in.acc3*imu_in.acc3);

					C_INIT:{
						C[0][0]=pitch_theta_cos*yaw_psai_cos;
						C[0][1]=-roll_fai_cos*yaw_psai_sin+roll_fai_sin*pitch_theta_sin*yaw_psai_cos;
						C[0][2]=roll_fai_sin*yaw_psai_sin+roll_fai_cos*pitch_theta_sin*yaw_psai_cos;
						C[1][0]=pitch_theta_cos*yaw_psai_sin;
						C[1][1]=roll_fai_cos*yaw_psai_cos+yaw_psai_sin*pitch_theta_sin*roll_fai_sin;
						C[1][2]=-roll_fai_sin*yaw_psai_cos+roll_fai_cos*pitch_theta_sin*yaw_psai_sin;
						C[2][0]=-pitch_theta_sin;
						C[2][1]=roll_fai_sin*pitch_theta_cos;
						C[2][2]=roll_fai_cos*pitch_theta_cos;}
					state=1;
				}
				else
					count=count+1;
			}
			else
			{
				tmp1=pi/180;
				gyr[0]=imu_in.gyr1*tmp1-Gyrbias.x;
				gyr[1]=imu_in.gyr2*tmp1-Gyrbias.y;
				gyr[2]=imu_in.gyr3*tmp1-Gyrbias.z;
				gyr_lf[0][gyr_count]=gyr[0];
				gyr_lf[1][gyr_count]=gyr[1];
				gyr_lf[2][gyr_count]=gyr[2];
				if(gyr_count==0)
					gyr_count=4;
				else
					gyr_count-=1;
				if(gyr_lf_count<5)
					gyr_lf_count+=1;
				gyr[0]=(gyr_lf[0][0]+gyr_lf[0][1]+gyr_lf[0][2]+gyr_lf[0][3]+gyr_lf[0][4])/gyr_lf_count;
				gyr[1]=(gyr_lf[1][0]+gyr_lf[1][1]+gyr_lf[1][2]+gyr_lf[1][3]+gyr_lf[1][4])/gyr_lf_count;
				gyr[2]=(gyr_lf[2][0]+gyr_lf[2][1]+gyr_lf[2][2]+gyr_lf[2][3]+gyr_lf[2][4])/gyr_lf_count;


				acc_lf[0][acc_count]=imu_in.acc1*g;
				acc_lf[1][acc_count]=imu_in.acc2*g;
				acc_lf[2][acc_count]=imu_in.acc3*g;
				if(acc_count==0)
					acc_count=2;
				else
					acc_count-=1;
				if(acc_lf_count<3)
					acc_lf_count+=1;
				acc[0]=(acc_lf[0][0]+acc_lf[0][1]+acc_lf[0][2])/acc_lf_count;
				acc[1]=(acc_lf[1][0]+acc_lf[1][1]+acc_lf[1][2])/acc_lf_count;
				acc[2]=(acc_lf[2][0]+acc_lf[2][1]+acc_lf[2][2])/acc_lf_count;

				omega[0][0]=0;
				omega[0][1]=-gyr[2];
				omega[0][2]=gyr[1];
				omega[1][0]=gyr[2];
				omega[1][1]=0;
				omega[1][2]=-gyr[0];
				omega[2][0]=-gyr[1];
				omega[2][1]=gyr[0];
				omega[2][2]=0;
				//orientation estimation
				////////////////////////////////////////////////////////////
				//C = C*(2*eye(3) + Omega*ts)/(2*eye(3) - Omega*ts);
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						//shichaofan
						if(isnan(tmp33_1[i][j]))
							tmp33_1[i][j] = 0;
					}	
				}
				

				MatrixAdd33(eye3_2fs,omega,tmp33_1);
				MatrixSub33(eye3_2fs,omega,tmp33_2);

				MatrixMul33_33(C,tmp33_1,tmp33_3);  //tmp1/C free
				MatrixInv3(tmp33_2,tmp33_1);        //tmp2/C free
				MatrixMul33_33(tmp33_3,tmp33_1,C);  //tmp all free

//////////////////////////////////////////////////////////////////////////
				a[0]=C[0][0]*acc[0]+C[0][1]*acc[1]+C[0][2]*acc[2];
				a[1]=C[1][0]*acc[0]+C[1][1]*acc[1]+C[1][2]*acc[2];
				a[2]=C[2][0]*acc[0]+C[2][1]*acc[1]+C[2][2]*acc[2];

				v[0]=v_last[0]+(a[0]+a_last[0])*half_ts;
				v[1]=v_last[1]+(a[1]+a_last[1])*half_ts;
				v[2]=v_last[2]+(a[2]+a_last[2]-2*g)*half_ts;

				pos[0]=pos_last[0]+(v[0]+v_last[0])*half_ts;
				pos[1]=pos_last[1]+(v[1]+v_last[1])*half_ts;
				pos[2]=pos_last[2]+(v[2]+v_last[2])*half_ts;
//////////////////////////////////////////////////////////////////
				//×´Ì¬Îó²îÔ¤²â
				F[6][1]=a[2]*ts;
				F[6][2]=-a[1]*ts;
				F[7][0]=-a[2]*ts;
				F[7][2]=a[0]*ts;
				F[8][0]=a[1]*ts;
				F[8][1]=-a[0]*ts;

				MatrixMul99_99(F,P,tmp99_1);
				MatrixTra99(F,P);
				MatrixMul99_99(tmp99_1,P,tmp99_2);
				MatrixAdd99(tmp99_2,Q,P);

				/////////////////////////////////////////////////////////////////////////////////////////////////
				//×´Ì¬¸üÐÂ
				zupt:{
				value=sqrtf(gyr[0]*gyr[0]+gyr[1]*gyr[1]+gyr[2]*gyr[2]);
				if(zupt_valid==1)
				{
					cnt1=cnt1+1;
					MatrixTra59(H,tmp95_1);
					MatrixMul99_95(P,tmp95_1,tmp95_2);  //P*H'
					MatrixMul59_95(H,tmp95_2,tmp55_1);  //H*P*H'
					MatrixAdd55(tmp55_1,R,tmp55_2);		//H*P*H'+R
					MatrixInv5(tmp55_2,tmp55_1);
					MatrixMul95_55(tmp95_2,tmp55_1,K);

					tmp5_1[1]=pos[2];
					tmp5_1[2]=v[0];
					tmp5_1[3]=v[1];
					tmp5_1[4]=v[2];

					MatrixMul95_5(K,tmp5_1,delta_x);

					MatrixMul95_59(K,H,tmp99_1);
					MatrixMul99_99(tmp99_1,P,tmp99_2);
					MatrixSub99(P,tmp99_2,tmp99_1);
					MatrixEqu99(tmp99_1,P);

					pos[0]=pos[0]-delta_x[3];
					pos[1]=pos[1]-delta_x[4];
					pos[2]=pos[2]-delta_x[5];
					v[0]=v[0]-delta_x[6];
					v[1]=v[1]-delta_x[7];
					v[2]=v[2]-delta_x[8];

					delta_angle[0][1]=delta_x[2];
					delta_angle[0][2]=-delta_x[1];
					delta_angle[1][0]=-delta_x[2];
					delta_angle[1][2]=delta_x[0];
					delta_angle[2][0]=delta_x[1];
					delta_angle[2][1]=-delta_x[0];
					//C = (2*eye(3) + delta_angle)/(2*eye(3) - delta_angle)*C;
					MatrixSub33(eye3_2,delta_angle,tmp33_1);
					MatrixInv3(tmp33_1,tmp33_2);
					MatrixAdd33(eye3_2,delta_angle,tmp33_1);
					MatrixMul33_33(tmp33_1,tmp33_2,tmp33_3);
					MatrixMul33_33(tmp33_3,C,tmp33_1);
					MatrixEqu33(tmp33_1,C);
				}
				else
					cnt2++;
				}
				*count_1=cnt1;
				*count_0=cnt2;
				pos_last[0]=pos[0];
				pos_last[1]=pos[1];
				pos_last[2]=pos[2];
				v_last[0]=v[0];
				v_last[1]=v[1];
				v_last[2]=v[2];
				a_last[0]=a[0];
				a_last[1]=a[1];
				a_last[2]=a[2];
				pos_out->posx=pos[0];
				pos_out->posy=pos[1];
				pos_out->posz=pos[2];
			}
		}
	ready_last=ready;
	}
}





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


void MatrixMul33_33(data_type a[3][3],data_type b[3][3],data_type res[3][3])
{
  // Iterate over the rows of the A matrix
   Row: for(int i = 0; i < 3; i++) {
      // Iterate over the columns of the B matrix
      Col: for(int j = 0; j < 3; j++) {
         res[i][j] = 0;
         // Do the inner product of a row of A and col of B
         Product: for(int k = 0; k < 3; k++) {
            res[i][j] += a[i][k] * b[k][j];
         }
      }
   }
}

void MatrixMul55_55(data_type a[5][5],data_type b[5][5],data_type res[5][5])
{
	 Row: for(int i = 0; i < 5; i++) {
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j < 5; j++) {
	         res[i][j] = 0;
	         // Do the inner product of a row of A and col of B
	         Product: for(int k = 0; k < 5; k++) {
	            res[i][j] += a[i][k] * b[k][j];
	         }
	      }
	   }
}

void MatrixMul99_99(data_type a[9][9],data_type b[9][9],data_type res[9][9])
{
	 Row: for(int i = 0; i < 9; i++) {
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j < 9; j++) {
	         res[i][j] = 0;
	         // Do the inner product of a row of A and col of B
	         Product: for(int k = 0; k < 9; k++) {
	            res[i][j] += a[i][k] * b[k][j];
	         }
	      }
	   }
}

void MatrixMul99_95(data_type a[9][9],data_type b[9][5],data_type res[9][5])
{
	 Row: for(int i = 0; i < 9; i++) {
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j <5; j++) {
	         res[i][j] = 0;
	         // Do the inner product of a row of A and col of B
	         Product: for(int k = 0; k < 9; k++) {
	            res[i][j] += a[i][k] * b[k][j];
	         }
	      }
	   }
}

void MatrixMul95_55(data_type a[9][5],data_type b[5][5],data_type res[9][5])
{
	 Row: for(int i = 0; i < 9; i++) {
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j < 5; j++) {
	         res[i][j] = 0;
	         // Do the inner product of a row of A and col of B
	         Product: for(int k = 0; k < 5; k++) {
	            res[i][j] += a[i][k] * b[k][j];
	         }
	      }
	   }
}

void MatrixMul95_59(data_type a[9][5],data_type b[5][9],data_type res[9][9])
{
	 Row: for(int i = 0; i < 9; i++) {
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j < 9; j++) {
	         res[i][j] = 0;
	         // Do the inner product of a row of A and col of B
	         Product: for(int k = 0; k < 5; k++) {
	            res[i][j] += a[i][k] * b[k][j];
	         }
	      }
	   }
}

void MatrixMul59_95(data_type a[5][9],data_type b[9][5],data_type res[5][5])
{
	 Row: for(int i = 0; i < 5; i++) {
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j < 5; j++) {
	         res[i][j] = 0;
	         // Do the inner product of a row of A and col of B
	         Product: for(int k = 0; k < 9; k++) {
	            res[i][j] += a[i][k] * b[k][j];
	         }
	      }
	   }
}

void MatrixMul95_5(data_type a[9][5],data_type b[5],data_type res[9])
{
	 Row: for(int i = 0; i < 9; i++)
	 {
		 res[i]=0;
	      // Iterate over the columns of the B matrix
	      Col: for(int j = 0; j < 5; j++)
	      {
	            res[i] += a[i][j] * b[j];
	      }
	   }
}

void MatrixInv3(data_type A[3][3],data_type B[3][3])
{
	data_type det=A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1])-A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0])+A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			B[j][i]=(A[(i+1)%3][(j+1)%3]*A[(i+2)%3][(j+2)%3]-A[(i+2)%3][(j+1)%3]*A[(i+1)%3][(j+2)%3])/det;
		}
	}
}

void SubMatrix4(char M,char N,data_type A[4][4],data_type B[3][3])
{
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(i<M&&j<N)
				B[i][j]=A[i][j];
			else if(i>M&&j<N)
				B[i-1][j]=A[i][j];
			else if(i<M&&j>N)
				B[i][j-1]=A[i][j];
			else if(i>M&&j>N)
				B[i-1][j-1]=A[i][j];
		}
	}
}
void SubMatrix5(char M,char N,data_type A[5][5],data_type B[4][4])
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(i<M&&j<N)
				B[i][j]=A[i][j];
			else if(i>M&&j<N)
				B[i-1][j]=A[i][j];
			else if(i<M&&j>N)
				B[i][j-1]=A[i][j];
			else if(i>M&&j>N)
				B[i-1][j-1]=A[i][j];
		}
	}
}


data_type MatrixDet3(data_type A[3][3])
{

	return A[0][0]*(A[1][1]*A[2][2]-A[1][2]*A[2][1])-A[0][1]*(A[1][0]*A[2][2]-A[1][2]*A[2][0])+A[0][2]*(A[1][0]*A[2][1]-A[1][1]*A[2][0]);
}

data_type MatrixDet4(data_type A[4][4])
{
	data_type sum=0;
	data_type B[3][3];
	MatrixDet4_label0:for(int i=0;i<4;i++)
	{
		SubMatrix4(0,i,A,B);
		if(i%2==0)
		sum+=A[0][i]*MatrixDet3(B);
		else
		sum-=A[0][i]*MatrixDet3(B);
	}
	return sum;
}
data_type MatrixDet5(data_type A[5][5])
{
	data_type sum=0;
	data_type B[4][4];
	MatrixDet5_label1:for(int i=0;i<5;i++)
	{
		SubMatrix5(0,i,A,B);
		if(i%2==0)
		sum+=A[0][i]*MatrixDet4(B);
		else
		sum-=A[0][i]*MatrixDet4(B);
	}
	return sum;
}

void MatrixInv5(data_type A[5][5],data_type B[5][5])
{
	data_type det=MatrixDet5(A);
	data_type C[4][4]={0};
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			SubMatrix5(i,j,A,C);
			B[j][i]=MatrixDet4(C)/det;
		}
	}
}

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

void MatrixSub33(data_type A[3][3],data_type B[3][3],data_type c[3][3])
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			c[i][j]=A[i][j]-B[i][j];
		}
	}
}

void MatrixAdd55(data_type A[5][5],data_type B[5][5],data_type c[5][5])
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			c[i][j]=A[i][j]+B[i][j];
		}
	}
}

void MatrixSub55(data_type A[5][5],data_type B[5][5],data_type c[5][5])
{
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			c[i][j]=A[i][j]-B[i][j];
		}
	}
}

void MatrixAdd99(data_type A[9][9],data_type B[9][9],data_type c[9][9])
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			c[i][j]=A[i][j]+B[i][j];
		}
	}
}

void MatrixSub99(data_type A[9][9],data_type B[9][9],data_type c[9][9])
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			c[i][j]=A[i][j]-B[i][j];
		}
	}
}

void MatrixLiner3(data_type A[3][3],data_type k,data_type res[3][3])
{
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			res[i][j]=A[i][j]*k;
}

void MatrixTra99(data_type a[9][9],data_type b[9][9])
{
	for(char i=0;i<9;i++)
		for(char j=0;j<9;j++)
		b[j][i]=a[i][j];
}

void MatrixTra59(data_type a[5][9],data_type b[9][5])
{
	for(char i=0;i<5;i++)
		for(char j=0;j<9;j++)
		b[j][i]=a[i][j];
}

void MatrixEqu33(data_type a[3][3],data_type b[3][3])
{
	for(char i=0;i<3;i++)
		for(char j=0;j<3;j++)
			b[i][j]=a[i][j];
}

void MatrixEqu99(data_type a[9][9],data_type b[9][9])
{
	for(char i=0;i<9;i++)
		for(char j=0;j<9;j++)
			b[i][j]=a[i][j];
}
