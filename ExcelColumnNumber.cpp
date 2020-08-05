/*
 * ExcelColumnNumber.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int titleToNumber(string A){
	int result = 0;
	unsigned int stringLen = A.length();

	for(unsigned int index = 0; index < stringLen; ++index){
		result += ((unsigned int)A[stringLen - 1 - index] - 'A' + 1) * (pow(26,index));
	}

	return result;
}



