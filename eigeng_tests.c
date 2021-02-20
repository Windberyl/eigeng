//#include <assert.h>
#include <string.h>
#include "eigeng.h"

#ifndef EPS
#define EPS 1e-3
#endif

static int counter = 1;

void assert_matrix(int n, double (*mat)[n], double ans_r[n], double ans_i[n])
{
    double *mem, *evalr, *evali, *evec;
    mem = (double *)calloc(n * n + 2 * n, sizeof(double));
    evec = mem;
    evalr = evec + n * n;
    evali = evalr + n;
    n_eigeng(mat[0], n, evalr, evali, evec);
    int breadth[n];
    memset(breadth, 0, sizeof(breadth));

    for (int i = 0; i < n; i++)
    {
        int it1 = -1, it2 = -1;
        for (int j = 0; j < n; j++)
        {
            if (fabs(evalr[i] - ans_r[j]) <= EPS && !breadth[j])
                it1 = j;
            if (fabs(evali[i] - ans_i[j]) <= EPS && !breadth[j])
                it2 = j;
            if (it1 != -1 && it2 != -1 && it1 == it2)
            {
                breadth[it1] = 1;
                break;
            }
        }
    }

    int t = 1;
    for (int i = 0; i < n; i++)
    {
        t &= breadth[i];
    }

    printf("Test %d: ", counter++);
    if(t) printf("PASS\n");
    else printf("FAIL\n");
    free(mem);
}

int main(int argc, char **argv)
{
    static double sample_small[5][5] = {{1.0, 6.0, -3.0, -1.0, 7.0},
                                        {8.0, -15.0, 18.0, 5.0, 4.0},
                                        {-2.0, 11.0, 9.0, 15.0, 20.0},
                                        {-13.0, 2.0, 21.0, 30.0, -6.0},
                                        {17.0, 22.0, -5.0, 3.0, 6.0}};
    static double sample_small_ans_r[5] = {42.961, 19.38, -15.3396, -15.3396, -0.661714};
    static double sample_small_ans_i[5] = {0.0, 0.0, 6.75569, -6.75569, 0.0};
    assert_matrix(5, sample_small, sample_small_ans_r, sample_small_ans_i);
    return 0;
}