//#include <assert.h>
#include <string.h>
#include "eigeng.h"

// epsilon - used to compare 2 floating point numbers
// a == b ? fabs(a-b) <= EPS : fabs(a-b) > EPS

#ifndef EPS
#define EPS 1e-3
#endif

static int counter = 1;

// Test correctness of eigeng.eigen()
// Parameters:      n - size of n x n matrix
//                  mat - n x n matrix
//                  ans_r - n array of eigenvalues (real part)
//                  ans_i - n array of eigenvalues (imag part)
//                      the ith eigenvalue is: ans_r[i] + ans_i[i]
void assert_matrix(int n, double (*mat)[n], double ans_r[n], double ans_i[n])
{
    // allocating memory to call eigen()
    // answers are returned through parameters
    // evalr + evali are eigenvalues
    // evec are eigen vectors
    double *mem, *evalr, *evali, *evec;
    mem = (double *)calloc(n * n + 2 * n, sizeof(double));
    evec = mem;
    evalr = evec + n * n;
    evali = evalr + n;
    n_eigeng(mat[0], n, evalr, evali, evec);

    // Idea: Order of eigenvalues returned by eigen() is unknown
    // Solution: Make assert_matrix check if a eigenvalue has been seen
    // breadth stores a boolean indiciating if the ith eigenvalue has been seen
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

    printf("Test %d:\n", counter++);
    int t = 1;
    for (int i = 0; i < n; i++)
    {
        t &= breadth[i];
        printf("\tEigenvalue #%d: %f+%fi\t\t", i + 1, ans_r[i], ans_i[i]);
        printf("%s\n", breadth[i] == 1 ? "CORRECT" : "INCORRECT");
    }

    if (t)
        printf("PASS\n\n");
    else
        printf("FAIL\n\n");
    free(mem);
}

int main(int argc, char **argv)
{
    ////////////////////////////////////////
    // TEST CASE: 1
    ////////////////////////////////////////
    // Small 5 x 5 matrix
    // 2 imaginary eigenvalues
    double sample_small[5][5] = {{1.0, 6.0, -3.0, -1.0, 7.0},
                                 {8.0, -15.0, 18.0, 5.0, 4.0},
                                 {-2.0, 11.0, 9.0, 15.0, 20.0},
                                 {-13.0, 2.0, 21.0, 30.0, -6.0},
                                 {17.0, 22.0, -5.0, 3.0, 6.0}};
    double sample_small_ans_r[5] = {42.961, 19.38, -15.3396, -15.3396, -0.661714};
    double sample_small_ans_i[5] = {0.0, 0.0, 6.75569, -6.75569, 0.0};
    assert_matrix(5, sample_small, sample_small_ans_r, sample_small_ans_i);

    ////////////////////////////////////////
    // TEST CASE: 2
    ////////////////////////////////////////
    // Small symmetric 5 x 5 matrix
    // 0 imaginary eigenvalues
    double symmetric_small[5][5] = {{10.0, 1.0, 2.0, 3.0, 4.0},
                                    {1.0, 9.0, -1.0, 2.0, -3.0},
                                    {2.0, -1.0, 7.0, 3.0, -5.0},
                                    {3.0, 2.0, 3.0, 12.0, -1.0},
                                    {4.0, -3.0, -5.0, -1.0, 15.0}};
    double symmetric_small_ans_r[5] = {19.1754, 15.8089, 9.36555, 6.99484, 1.65527};
    double symmetric_small_ans_i[5] = {0.0, 0.0, 0.0, 0.0, 0.0};
    assert_matrix(5, symmetric_small, symmetric_small_ans_r, symmetric_small_ans_i);

    ////////////////////////////////////////
    // TEST CASE: 3
    ////////////////////////////////////////
    // Small zero 2 x 2 matrix
    // Eigenvalues and eigenvectors of an n size
    //      matrix are guaranteed to be 0 and the zero
    //      vector respectively.
    double zero_small[2][2] = {{0.0, 0.0},
                               {0.0, 0.0}};
    double zero_small_ans_r[5] = {0.0, 0.0};
    double zero_small_ans_i[5] = {0.0, 0.0};
    assert_matrix(2, zero_small, zero_small_ans_r, zero_small_ans_i);

    ////////////////////////////////////////
    // TEST CASE: 4
    ////////////////////////////////////////
    // Small identity 2 x 2 matrix
    // Eigenvalues are always equal to 1
    double identity_small[2][2] = {{1.0, 0.0},
                                   {0.0, 1.0}};
    double identity_small_ans_r[5] = {1.0, 1.0};
    double identity_small_ans_i[5] = {0.0, 0.0};
    assert_matrix(2, identity_small, identity_small_ans_r, identity_small_ans_i);

    ////////////////////////////////////////
    // TEST CASE: 5
    ////////////////////////////////////////
    // Small orthogonal 2 x 2 matrix
    // If matrix A is orthogonal AA^T=I
    double orthogonal_small[2][2] = {{0.96, -0.28},
                                     {0.28, 0.96}};
    double orthogonal_small_ans_r[2] = {0.96, 0.96};
    double orthogonal_small_ans_i[2] = {0.28, -0.28};
    assert_matrix(2, orthogonal_small, orthogonal_small_ans_r, orthogonal_small_ans_i);

    return 0;
}
