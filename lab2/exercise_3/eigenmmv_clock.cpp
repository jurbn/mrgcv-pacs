#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include <ctime>

using namespace Eigen;
using namespace std;

int main(int argc, char *argv[])
{
    clock_t time;
    time = clock();
    
    int N = std::atoi(argv[1]);
    int i, j, k;

    MatrixXd a = MatrixXd::Random(N,N);
    MatrixXd b = MatrixXd::Random(N,N);
    MatrixXd c(N,N);

    time = clock() - time;
    cout << "First part: " << ((float)time)/CLOCKS_PER_SEC << endl;

    time = clock();

    c = a * b;

    time = clock() - time;
    cout << "Second part: " << ((float)time)/CLOCKS_PER_SEC << endl;

    return 0;
}
