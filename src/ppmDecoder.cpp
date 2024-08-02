#include <iostream>
#include <fstream> //For reading files
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> openfile(std::string filename);

std::vector<int> ppmDecoding(std::vector<int> dataBinary);

void writeFile(std::vector<int> intData, std::string output_file);

// Overloading << Operator to print everything the vector
template <typename S>
std::ostream& operator<<(std::ostream& os,
    const std::vector<S>& vector)
{
    // Printing all the elements
    // using <<
    for (auto element : vector) {
        os << element << "\n";
    }
    return os;
}



int main(int argc, char** argv)
{
    // Read in file
    // Expects data in terms of txt file named binaryData.txt
    
    std::string input_file = argv[1];

    // Reads file, returns vector of integers
    std::vector<int> dataBinary = openfile(std::string("output/") + input_file);

    // Converts binary ppm back into 8 bit
    std::vector<int> dataInt = ppmDecoding(dataBinary);

    // Writes to file
    writeFile(dataInt, argv[2]);

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


std::vector<int> ppmDecoding(std::vector<int> dataBinary){
     // Output vector we will write to
    std::vector<int> ppmDecoded;
    
    const size_t chunkSize = 256;
    auto start = dataBinary.begin();
    auto end = dataBinary.end();

    int target = 1;

    // Find the first 1 in the ppm frame

    while  (start < end){
        
        // Determine the end of the current chunk
        auto chunkEnd = (start + chunkSize < end) ? start + chunkSize : end;
        

        // Use std::find to search within the current chunk
        auto it = std::find(start, chunkEnd, target);


        if (it != chunkEnd) {
            // If found, check if there is another 1 in the current chunk
        
            //return the index of the found element
            ppmDecoded.push_back((it - dataBinary.begin()) % 256);
        }
        else{
            ppmDecoded.push_back(0);
        }

        // Move to the next chunk
        start = chunkEnd;


    }

    return ppmDecoded;

}


void writeFile(std::vector<int> intData, std::string output_file){
    std::ofstream outfile(std::string("output/") + output_file);
    outfile << intData << std::endl;
    outfile.close();

    return;

}