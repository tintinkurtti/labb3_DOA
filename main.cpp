#include <iostream>
#include "Search.h"
#include <vector>
#include <chrono>
#include <fstream>
#include <valarray>
#include <numeric>

struct run {
    int N;
    double time;
    double std_dev;
    int samples;
};

run create_run(int N, double time, double std_dev, int samples) {
    run r;
    r.N = N;
    r.time = time;
    r.std_dev = std_dev;
    r.samples = samples;
    return r;
}

std::vector<bool> create_primes(int N){
    std::vector<bool> primes(N + 1, true);
    primes[0] = false;
    primes[1] = false;
    for (int i = 2; i * i <= N; i++) {
        if (primes[i]) {
            for (int j = i * i; j <= N; j += i) {
                primes[j] = false;
            }
        }
    }
    return primes;

}

void write_to_file(std::vector<run> &results, std::string filename) {
    std::ofstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << "Could not open file" << std::endl;
        return;
    }

    for (auto &run : results) {
        file << run.N << "  " << run.time << "  " << run.std_dev << " " << run.samples << std::endl;
    }

    file.close();
}

double std_dev(std::vector<double> &times) {

    double sum = std::accumulate(times.begin(), times.end(), 0.0);
    auto avg = sum / times.size();

    // Calculate the deviation from the average
    std::vector<double> dev_square(times);
    for(auto &time : dev_square) {
        time = std::pow(time - avg, 2);
    }

    // Calculate the sum of the squares
    double sum_square = std::accumulate(dev_square.begin(), dev_square.end(), 0.0);

    // Calculate the standard deviation
    return std::sqrt(sum_square * (1.0 / (times.size() - 1)));
}

void generate_random(int N, std::vector<int> &vec) {
    for (int i = 0; i < N; i++) {
        vec.push_back(rand() % N);
    }
}

void generate_rising(int N, std::vector<int> &vec) {
    for (int i = 0; i < N; i++) {
        vec.push_back(i);
    }
}

void generate_falling(int N, std::vector<int> &vec) {
    for (int i = N; i > 0; i--) {
        vec.push_back(i);
    }
}

void run_time(std::vector<int> &vec, void (*sort)(std::vector<int> &, int a, int b), int N, int samples, std::vector<run> &results) {
    double time = 0;
    double deviation = 0;
    std::vector<double> times;
    for (int i = 0; i < samples; i++) {
        // Copy the vector
        std::vector<int> copy = vec;
        // Start the timer
        auto start = std::chrono::high_resolution_clock::now();
        //sort(copy);
        //std::sort(copy.begin(), copy.end());
        sort(copy, 0, N - 1);
        auto end = std::chrono::high_resolution_clock::now();
        // Calculate the duration
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
        // Add the duration to the total time
        time += duration.count();
        times.push_back(duration.count());
    }
    // Calculate the average time
    time /= samples;
    // Calculate the standard deviation
    deviation = std_dev(times);
    // Create a run and add it to the results
    results.push_back(create_run(N, time, deviation, samples));
}


int main() {

    std::vector<run> results;

    int N = 2000;
    int samples = 5;
    while(N <= 20000) {
        std::vector<int> vec;
        std::vector<int> const_vec(N, 10);
        generate_rising(N, vec);
        run_time(vec, quicksort_piv_right, N, samples, results);
        N += 1000;
    }

    write_to_file(results, "qsr_ris.txt");

    return 0;
}