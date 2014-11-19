// CMPS 109 HW06
// HEX BORAD PRESENTATION

#include <iostream>
#include <ctime>
#include "GraphHex.h"
#include <omp.h>

int main(void)
{
	srand(time(0));
	Graph one ;		// default size 11; if you want to change it please go to GraphHex.h
	
	one.playGame(); // randomly fill the graphs

	std::cout << std::endl << std::endl;

	std::cout << "Thank you for running." << std::endl;
}  