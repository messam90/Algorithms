/*
 * GreatestCommonDivisor.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int gcd(int A, int B){
	int result, gcd = (A < B) ? A : B;
	if(B == 0) result = A;
	else if(A == 0) result = B;
	else{
		for(unsigned int i = gcd; gcd >= 1; --i){
			if(A % i == 0 && B % i == 0){
				result = i;
				break;
			}
		}
	}
	return result;
}



