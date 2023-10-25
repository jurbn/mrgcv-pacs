#include <iomanip>
#include <iostream>
#include <limits>
#include <cmath>
#include <chrono>

// Allow to change the floating point type
using my_float = long double;

my_float pi_taylor(size_t steps) {
    long double sum_value = 0.0;
    int sign = -1;
    for (size_t n = 0; n < steps; n++) {
        sign = -sign;
        sum_value += sign / static_cast<my_float>(2 * n + 1);
    }
    return 4.0 * sum_value;
}

int main() {

    // read the number of steps from the command line

    // size_t steps = std::stoll(argv[1]); // std::stoll converts a string to a long long int
    size_t steps[] = {16, 16, 128, 1024, 1048576, 4294967295};
    for (int i = 0; i < 6; i++){
        // use std::chrono to measure time of execution for each step value
        my_float pi;
        auto start = std::chrono::high_resolution_clock::now();
        pi = pi_taylor(steps[i]);
        auto end = std::chrono::high_resolution_clock::now();
        // print the time taken
        std::cout << "Time taken for " << steps[i] << " steps: "
            << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
            << "ns" << std::endl;
        // print the pi value
        std::cout << "pi = " << std::setprecision(std::numeric_limits<my_float>::digits10 + 1) << pi << std::endl;
    }
}
