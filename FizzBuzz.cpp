/*
 * FizzBuzz.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

vector<string> fizzBuzz(int A) {
	vector<string> result;

	for(unsigned int i = 1; i <= A; ++i){
		bool isDiv = false;
		stringstream ss;

		if((i % 3) == 0){
			ss<<"Fizz";
			isDiv = true;
		}
		if((i  % 5) == 0){
			ss<<"Buzz";
			isDiv = true;
		}
		if(!isDiv){
			ss<<i;
		}
		result.push_back(ss.str());
	}

	return result;
}




