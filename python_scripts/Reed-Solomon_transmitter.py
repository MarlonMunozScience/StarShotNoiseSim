# -*- coding: utf-8 -*-
"""
Created on Tue Aug  8 17:24:36 2023

@author: Marlon
"""


# TODO:
"""
- Inputs to script (location mainly)

"""

from reedsolo import RSCodec, ReedSolomonError
import numpy as np
import sys

# Define message parameters: information and ECC characters per chunk
INFO_LENGTH = 4
EEC_LENGTH = 8
CHUNKS_LENGTH = INFO_LENGTH + EEC_LENGTH
OUTPUT_FILE_NAME = sys.argv[2]
OUTPUT_FILE = 'output/' + OUTPUT_FILE_NAME

def save_data(data):
    with open(OUTPUT_FILE, 'w') as f:
        for element in data[:-1]:
            f.write(str(element) + '\n')
        f.write(str(data[-1]))
    return None

def read_input_file(file_path):
    with open(file_path, 'r') as file:
        file_contents = file.read()
        trans_message = file_contents
        return trans_message.encode()


codec = RSCodec(EEC_LENGTH)
input_file_name = sys.argv[1] # Takes in the command line argument, which should be file name
trans_msg = read_input_file('input/' + input_file_name) # Message that we want to send (change it to whatever)
trans_msg = list(trans_msg) # Generate a list of bytes (from 0 to 255)

# Divide message in chunks of specified length
msg_chunks = []
for i in range(0, len(trans_msg), INFO_LENGTH):
    msg_chunks.append(trans_msg[i:i+INFO_LENGTH])

# Append ECC symbols at the end of each chunk and reshape into 1D list 
encoded_msg = []
for chunk in msg_chunks:
    encoded_msg += codec.encode(chunk)

# Save results in RSC.txt file
save_data(encoded_msg)

