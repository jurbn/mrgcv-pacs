#include <iostream>
#include <cstdlib>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[])
{
    // clock_t time;
    // time = clock();

    struct timeval start, end, start_mult, end_mult;
    gettimeofday(&start, NULL);

    int N = std::atoi(argv[1]);
    int i, j, k;

    // Memory allocation
    double **a = new double*[N];
    double **b = new double*[N];
    double **c = new double*[N];

    for(i = 0; i < N; ++i)
    {
	a[i] = new double[N];
	b[i] = new double[N];
	c[i] = new double[N];
    }

    // Storing elements of matrices
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
        {
            a[i][j] = ((double)rand()) / RAND_MAX;
	    b[i][j] = ((double)rand()) / RAND_MAX;
        }

    // Initializing elements of matrix c to 0
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
            c[i][j] = 0;

    gettimeofday(&end, NULL);

    gettimeofday(&start_mult, NULL);

    // Multiplying matrix a and b and storing in matrix c
    for(i = 0; i < N; ++i)
        for(k = 0; k < N; ++k)
            for(j = 0; j < N; ++j)    
                c[i][j] += a[i][k] * b[k][j];

    // Displaying the multiplication of two matrix
    //cout << endl << "Output Matrix: " << endl;
    //for(i = 0; i < N; ++i)
    //   for(j = 0; j < N; ++j)
    //   {
    //       cout << " " << c[i][j];
    //       if(j == N-1)
    //           cout << endl;
    //   }

    // time = clock() - time;
    // cout << "Measured: " << ((float)time)/CLOCKS_PER_SEC << endl;

    gettimeofday(&end_mult, NULL);

    float first_part = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    float second_part = (end_mult.tv_sec - start_mult.tv_sec) + (end_mult.tv_usec - start_mult.tv_usec) / 1000000.0;

    cout << "First part: " << first_part << endl;

    //cout << "First part: " << (end.tv_usec - start.tv_usec) / 1000000.0 << endl;
    cout << "Second part: " << second_part << endl;

    return 0;
}
