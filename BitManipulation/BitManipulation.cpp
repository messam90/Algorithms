/*
 * BitManipulation.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int numSetBits(unsigned int A) {
	int count = 0;
	while(A != 0){
		A &= (A - 1);
		count++;
	}
	return count;
}

int findMinXor(vector<int> &A) {
	unsigned int minXor = (unsigned int)~0;
	vector<int> tempA(A);

	sort(tempA.begin(), tempA.end());

	for(auto i = 0u; i < tempA.size() - 1; ++i){
		unsigned int tempXor = tempA[i] ^ tempA[i + 1];
		minXor = min(minXor, tempXor);
	}

	return minXor;
}

int singleNumber(const vector<int> &A) {
	int result = 0;

	for(auto i = 0u; i < sizeof(int) * 8; ++i){
		int mask = 1 << i, sum = 0;

		for(auto j = 0u; j < A.size(); ++j){
			if(A[j] & mask){
				sum++;
			}
		}

		if(sum % 2 != 0){
			result |= mask;
		}
	}

	return result;
}

