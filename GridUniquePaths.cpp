/*
 * GridUniquePaths.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int uniquePaths(int A, int B) {
    if(A == 1 || B == 1){
        return 1;
    }

    return uniquePaths(A - 1, B) + uniquePaths(A, B - 1);
}



