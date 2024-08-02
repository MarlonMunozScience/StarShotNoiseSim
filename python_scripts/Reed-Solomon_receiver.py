# -*- coding: utf-8 -*-
"""
Created on Tue Aug  8 17:58:20 2023

@author: Marlon
"""

from reedsolo import RSCodec, ReedSolomonError
import numpy as np
import sys

# Define message parameters - NEED TO BE THE SAME AS RECEIVER'S PARAMS
INFO_LENGTH = 4 # RSC addenum   
EEC_LENGTH = 8 # RSC block
CHUNKS_LENGTH = INFO_LENGTH + EEC_LENGTH

INPUT_FILE = 'output/' + sys.argv[1] # Change to input folder

codec = RSCodec(EEC_LENGTH)

file = open(INPUT_FILE, "r") #  Open the .txt file
text = file.readlines() # Create a list where the elements are each of the lines from the file in string form
#rec_msg = [int(float(element)) for element in text] # Convert each entry to an integer
rec_msg = []
for element in text:
    try:
        rec_msg.append(int(float(element)))
    except:
        pass

# Start by decomposing the received message into chunks
rec_msg_chunks = []
for i in range(0, len(rec_msg), CHUNKS_LENGTH):
    rec_msg_chunks.append(rec_msg[i:i+CHUNKS_LENGTH])

decoded_msg = []
for chunk in rec_msg_chunks:
    decoded_chunk = list(codec.decode(chunk)[0])
    
    if len(chunk) == CHUNKS_LENGTH:
        decoded_msg += decoded_chunk
    else:
        decoded_msg += decoded_chunk[:CHUNKS_LENGTH - len(chunk)]

message = ''
for ASCII_val in decoded_msg:
    message += chr(ASCII_val) # Transform ASCII values to characters and append them on the message string
    
print(message) # Print final message
