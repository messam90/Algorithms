/*
 * TrailingZerosInFactorial.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int trailingZeros_1(int A, int div){
    if(A / div == 0){
        return 0;
    }

    return floor(A / div) + trailingZeros_1(A, div * 5);
}

int trailingZeroes(int A) {
    return trailingZeros_1(A, 5);
}
