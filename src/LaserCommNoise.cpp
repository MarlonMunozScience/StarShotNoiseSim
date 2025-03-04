




#include <iostream>
#include <fstream> //For reading files
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <random>

#include "noise.h"




// Overloading << Operator to print everything the vector
template <typename S>
std::ostream& operator<<(std::ostream& os,
    const std::vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << " ";
    }
    return os;
}

// Opens the provided file with error handling
// Returns vector of signal photons
std::vector<int> openfile(std::string filename);

//Takes in ASCII vector, converts it to binary
std::vector<int> ASCIItoBinary(std::vector<int> signalPhotons);

// Converts an ASCII vector back into binary
std::vector<int> BinarytoASCII(std::vector<int> BinaryVector);


int main(int argc, char** argv)
{
    // Script expects 3 arguments: Name of noise file in 'Noise' folder, erasure probability, and noise probability 
    
    // If user does not input correct amount of commands
    // Handling each input
    for (int i = 0; i < argc; i++) {
        if (std::string(argv[i]) == "-h") {
            std::cout << "This code inserts noise and erasures into a ASCII file.";
            std::cout << "The input file must be placed in the 'Noise' Folder" << std::endl;
            std::cout << "Command Line arguments are: \n" << std::endl;
            std::cout << "[Name of Input] [Name of Output] [Erasure Probability] [Noise Probability]" << std::endl;
            return 0;
        }
    }
    if (argc != 5) {
        std::cout << "You have entered an incorrect amount of arguments. Use -h for help." << std::endl;
        return 0;
    }


    // Input file 
    std::string input_file = argv[1];
    std::string output_file = argv[2];

    // Add the noise folder to the input:
    //input_file = "binaryData.txt";

    // Erasure Probability
    double erasure_prob = std::stod(argv[3]);

    // Noise probability
    double noise_prob = std::stod(argv[4]);

    // Opening file
    //std::string fname = R"(Noise\test.txt)";
    std::vector<int> signal = openfile(std::string("output/") + input_file);

    //Printing all the elements
    //std::cout << signal << std::endl;

    // Convert input vector into binary for processing
    //std::vector<int> signalBinary = ASCIItoBinary(signal);
    //std::cout << signalBinary << std::endl;

    // Introduce Erasures
    std::vector<int> signalErasured = signalErasure(signal, erasure_prob);
    //std::cout << "\n" << signalErasured << std::endl;
    
    // Introduce Noise
    std::vector<int> signalNoised = signalNoise(signalErasured, noise_prob);
    //std::cout << "\n" << signalNoised << std::endl;

    // Turning Binary back into ASCII
//std::vector<int> outputASCII = BinarytoASCII(signalNoised);
    //std::cout << "Binary Output\n" << outputBinary << std::endl;

    //Writes the vector to an output file
    std::ofstream outfile(std::string("./output/") + output_file );
    outfile << signalNoised << std::endl;
    outfile.close();


    return 0;
}

// Opens the provided file with error handling
// Returns vector of signal photons
std::vector<int> openfile(std::string filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file :C";
    }

    std::vector<int> signalPhotons;

    int element;

    //Reads elements from the file and appends them to the vector
    while (inputFile >> element) {
        signalPhotons.push_back(element);
    }


    return signalPhotons;
}


//Takes in ASCII vector, converts it to binary
std::vector<int> ASCIItoBinary(std::vector<int> signalPhotons) {
    // ASCII vectors come in form of <number of zeros> <number of signal photons>
    std::vector<int> signalBinary;

    int count = 0; // Counter to help us keep track if we are counting zeros or ones

    for (auto element : signalPhotons) {
        // for zeros
        if (count == 0)
        {
            for (int i = 0; i < element; i++) {
                signalBinary.push_back(0);
            }
            count = 1; //switching for next case
        }
        else // for signal photons
        {
            for (int i = 0; i < element; i++) {
                signalBinary.push_back(1);
            }
            count = 0; // switching for the next case
        }
    }

    return signalBinary;

}


std::vector<int> BinarytoASCII(std::vector<int> BinaryVector) {
    int counter = 0; // Internal Counter

    std::vector<int> BinaryOutput; // Output Vector
    for (auto element : BinaryVector) {
        if (element == 0) {
            counter++;
        }
        else {
            BinaryOutput.push_back(counter);
            BinaryOutput.push_back(1);
            counter = 0;
        }
    }

    return BinaryOutput;
}