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

vector<int> intersect(const vector<int> &A, const vector<int> &B) {
	int i = 0;
	const vector<int> *smaller_array, *bigger_array;
	vector<int> result;

	if(A.size() < B.size()){
		smaller_array = &A;
		bigger_array = &B;
	}else{
		smaller_array = &B;
		bigger_array = &A;
	}

	for(auto j = 0u; j < smaller_array->size();){
		if((*smaller_array)[j] == (*bigger_array)[i]){
			result.push_back((*smaller_array)[j]);
			j++;
		}
		i++;
	}

	return result;
}

vector<vector<int> > threeSum(vector<int> &A) {
	unordered_set<int> temp_set;
	vector<vector<int>> result;

	if(A.size() < 3) return result;

	for(auto i = 0; i < A.size() - 1; ++i){
		unordered_set<long long> temp_set;

		for(auto j = i + 1; j < A.size(); ++j){
			long long sum = -1 * ((long long)A[i] + (long long)A[j]);

			if(temp_set.find(sum) != temp_set.end()){
	            multiset<int> temp{A[i], A[j], (int)sum};
	            vector<int> temp_vector;
	            for(auto it = temp.begin(); it != temp.end(); ++it){
	                temp_vector.push_back(*it);
	            }
	            if(find(result.begin(), result.end(), temp_vector) == result.end()){
	                result.push_back(temp_vector);
	            }
			}else{
				temp_set.insert(A[j]);
			}
		}
	}

	return result;

	/**
	 *     int i = 0, j = i + 1, k = j + 1;
    vector<vector<int>> result;

    if(A.size() < 3) return result;

    while(i < A.size() - 2){
        if((long long)A[i] + (long long)A[j] + (long long)A[k] == 0){
            multiset<int> temp{A[i], A[j], A[k]};
            vector<int> temp_vector;
            for(auto it = temp.begin(); it != temp.end(); ++it){
                temp_vector.push_back(*it);
            }
            if(find(result.begin(), result.end(), temp_vector) == result.end()){
                result.push_back(temp_vector);
            }
        }
        k++;
        if(k == A.size()){
            j++;
            k = j + 1;
        }
        if(j == A.size() - 1){
            i++;
            j = i + 1;
            k = j + 1;
        }
    }

    return result;
	 */
}

//////////////////////////////////////////////////////
void test_threeSum(){
	vector<int> A{-1, 0, 1, 2, -1, -4};
	auto result = threeSum(A);
	for(auto a : result){
		for(auto b : a){
			cout<<b<<" ";
		}
		cout<<endl;
	}
}

void test_intersect(){
	vector<int> A{1, 2, 3, 3, 4, 5, 6}, B{3, 3, 5};
	auto result = intersect(A, B);
	for(auto a : result){
		cout<<a<<" ";
	}
}

