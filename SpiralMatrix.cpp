/*
 * SpiralMatrix.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: messam
 */
#include "Headers.hpp"

enum class incrementType{INCREMENT_J, INCREMENT_I, DECREMENT_J, DECREMENT_I};

void increment(unsigned int &i, unsigned int& j, incrementType incrementDirection){
    switch(incrementDirection){
      case incrementType::INCREMENT_J: j++; break;
      case incrementType::INCREMENT_I: i++; break;
      case incrementType::DECREMENT_J: j--; break;
      case incrementType::DECREMENT_I: i--; break;
    }
}

vector<vector<int>> generateMatrix(int A) {
  const unsigned int matrixInitValue = 0;
  vector<int> row(A, matrixInitValue);
  vector<vector<int>> matrix(A, row);

  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int count = 1;
  incrementType incrementDirection{incrementType::INCREMENT_J};

  for(unsigned int index = 0; index < A*A; index++){
    matrix[i][j] = count++;

    increment(i, j, incrementDirection);

    if(i >= 4 || j >= 4 || matrix[i][j] != matrixInitValue){
      //already filled, change direction
      switch(incrementDirection){
        case incrementType::INCREMENT_J: j--; incrementDirection = incrementType::INCREMENT_I;
        break;
        case incrementType::INCREMENT_I: i--; incrementDirection = incrementType::DECREMENT_J;
        break;
        case incrementType::DECREMENT_J: j++; incrementDirection = incrementType::DECREMENT_I;
        break;
        case incrementType::DECREMENT_I: i++; incrementDirection = incrementType::INCREMENT_J;
        break;
      }

      increment(i, j, incrementDirection);
    }
  }

  return matrix;
}




