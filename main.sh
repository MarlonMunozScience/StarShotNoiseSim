#!/bin/bash

# Variables defined for each step

# Input File Name located in the /input folder
input_file="input.txt"
output_RSCTrans="RSC.txt"

# Input file the PPM Encoder expects
input_ppmEncoder="RSC.txt"
output_ppmEncoder="RSC_PPM.txt"

# Input and Output files in Laser Noise Simulation
input_noise="RSC_PPM.txt"
output_noise="RSC_PPM_NOISE.txt"

# Variables of noise and erasures
noise_rate="1e-3"
erasure_rate="1e-3"

# Input and Output files \the PPM Decoder expects
input_ppmDecoder="RSC_PPM_NOISE.txt"
output_ppmDecoder="RSC_BINARY.txt"

# Input for the RSC Reciever 
input_RSCRecv="RSC_BINARY.txt"

echo "Starting Code"

# Step 1: Run the first Python script
python3 python_scripts/Reed-Solomon_transmitter.py $input_file $output_RSCTrans
# Outputs file called RSC.txt

# Ensure Python script succeeded
if [ $? -ne 0 ]; then
    echo "Python script 1 failed, exiting."
    exit 1
fi

# Compile the ppm Encoder
g++ -o ppmEncoder src/ppmEncoder.cpp

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    echo "Running the program..."
    # Run the compiled program
    ./ppmEncoder $input_ppmEncoder $output_ppmEncoder
else
    echo "Compilation failed."
fi

# Run the Main Laser comm simulation
./simulate $input_noise $output_noise $erasure_rate $noise_rate

# Compile the ppm Decoder
g++ -o ppmDecoder src/ppmDecoder.cpp

# Check if the compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful."
    echo "Running the program..."
    # Run the compiled program
    ./ppmDecoder $input_ppmDecoder $output_ppmDecoder
else
    echo "Compilation failed."
fi


# Run the RSC Receiver python code
python3 python_scripts/Reed-Solomon_receiver.py $input_RSCRecv