#include <riscv_vector.h>
#include <stdio.h>

typedef float data_type;

#define MLEN 3
#define KLEN 3
#define NLEN 3

data_type b[3] = {1.0, 1.0, 1.0};
data_type c[3] = {0};
data_type a[3][3] = {{1.0, 2.0, 3.0},{4.0, 5.0, 6.0},{7.0, 8.0, 9.0}};
data_type d[3][3] = {{1.0, 1.0, 1.0},{1.0, 1.0, 1.0},{1.0, 1.0, 1.0}};
data_type e[3][3] = {0};
data_type f[5][5] = {{1.0, 2.0, 3.0, 4.0, 5.0},{1.0, 2.0, 3.0, 4.0, 5.0},{1.0, 2.0, 3.0, 4.0, 5.0},{1.0, 2.0, 3.0, 4.0, 5.0},{1.0, 2.0, 3.0, 4.0, 5.0}};
data_type g[5][5] = {{1.0, 1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0, 1.0},{1.0, 1.0, 1.0, 1.0, 1.0}};
data_type h[5][5] = {0};
data_type l[9][9] = {{1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9}};
data_type m[9][9] = {{1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1}};
data_type n[9][9] = {0};
data_type o[9][5] = {{1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5},
               {1,2,3,4,5}};
data_type p[9][5] = {0};
data_type q[9][5] = {{1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1},
               {1,1,1,1,1}};
data_type r[5][9] = {{1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1},
               {1,1,1,1,1,1,1,1,1}};
data_type s[5][9] = {{1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9},
               {1,2,3,4,5,6,7,8,9}};
data_type t[5] = {1,1,1,1,1};
data_type u[9] = {0};

data_type aa[9] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
data_type dd[9] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
data_type ee[9] = {0};




void MatrixMul33_3(data_type a[3][3], data_type b[3], data_type res[3]);
void MatrixMul33_33(data_type a[3][3],data_type b[3][3],data_type res[3][3]);
void MatrixMul55_55(data_type a[5][5],data_type b[5][5],data_type res[5][5]);
void MatrixMul99_99(data_type a[9][9],data_type b[9][9],data_type res[9][9]);
void MatrixMul99_95(data_type a[9][9],data_type b[9][5],data_type res[9][5]);
void MatrixMul95_55(data_type a[9][5],data_type b[5][5],data_type res[9][5]);
void MatrixMul95_59(data_type a[9][5],data_type b[5][9],data_type res[9][9]);
void MatrixMul59_95(data_type a[5][9],data_type b[9][5],data_type res[5][5]);
void MatrixMul95_5(data_type a[9][5],data_type b[5],data_type res[9]);

void MatrixAdd33(data_type A[3][3],data_type B[3][3],data_type c[3][3]);
void MatrixSub33(data_type A[3][3],data_type B[3][3],data_type c[3][3]);
void MatrixAdd55(data_type A[5][5],data_type B[5][5],data_type c[5][5]);
void MatrixSub55(data_type A[5][5],data_type B[5][5],data_type c[5][5]);
void MatrixAdd99(data_type A[9][9],data_type B[9][9],data_type c[9][9]);
void MatrixSub99(data_type A[9][9],data_type B[9][9],data_type c[9][9]);
void MatrixLiner3(data_type A[3][3],data_type k,data_type res[3][3]);
void MatrixTra99(data_type a[9][9],data_type b[9][9]);


void sgemm_golden();
void sgemm_vec(size_t size_m, size_t size_n, size_t size_k,
               const float *a, // m * k matrix
               size_t column_a,
               const float *b, // k * n matrix
               size_t column_b,
               float *c, // m * n matrix
               size_t column_c);

