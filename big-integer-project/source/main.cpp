/**
 *	Author: Haleeq Usman
 *
 *	This file contains the main executable/start point of program.
 *
 */

#include "include/globals.h"

void dec_to_binary32() {
	time_t start_time;
	double elapsed_time;
	BigInteger input;
	std::vector<char> output;
	std::vector<char>::const_iterator it;
	int i;

	std::cout << "Please enter a whole number (any length): ";
	std::cin >> input;

	std::cout << "Your number, " << input << ", in binary is:\n";

	start_time = time(NULL);

	while (1) {
		if((input % 2).isGTZero())
			output.push_back('1');
		else
			output.push_back('0');
		input /= 2;
		if(!input.isGTZero()) {
			break;
		}
	}

	size_t num_bits = 32;
	if(output.size() < num_bits) {
		num_bits -= output.size();
		for(i=0; i<num_bits; ++i) {
			output.push_back('0');
		}
	}
	reverse(output.begin(), output.end());
	i = 0;
	for(it = output.begin(); it != output.end(); ++it) {
		++i;
		std::cout << *it;
		if(i % 4 == 0)
			printf(" ");
	}
	printf("\n");

	// Let's measure how long it took to hit the end of the function
	elapsed_time = difftime(time(NULL), start_time);
	printf(
			"The function sum_ints_fast() took ~%.2lf seconds --> ~%.2lf minutes\n",
			elapsed_time, elapsed_time / 60);
}

int main() {
	dec_to_binary32();
	return 0;
}
