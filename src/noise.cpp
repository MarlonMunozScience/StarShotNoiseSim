#include <cstdlib>
#include <string>
#include <ctime>
#include <random>
#include <iomanip>
#include <iostream>

#include "noise.h"

// Introduces erasures by turning ones into zeros
std::vector<int> signalErasure(std::vector<int> signalOriginal, double erasure_probability) {
    // Index through each element of the original signal, roll a random number and if it is higher, erase the value
   // To safe time, we only have to do this with values that are 1.

     /* Seed */
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0, 0x000000003B9ACA00);

    int counter = 0; //used to index elements later
    //Looping through the original signal
    for (auto element : signalOriginal) {
        if (element == 1) { // only worried about slots with signal photons

            // Generate a random number between 0 and 1 with 8 decimal point precision
            double random = distribution(generator) / 1000000000.0;

            if (random < erasure_probability) {
                signalOriginal[counter] = 0;
                
            }

        }
        counter++;
    }
    
    return signalOriginal;
}

// Introduces noise by turning zeros into ones
std::vector<int> signalNoise(std::vector<int> signalOriginal, double noise_probability) {
    // Index through each element of the original signal, roll a random number and if it is higher, add noise
   // To safe time, we only have to do this with values that are 0.

    /* Seed */
    std::random_device rd;

    /* Random number generator */
    std::default_random_engine generator(rd());

    /* Distribution on which to apply the generator */
    std::uniform_int_distribution<long long unsigned> distribution(0, 0x000000003B9ACA00);

    int counter = 0; //used to index elements later
    //Looping through the original signal
    for (auto element : signalOriginal) {
        if (element == 0) { // only worried about slots with signal photons

            // Generate a random number between 0 and 1 with 8 decimal point precision
            double random = distribution(generator) / 1000000000.0;


            if (random < noise_probability) {
                signalOriginal[counter] = 1;
            }

        }
        counter++;
    }

    return signalOriginal;
}

