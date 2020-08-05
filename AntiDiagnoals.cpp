/*
 * AntiDiagnoals.cpp
 *
 *  Created on: Jul 4, 2020
 *      Author: messam
 */
#include "Headers.hpp"

vector<vector<int>> diagonal(vector<vector<int>> &A) {
	vector<vector<int>> result;

	if(A.size() > 0){
		vector<int> row(1, A[0][0]);
		result.push_back(row);

		int i = 0;
		int j = 1;

		while(i < A.size()){
			vector<int> row;
			int tempI = i;
			int tempJ = j;

			while(tempJ >= 0 && tempI < A.size()){
				row.push_back(A[tempI][tempJ]);
				tempJ--;
				tempI++;
			}

			j++;
			if(j == A.size()){
				j--;
				i++;
			}
			result.push_back(row);
		}
	}

	return result;
}

enum class incrementType_t{INCREMENT_I, INCREMENT_J, DECREMENT_I, DECREMENT_J};

vector<vector<int>> diagonal_2(vector<vector<int>> &A){
	vector<vector<int>> result;
	unsigned int numRows = A.size();
	incrementType_t incrementType{incrementType_t::INCREMENT_J};

	if(numRows > 0){
		vector<int> row(1, A[0][0]);
		result.push_back(row);
		row.clear();

		int i = 0;
		int j = 1;
		int tempI = i;
		int tempJ = j;
		for(unsigned int index = 1; index < numRows * numRows; ++index){
			row.push_back(A[tempI][tempJ]);

			tempI++;
			if(tempI == numRows){
				tempI = ++i;
				tempJ = j;
				result.push_back(row);
				row.clear();
			}else{
				tempJ--;
				if(tempJ < 0){
					tempJ = ++j;
					tempI = i;
					result.push_back(row);
					row.clear();
				}
			}
		}
	}

	return result;
}

