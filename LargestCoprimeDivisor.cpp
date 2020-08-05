/*
 * LargestCoprimeDivisor.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int gcd(int A, int B);

int cpFact(int A, int B) {
	int cPrime = A;
	for(; cPrime > 0; cPrime--){
		if(A % cPrime == 0 && gcd(cPrime, B) == 1){
			break;
		}
	}
	return cPrime;
}



