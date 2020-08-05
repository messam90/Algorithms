/*
 * TwoPointers.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: messam
 */
#include "Headers.hpp"

void merge(vector<int> &A, vector<int> &B) {
	if(A.size() == 0){
		A = B;
	}else{
		/*for(auto indexB = 0u; indexB < B.size(); ++indexB){
			auto indexA = A.size() - 1;

			if(B[indexB] <= A[0]){
				A.insert(A.begin(), B[indexB]);
			}else if(B[indexB] >= A[A.size() - 1]){
				A.insert(A.end(), B[indexB]);
			}else{
				for(; indexA > 0; --indexA){
					if(B[indexB] < A[indexA] && B[indexB] > A[indexA - 1]){
						A.insert(A.begin() + indexA, B[indexB]);
					}else if(B[indexB] == A[indexA]){
						A.insert(A.begin() + indexA, B[indexB]);
					}
				}
			}
		}*/

		unsigned int indexA = 0, indexB = 0, elementsNum = A.size() + B.size();
		vector<int> C(elementsNum, 0);

		for(auto indexC = 0u; indexC < elementsNum; ++indexC){
			if(indexA < A.size() && indexB < B.size()){
				if(A[indexA] < B[indexB]){
					C[indexC] = A[indexA++];
				}else if(B[indexB] < A[indexA]){
					C[indexC] = B[indexB++];
				}else{
					C[indexC++] = A[indexA++];
					C[indexC] = B[indexB++];
				}
			}else if(indexA < A.size()){
				C[indexC] = A[indexA++];
			}else{
				C[indexC] = B[indexB++];
			}

		}

		A = C;
	}
}

int threeSumClosest(vector<int> &A, int B) {
	int closestSum = ~0;
	vector<int> tempA(A);
	sort(tempA.begin(), tempA.end());

	for(auto i = 0u; i < tempA.size() - 2; ++i){
		unsigned int j = i + 1, k = A.size() - 1;

		while(j != k){
			int sum = tempA[i] + tempA[j] + tempA[k];

			if((i == 0 && j == 1 && k == A.size() - 1) || abs(B - sum) < abs(B - closestSum)){
				closestSum = sum;
			}

			if(sum > B){
				k--;
			}else if(sum < B){
				j++;
			}else{
				i = tempA.size();
				break;
			}
		}

	}

	return closestSum;
}


