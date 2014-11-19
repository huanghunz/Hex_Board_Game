
// HEX BORAD GAME

#include <iostream>
#include <ctime>
#include "GraphHex.h"
#include <omp.h>

int main(void)
{
	srand(time(0));
	Graph one ;		// board size is 11x11
	
	one.playGame(); // randomly fill the graphs

	std::cout << std::endl << std::endl;

	std::cout << "Thank you for running." << std::endl;
}  