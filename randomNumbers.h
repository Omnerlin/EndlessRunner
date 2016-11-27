#pragma once
#include <random>

float generateRandomFloat(int min, int max) {
	/*int randed = std::rand();
	float randomNumber = (randed % max) + min;
	return randomNumber;*/

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range

	
	return distr(eng); // generate numbers
}