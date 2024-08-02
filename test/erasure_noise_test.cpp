// Test to see how random our random number is on long data sets

#include <iostream>
#include <vector>
#include <algorithm> // For std::count
#include <iomanip> // for std::setprecision and std::scientific


// In include folder
#include "noise.h"

// Generates a test vector full of either zeros or ones
std::vector<int> generate_vector(int length, bool zeros);

// Estimates noise or erasure probability by counting how many zeros or ones have changed
double calculate_probability(std::vector<int> input_vector, int length,  bool zeros);

int main(int argc, char** argv){

    std::cout << "This code tests the noise functions to ensure the random number generator works properly" << std::endl;
    std::cout << "Given a probability, this code will generate a sample data set and return either a noise or erasure percentage" << std::endl;
    std::cout << "Then it will compare it to the original probability and see if it is within spec." << std::endl;
    std::cout << "Command line arguments are " << std::endl;
    std::cout << "[Probability to be test] [Length of test array]" << std::endl;

    if (argc != 3){
        std::cout << "ERROR: you have entered an incorrect amount of arguments, try again"  << std::endl;
        return 1;
    }

    // Grabbing values from input
    double test_probability = std::stod(argv[1]);
    int test_length = std::stoi(argv[2]);

    // first test noise function from noise.h
    std::vector<int> test_vector_zero = generate_vector(test_length, true);

   
    // Inserts noise 
    test_vector_zero = signalNoise(test_vector_zero, test_probability);

    
    // Calculate actual noise probability

    double calculated_probability = calculate_probability(test_vector_zero, test_length, true);

    std::cout << std::scientific;
    std::cout << std::setprecision(5);
    std::cout << "calculated probability is " << std::scientific << std::setprecision(15) << calculated_probability << " compared to " << test_probability << std::endl;

    // Calculate percentage difference
    double percent_diff = ((test_probability - calculated_probability)/ test_probability) * 100;
    std::cout << "Percent Difference: " << percent_diff << std::endl;

    return 0;
}

// Generates a test vector full of either zeros or ones
std::vector<int> generate_vector(int length, bool zeros){
    int x = 0;
    if (zeros != true){
        int x = 1;
    }

    // Fill vector based on length
    std::vector test_vec(length, x);

    return test_vec;

}

double calculate_probability(std::vector<int> input_vector, int length,  bool zeros){
    int x = 1;
    if (zeros != true){
        int x = 0;
    }

    int num = std::count(input_vector.begin(), input_vector.end(), x);

   
    double result = static_cast<double>(num) / length;

    return result;
}
