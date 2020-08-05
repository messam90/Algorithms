/*
 * PalindromeInteger.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int isPalindrome(int A){
	int result = true;
	string number;
	stringstream ss;

	ss<<A;
	number = ss.str();

	int i = 0;
	int j = number.length() - 1;

	while(i <= j){
		if(number[i++] != number[j--]){
			result = false;
			break;
		}
	}

	return result;
}



