#pragma once

#ifndef NOISE_H
#define NOISE_H

#include <vector>

std::vector<int> signalErasure(std::vector<int> signalOriginal, double erasure_probability);

std::vector<int> signalNoise(std::vector<int> signalOriginal, double noise_probability);

#endif NOISE_H
