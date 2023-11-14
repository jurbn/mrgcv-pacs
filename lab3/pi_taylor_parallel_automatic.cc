#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <fstream>
#include <chrono>

std::ofstream BenchmarkFile("data.csv");

using my_float = long double;

void pi_taylor_chunk(std::vector<my_float> &output,
        size_t thread_id, size_t start_step, size_t stop_step) {
    long double sum_value = 0.0;
    int sign = start_step % 2 == 0 ? 1 : -1;
    for (size_t n = start_step; n < stop_step; n++) {
        sum_value += sign / static_cast<my_float>(2 * n + 1);
        sign = -sign;
    }
    output[thread_id] = sum_value;
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

int main() {
    BenchmarkFile << "Threads,Time,Value" << std::endl;

    auto n_steps = 4294967295;
    int n_threads_arr[] = {1, 2, 4, 8, 16};

    for (size_t i = 0; i < 5; i++){
        auto start = std::chrono::high_resolution_clock::now();
        int n_threads = n_threads_arr[i];
        std::vector<std::thread> thread_pool;
        std::vector<my_float> output(n_threads, 0.0);
        for (int j = 0; j < n_threads; j++){
            auto start_step = j * (n_steps / n_threads);
            auto stop_step = (j + 1) * (n_steps / n_threads);
            // launch a thread to compute pi_taylor_chunk for the i-th chunk
            thread_pool.emplace_back(pi_taylor_chunk, std::ref(output), j, start_step, stop_step);
            //pi_taylor_chunk(output, i, start_step, stop_step);
        }
        // wait for all threads to finish
        for (auto &t : thread_pool) {
            t.join();
        }
        // do the sum of values in output
        auto pi_value = std::accumulate(output.begin(), output.end(), 0.0);
        pi_value = pi_value * 4.0;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        BenchmarkFile << n_threads << "," << duration.count() << "," << pi_value << std::endl;
        // kill the threads
        thread_pool.clear();
    }
}

