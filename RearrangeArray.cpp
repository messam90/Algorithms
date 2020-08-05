/*
 * RearrangeArray.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

void arrange(vector<int> &A){
	const unsigned int carryOverMask = 0xFFFF0000;

	for(unsigned int i = 0; i < A.size(); ++i){
		unsigned int opResult = A[A[i]] & carryOverMask;
		if(opResult != 0){
			unsigned int carryOVer;
			A[i] = (unsigned int)A[i] << 16; //take caryover first;
			carryOVer = ((unsigned int)A[A[i] >> 16] >> 16);
			carryOVer = (carryOVer == ~carryOverMask)? 0 : carryOVer;
			A[(unsigned int)A[i] >> 16] &= ~carryOverMask; //clear other cell carry over
			A[i] |= carryOVer; //take other cell carry over
			if(((unsigned int)A[i] >> 16) == 0){
				A[i] |= carryOverMask; //mark carry over for 0
			}
		}else{
			unsigned int offset = 0;
			if(A[i] != A[A[i]]){
				A[i] = (unsigned int)A[i] << 16; //take caryover first;
				offset = (unsigned int)A[i] >> 16;
			}else{
				offset = A[i];
			}
			A[i] |= A[offset]; //take other cell value
		}
	}

	for(unsigned int i = 0; i < A.size(); ++i){
		A[i] &= ~carryOverMask;
	}


	/*unsigned int carryOver = 0;
	unsigned carryOverIndex = ~0;
	for(unsigned int i = 0; i < A.size(); ++i){
		unsigned int newCarryOver = A[i];
		if(carryOverIndex == A[i]){
			if(A[i] != A[A[i]]){
				carryOverIndex = i;
			}else {
				carryOverIndex = ~0;
			}
			A[i] = carryOver;
			carryOver = newCarryOver;
		}else if(A[i] != A[A[i]]){
			carryOver = newCarryOver;
			carryOverIndex = i;
			A[i] = A[A[i]];
		}
	}*/
}



/*
 *     for(auto i = 0U; i < A.size(); i++){
        int j = A[i];
        A[i] = A[A[j]];
        A[A[j]] = j;
    }
 */
