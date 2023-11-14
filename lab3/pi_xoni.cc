#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

using my_float = long double;

void pi_taylor_chunk(std::vector<my_float> &output,
        size_t thread_id, size_t start_step, size_t stop_step) {
    my_float pi = 0.0f;
    int sign = 1;
    for (size_t i = start_step; i < stop_step; i++) {
        pi += 1 / (2.0f * i + 1.0f)*sign;
        sign = -sign;
    }
    output[thread_id] = pi;
}

std::pair<size_t, size_t>
usage(int argc, const char *argv[]) {
    // read the number of steps from the command line
    if (argc != 3) {
        std::cerr << "Invalid syntax: pi_taylor <steps> <threads>" << std::endl;
        exit(1);
    }

    size_t steps = std::stoll(argv[1]);
    size_t threads = std::stoll(argv[2]);

    if (steps < threads ){
        std::cerr << "The number of steps should be larger than the number of threads" << std::endl;
        exit(1);

    }
    return std::make_pair(steps, threads);
}

int main(int argc, const char *argv[]) {


    auto ret_pair = usage(argc, argv);
    auto steps = ret_pair.first;
    auto threads = ret_pair.second;

    my_float pi;
    std::vector<std::thread> thread_pool;
    std::vector<my_float> partial_output(threads, 0.0f);

    auto start = std::chrono::steady_clock::now();
    for (size_t i = 0; i < threads; i++) {
        size_t start_step = i * steps / threads;
        size_t stop_step = (i + 1) * steps / threads;

        // Launch threads to compute partial sums
        thread_pool.emplace_back(pi_taylor_chunk,
                std::ref(partial_output), i, start_step, stop_step);   
    }

    // Wait for all threads to finish
    for (size_t i = 0; i < threads; i++) {
        thread_pool[i].join();
    }

    // Accumulate partial sums to get the final pi result
    pi = std::accumulate(partial_output.begin(), partial_output.end(), 0.0f);

    // Multiply by 4 to get the final result
    pi *= 4;

    // Measure the execution time
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> time = end - start;

    std::cout << "For " << steps << "steps, pi value: "
        << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
        << pi << std::endl;
        std::cout << "Time: " << time.count() << " seconds" << std::endl;
}

