#include "utils.h"

#include <random>

size_t generate_random_size_t(size_t max) {
	std::random_device rd;
	std::mt19937 engine(rd());

	std::uniform_int_distribution<size_t> dist(0, max);

	return dist(engine);
}

const char* generate_random_cstr(size_t length, size_t max_char) {
	assert(max_char <= 255);

	std::random_device rd;
	std::mt19937 engine(rd());

	// Define a uniform integer distribution to get a random index
	std::uniform_int_distribution<size_t> dist(1, max_char);

	// Create the random string
	char* random_string = new char[length + 1];

	for (size_t i = 0; i < length; ++i) {
		random_string[i] = dist(engine);
	}

	random_string[length] = '\0';

	return random_string;
}
