#include "evaluator.h"
#include "../deck/card.h"
#include <iostream>
//g++ -std=c++23 -I./src/deck -I./src/evaluator ./src/evaluator/tester.cpp ./src/deck/card.cpp ./src/evaluator/evaluator.cpp -o tester
//   As an example, the Five of Hearts would be represented as
//
//   +--------+--------+--------+--------+
//   |00000000|00001000|00100011|00000111| = 0x00082307
//   +--------+--------+--------+--------+
//
//   and the Queen of Clubs would be represented as
//
//   +--------+--------+--------+--------+
//   |00000100|00000000|10001010|00011111| = 0x04008A1F
//   +--------+--------+--------+--------+
int main() {
	Card testerCard(QUEEN, CLUBS);
	int encoded = encodeCard(testerCard);
	std::cout << "Encoded card: " << std::hex << encoded << std::dec << "\n";
	return 0;
}