int main (void)
{
    MatrixMul33_33(a,d,e);
    sgemm_vec(3, 3, 3, aa, 3, dd, 3, ee, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%f\t", e[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for (int i = 0; i < 9; i++)
    {   
            printf("%f\t", ee[i]);
        //printf("\n");
    }

    return 0;
}



/*
void MatrixMul33_3(data_type a[3][3], data_type b[3], data_type res[3])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0];
            int n = 3;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i] = sum;
    }
}
*/
void MatrixMul33_33(data_type a[3][3], data_type b[3][3], data_type res[3][3])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 3;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}
/*
void MatrixMul55_55(data_type a[5][5], data_type b[5][5], data_type res[5][5])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 5;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}

void MatrixMul99_99(data_type a[9][9], data_type b[9][9], data_type res[9][9])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 9;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}

void MatrixMul99_95(data_type a[9][9], data_type b[9][5], data_type res[9][5])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 9;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}

void MatrixMul95_55(data_type a[9][5], data_type b[5][5], data_type res[9][5])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 5;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}

void MatrixMul95_59(data_type a[9][5], data_type b[5][9], data_type res[9][9])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 5;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}

void MatrixMul59_95(data_type a[5][9], data_type b[9][5], data_type res[5][5])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0][j];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 9;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i][j] = sum;
        }
    }
}

void MatrixMul95_5(data_type a[9][5], data_type b[5], data_type res[9])//a[x][z], b[z][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
            float *ptr_a = &a[i][0];
            float *ptr_b = &b[0];//这里有一个问题，因为数组在内存是一维连续存放, 因此*ptr_a = &a[i][0], *ptr_b = &b[j][0], 矩阵变成  行乘行，其中一个矩阵要转置一下
            int n = 5;
            vfloat32m1_t vec_s = vfmv_v_f_f32m1(0, vlmax);
            vfloat32m1_t vec_zero = vfmv_v_f_f32m1(0, vlmax);
            for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
            {
                vl = vsetvl_e32m1(n);

                vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
                vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

                vec_s = vfmacc_vv_f32m1(vec_s, vec_a, vec_b, vl);
            }

            vfloat32m1_t vec_sum;
            vec_sum = vfredusum_vs_f32m1_f32m1(vec_zero, vec_s, vec_zero, vlmax);
            float sum = vfmv_f_s_f32m1_f32(vec_sum);
            res[i] = sum;
    }
}

void MatrixAdd33(data_type A[3][3], data_type B[3][3], data_type C[3][3])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        int n = 3;
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
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

void MatrixSub33(data_type A[3][3], data_type B[3][3], data_type C[3][3])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 3; i++)
    {
        int n = 3;
        float *ptr_a = &A[i][0];
        float *ptr_b = &B[i][0];
        float *ptr_c = &C[i][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfsub_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

void MatrixAdd55(data_type A[5][5], data_type B[5][5], data_type C[5][5])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 5; i++)
    {
        int n = 5;
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
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

void MatrixSub55(data_type A[5][5], data_type B[5][5], data_type C[5][5])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 5; i++)
    {
        int n = 5;
        float *ptr_a = &A[i][0];
        float *ptr_b = &B[i][0];
        float *ptr_c = &C[i][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfsub_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

void MatrixAdd99(data_type A[9][9], data_type B[9][9], data_type C[9][9])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
        int n = 9;
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
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

void MatrixSub99(data_type A[9][9], data_type B[9][9], data_type C[9][9])///A[x][y],B[x][y]
{
    size_t vlmax = vsetvlmax_e32m1();
    for (int i = 0; i < 9; i++)
    {
        int n = 9;
        float *ptr_a = &A[i][0];
        float *ptr_b = &B[i][0];
        float *ptr_c = &C[i][0];
        vfloat32m1_t vec_c = vfmv_v_f_f32m1(0, vlmax);
        for (size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl, ptr_c += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);
            vfloat32m1_t vec_b = vle32_v_f32m1(ptr_b, vl);

            vec_c = vfsub_vv_f32m1(vec_a, vec_b, vl);
            vse32_v_f32m1(ptr_c, vec_c, vl);
        }
    }   
}

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
            vse32_v_f32m1(ptr_res, vec_res, vl);
        }
    }   
}

void MatrixTra99(data_type a[9][9],data_type b[9][9])///a[x][y], b[y][x]
{
	for(int i=0; i<9; i++)
    {
        int n = 9;
        float *ptr_a = &a[i][0];
        float *ptr_b = &b[0][i];
		for(size_t vl; n > 0; n -= vl, ptr_a += vl, ptr_b += vl)
        {
            vl = vsetvl_e32m1(n);
            vfloat32m1_t vec_a = vle32_v_f32m1(ptr_a, vl);

            //vfloat32m1_t vec_b = vmv_v_v_f32m1(vec_a, vl);            
            vse32_v_f32m1(ptr_b, vec_a, vl);
        }
    }
}

///////////////////////////////////////
void sgemm_golden() 
{
  for (size_t i = 0; i < MLEN; ++i)
    for (size_t j = 0; j < NLEN; ++j)
      for (size_t k = 0; k < KLEN; ++k)
        ee[i * NLEN + j] += aa[i * KLEN + k] * dd[j + k * NLEN];
}
*/
void sgemm_vec(size_t size_m, size_t size_n, size_t size_k,
               const float *a, // m * k matrix
               size_t column_a, //k
               const float *b, // k * n matrix
               size_t column_b, //n
               float *c, // m * n matrix
               size_t column_c) //n
{
  size_t vl;
  for (size_t m = 0; m < size_m; ++m) 
  {
    const float *b_n_ptr = b;
    float *c_n_ptr = c;
    for (size_t c_n_count = size_n; c_n_count>0; c_n_count -= vl) 
    {
      vl = vsetvl_e32m1(c_n_count);
      const float *a_k_ptr = a;
      const float *b_k_ptr = b_n_ptr;
      vfloat32m1_t acc = vle32_v_f32m1(c_n_ptr, vl);
      for (size_t k = 0; k < size_k; ++k) //a[0-lda]
      {
        vfloat32m1_t b_n_data = vle32_v_f32m1(b_k_ptr, vl);
        acc = vfmacc_vf_f32m1(acc, *a_k_ptr, b_n_data, vl);//a[0] * b[0-ldb]//vfloat32m1_t vfmacc_vf_f32m1 (vfloat32m1_t vd, float32_t rs1, vfloat32m1_t vs2, size_t vl);
        b_k_ptr += column_b;
        a_k_ptr++;
      }
      vse32_v_f32m1(c_n_ptr, acc, vl);
      c_n_ptr += vl;
      b_n_ptr += vl;
    }
    a += column_a;
    c += column_c;
  }
}
///////////////////////////////////////////////