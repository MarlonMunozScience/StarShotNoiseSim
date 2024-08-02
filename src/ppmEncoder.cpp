#include <iostream>
#include <fstream> //For reading files
#include <string>
#include <vector>

std::vector<int> openfile(std::string filename);

std::vector<int> ppmEncoding(std::vector<int> data256);
void writeFile(std::vector<int> binaryData, std::string output_file);

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


int main(int argc, char** argv)
{

    // Read in file
    // Expects data in terms of txt file named encoded_msg.txt
    
    std::string input_file = std::string("output/") + argv[1];

    // Reads file, returns vector of integers
    std::vector<int> data8bit = openfile(input_file);

    // Convert 8 bit into binary ppm 
    std::vector<int> dataBinary = ppmEncoding(data8bit);

    // Write to file 
    writeFile(dataBinary, argv[2]);    
    return 0;

    
}


// Opens the provided file with error handling
// Returns vector of signal photons
std::vector<int> openfile(std::string filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file :C";
    }

    std::vector<int>  inputData;

    int element;

    //Reads elements from the file and appends them to the vector
    while (inputFile >> element) {
        inputData.push_back(element);
    }

    

    return inputData;
}


std::vector<int> ppmEncoding(std::vector<int> data256){

    // Output vector we will write to
    std::vector<int> ppmEncoded;
    // Cycle through each item in the data, 
    for(const int& element : data256){ 

        // For each element, create 256 zeros
        for(int i = 0; i < 256; i++){
            if (element != i){
                ppmEncoded.push_back(0);
            }
            else{
                ppmEncoded.push_back(1);
            }

        }
    }
    return ppmEncoded;
}

void writeFile(std::vector<int> binaryData, std::string output_file){
    std::ofstream outfile(std::string("output/") + output_file);
    outfile << binaryData << std::endl;
    outfile.close();

    return;

}