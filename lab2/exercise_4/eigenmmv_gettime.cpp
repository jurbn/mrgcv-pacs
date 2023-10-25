#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include <sys/time.h>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{
    // clock_t time;
    // time = clock();
    
    struct timeval start, end, start_mult, end_mult;
    gettimeofday(&start, NULL);

    int N = std::atoi(argv[1]);

    int i, j, k;

    MatrixXd a = MatrixXd::Random(N,N);
    MatrixXd b = MatrixXd::Random(N,N);
    MatrixXd c(N,N);

    gettimeofday(&end, NULL);
    gettimeofday(&start_mult, NULL);

    c = a * b;

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
