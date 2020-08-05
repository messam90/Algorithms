/*
 * PrimeSum.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

bool isPrime(unsigned int A){
	bool result = true;

	for(unsigned int i = 2; i < (A / 2); ++i){
		if(A % i == 0){
			result = false;
			break;
		}
	}

	return result;
}

vector<int> primesum(int A){
	vector<int> result(2, 0);

	if(A == 4){
		result[0] = 2;
		result[1] = 2;
	}else{
		for(unsigned int i = 3; i <= (A / 2); i += 2){
			unsigned int diff = A - i;

			if(diff % 2 != 0 && isPrime(i) && isPrime(diff)){
				result[0] = i;
				result[1] = diff;
				break;
			}
		}
	}

	return result;
}



