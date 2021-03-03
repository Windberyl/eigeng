#include "eigeng.h"

void decompose_matrix(int n, double **mat)
{
    double *mem, *evalr, *evali, *evec;
    mem = (double *)calloc(n * n + 2 * n, sizeof(double));
    evec = mem;
    evalr = evec + n * n;
    evali = evalr + n;
    n_eigeng(mat[0], n, evalr, evali, evec);
}

int main(int argc, char **argv){
    if(argc < 2){
        printf("USAGE: ./eigeng_runtime [input path]\n");
        return 0;
    }
    FILE *f = fopen(argv[1], "r");
    int tests, n;
    fscanf(f, "%d %d", &tests, &n);
    double *mat[n];
    for(int i = 0; i < n; i++){
        mat[i] = (double *) malloc(n * sizeof(double));
    }
    for(int k = 0; k < tests; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                fscanf(f, "%d", &mat[i][j]);
            }
        }
        decompose_matrix(n, mat);
    }
    return 0;
}
