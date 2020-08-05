/*
 * PascalTriangle.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: messam
 */
#include "Headers.hpp"

void generateRow(vector<vector<int>>& triangle, unsigned int rowNum){
	if(rowNum == 1){
		vector<int> temp(1, 1);
		triangle.push_back(temp);
		return;
	}

	generateRow(triangle, rowNum - 1);

	if(rowNum == 2){
		vector<int> temp(2, 1);
		triangle.push_back(temp);
	}else{
		vector<int> temp(rowNum, 1);

		temp[1] = rowNum - 1;
		temp[temp.size() - 2] = rowNum - 1;

		for(unsigned int index = 2; index < temp.size() - 1; ++index){
			temp[index] = triangle[rowNum - 2][index] + triangle[rowNum - 2][index - 1];
		}

		triangle.push_back(temp);
	}
}

vector<vector<int>> generateTriangle(int A){
	vector<vector<int>> triangle;

	generateRow(triangle, A);

	return triangle;
}

vector<int> generateRow_2(unsigned int k){
	vector<int> row(k + 1 + 1, 1);

	for(unsigned int rowIndex = 2; rowIndex < k + 1; ++rowIndex){
		unsigned int prevValue_1 = row[0];
		unsigned int prevValue_2 = row[1];

		for(unsigned int columnIndex = 1; columnIndex < rowIndex; ++columnIndex){
			unsigned int temp = 0;

			temp = prevValue_1 + prevValue_2;
			prevValue_1 = prevValue_2;
			prevValue_2 = row[columnIndex + 1];
			row[columnIndex] = temp;
		}
	}

	row.erase(row.begin() + row.size() - 1);
	return row;
}
