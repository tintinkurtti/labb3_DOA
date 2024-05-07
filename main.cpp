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

int number_of_primes(std::vector<bool> &primes){
    int count = 0;
    for (auto index : primes){
        if (index){
            count += 1;
        }
    }
    return count;
}

std::vector<bool> create_primes(int N){
    int size = N * log(N) * 1.2;
    std::vector<bool> primes(size, true);
    primes[0] = false;
    primes[1] = false;
    int i = 2;
    while(i < size/2){
        int divisor = i * 2;
        while(divisor <= size){
            primes[divisor] = false;
            divisor += i;
        }
        i++;
        while(!primes[i]){
            i++;
        }
    }
    return primes;
}

std::vector<int> create_prime_vec(int N) {
    std::vector<bool> primes = create_primes(N);
    std::vector<int> prime_vec;
    for(int i = 0; prime_vec.size() < N ; i++){
        if (primes[i]){
            prime_vec.push_back(i);
        }
    }
    return prime_vec;
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

void run_time(std::vector<int> &vec, bool (*search)(Node* root, int a), int N, int samples, std::vector<run> &results) {
    double time = 0;
    double deviation = 0;
    std::vector<double> times;
    for (int i = 0; i < samples; i++) {
        // Copy the vector
        std::vector<int> copy = vec;
        // Start the timer
        // Create the binary tree
        Node* root = create_binary_tree(copy, 0, copy.size() - 1);
        auto start = std::chrono::high_resolution_clock::now();


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

    std::vector<int> primes = create_prime_vec(100);

    Node *rootPointer = nullptr;
    rootPointer= create_binary_tree(primes, 0, primes.size() - 1);
    printBinaryTree(rootPointer, "");



    return 0;
}