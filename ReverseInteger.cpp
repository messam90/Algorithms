/*
 * ReverseInteger.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int reverseInt(int A) {
	bool negNum = false;
	int result = 0;
	unsigned int numDigits = 1;
	unsigned long long tempNum;

	if(A < 0){
		negNum = true;
		A *= -1;
	}
	tempNum = A;

	while(tempNum >= 10){
		numDigits++;
		tempNum /= 10;
	}
	tempNum = 0;

	while(A >= 10){
		tempNum += (A % 10) * pow(10, numDigits - 1);
		numDigits--;
		A /= 10;
	}
	tempNum += A * pow(10, numDigits - 1);
	result = (negNum) ? -1 * tempNum : tempNum;

	if(abs(result) != tempNum){
		result = 0;
	}

	return result;
}



/*int getNumDigits(int A){
    int num = 0;

    while(A > 0){
        num++;
        A /= 10;
    }

    return num;
}

int Solution::reverse(int A) {
        bool positive = true;
    int tempNum = A;

    if(A < 0){
        positive = false;
        tempNum *= -1;
    }

    int numDigits = getNumDigits(tempNum);
    int power = getNumDigits(tempNum) - 1;
    int reversedNum = 0;
    int remainder = 0;
    int result = tempNum;
    for(auto i = 0; i < numDigits; i++){
        remainder = result % 10;
        result /= 10;
        reversedNum += remainder * ceil(pow(10.0, (double)power));
        power--;
    }

    if(reversedNum < 0){
        return 0;
    }else{
        if(!positive){
            reversedNum *= -1;
        }

        return reversedNum;
    }
}*/
