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
	unordered_multimap<int, pair<int, int>> temp_map;
	vector<vector<int>> result;

	if(A.size() < 3) return result;

	for(auto i = 0; i < A.size() - 1; ++i){
		unordered_set<long long> temp_set;

		for(auto j = i + 1; j < A.size(); ++j){
			long long sum = -1 * ((long long)A[i] + (long long)A[j]);

			if(temp_set.find(sum) != temp_set.end()){
	            multiset<int> temp{A[i], A[j], (int)sum};
	            vector<int> temp_vector;
	            auto it_range = temp_map.equal_range(*temp.begin());
	            bool found = false;
	            auto it_1 = temp.begin(), it_2 = temp.begin();
	            advance(it_1, 1);
	            advance(it_2, 2);
	            for(auto it = it_range.first; it != it_range.second; ++it){
	            	if(it->second.first == *it_1 && it->second.second == *it_2){
	            		found = true;
	            		break;
	            	}
	            }

	            if(!found){
		            for(auto it = temp.begin(); it != temp.end(); ++it){
		                temp_vector.push_back(*it);
		            }
		            result.push_back(temp_vector);
		            temp_map.insert(pair<int, pair<int, int>>{*temp.begin(), pair<int, int>{(const int)*it_1, (const int)*it_2}});
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

int nTriang(vector<int> &A) {
	vector<int> B(A);
	sort(B.begin(), B.end());

	int i = 0, j = i + 1, k = j + 1, result = 0;

	if(B.size() < 3) return 0;

	while(i < B.size() - 2){
		if(B[i] + B[j] > B[k] &&
				B[i] + B[k] > B[j] &&
				B[j] + B[k] > B[i]){
			result++;
			k++;
		}else{
			j++;
			k = j + 1;
		}

		if(k == B.size()){
			j++;
			k = j + 1;
		}
		if(j >= B.size() - 1){
			i++;
			j = i + 1;
			k = j + 1;
		}
	}

	return result;

   /* vector<int> B(A);
    // Sort the array elements in non-decreasing order
    sort(B.begin(), B.end());

    // Initialize count of triangles
    int count = 0;

    // Fix the first element. We need to run till n-3
    // as the other two elements are selected from
    // arr[i+1...n-1]
    for (int i = 0; i < B.size() - 2; ++i) {
        // Initialize index of the rightmost third
        // element
        int k = i + 2;

        // Fix the second element
        for (int j = i + 1; j < B.size(); ++j) {
            // Find the rightmost element which is
            // smaller than the sum of two fixed elements
            // The important thing to note here is, we
            // use the previous value of k. If value of
            // arr[i] + arr[j-1] was greater than arr[k],
            // then arr[i] + arr[j] must be greater than k,
            // because the array is sorted.
            while (k < B.size() && B[i] + B[j] > B[k])
                ++k;

            // Total number of possible triangles that can
            // be formed with the two fixed elements is
            // k - j - 1. The two fixed elements are arr[i]
            // and arr[j]. All elements between arr[j+1]/ to
            // arr[k-1] can form a triangle with arr[i] and arr[j].
            // One is subtracted from k because k is incremented
            // one extra in above while loop.
            // k will always be greater than j. If j becomes equal
            // to k, then above loop will increment k, because arr[k]
            // + arr[i] is always greater than arr[k]
            if (k > j)
                count += k - j - 1;
        }
    }

    return count; */
}

int diffPossible(vector<int> &A, int B) {
	/*unordered_set<int> temp_set;

	for(auto i = 0u; i < A.size(); ++i){
		int s = A[i] - B;
		if(temp_set.find(s) != temp_set.end()){
			return 1;
		}else{
			temp_set.insert(A[i]);
		}
	}

	return 0;*/

	int i = 0, j = A.size() - 1;

	while(i < A.size() - 1){
		if(abs(A[i] - A[j]) == B){
			return 1;
		}else if(abs(A[i] - A[j]) < B){
			j = A.size() - 1;
		}

		j--;
		if(j == i){
			i++;
			j = A.size() - 1;
		}
	}

	return 0;
}

int get_end_index(vector<int>& A, int i){
	int desired_val = A[i];

	for(; i < A.size(); ++i){
		if(A[i] != desired_val){
			return i - 1;
		}
	}

	return i - 1;
}

int removeDuplicates(vector<int> &A) {
	for(auto i = 0u; i < A.size(); ++i){
		int end_index = get_end_index(A, i);
		if(end_index != i){
			A.erase(A.begin() + i + 1, A.begin() + end_index);
		}
	}

	return A.size();
}

int removeElement(vector<int> &A, int B) {
	int i = 0, j = A.size() - 1;

	while(i <= j){
		if(A[i] == B){
			A.erase(A.begin() + i);
			j--;
		}else{
			i++;
		}

		if(A[j] == B){
			A.erase(A.begin() + j);
		}
		j--;
	}

	return A.size();
}

void swap(vector<int>& A, int start_1, int end_1, int start_2, int end_2){
	if(A[start_2] < A[start_1] || A[start_2] < A[end_1]){
		vector<int> A_1, A_2;
		A_1.insert(A_1.begin() + 0, A.begin() + start_1, A.begin() + end_1 + 1);
		A_2.insert(A_2.begin(), A.begin() + start_2, A.begin() + end_2 + 1);

		auto i = 0;
		for(; i < A_2.size(); ++i){
			A[i + start_1] = A_2[i];
		}
		for(auto j = 0; j < A_1.size(); ++j){
			A[i + start_1] = A_1[j];
			i++;
		}
	}
}

void sort_colors(vector<int>& A, int start_id, int end_id){
	if(start_id >= end_id) return;

	int mid = (start_id + end_id) / 2;

	sort_colors(A, start_id, mid);
	sort_colors(A, mid + 1, end_id);

	swap(A, start_id, mid, mid + 1, end_id);
}

void sortColors(vector<int> &A) {
	for(auto i = 0u; i < A.size(); ++i){
		for(auto j = i + 1; j < A.size(); ++j){
			if(A[j] < A[i]){
				int temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	}
}

int minimize(const vector<int> &A, const vector<int> &B, const vector<int> &C) {
    int i = A.size() - 1, j = B.size() - 1, k = C.size() - 1;
    set<int> temp_set;

    while(i >= 0){
        int s = max(abs(A[i] - B[j]), abs(B[j] - C[k]));
        s = max(s, abs(C[k] - A[i]));
        temp_set.insert(s);

        k--;
        if(k < 0){
            k = C.size() - 1;
            j--;
        }
        if(j < 0){
            j = B.size() - 1;
            i--;
        }
    }

    return *temp_set.begin();
}

//////////////////////////////////////////////////////
void test_minimize(){
	vector<int> A{1, 4, 10}, B{2, 15, 20}, C{10, 12};
	cout<<minimize(A, B, C);
}

void test_sortColors(){
	vector<int> A{0,1,2,0,1,2};
	sortColors(A);
	for(auto& a : A){
		cout<<a<<" ";
	}
}
void test_removeElement(){
	vector<int> A{0, 0, 3, 0, 3, 3, 3, 3, 2, 3, 2, 1, 2, 1, 0, 2, 1, 1, 3, 1, 3, 0, 2, 0, 1, 1, 2, 3, 0, 3, 2, 3, 2, 1, 3, 0, 0, 3, 0, 2, 1, 2, 2, 0, 1, 2, 3, 2, 2, 2, 2, 1, 0, 0, 3, 0, 2, 3, 3, 0, 2, 3, 0, 3, 0, 3, 2, 0, 0, 2, 2, 0, 3, 2, 0, 3, 3, 3, 2, 1, 1, 1, 1, 3, 0, 3, 3, 2, 0, 2, 1, 0, 1, 1, 0, 2, 0, 1, 1, 0, 2, 0, 3, 3, 2, 0, 2, 2, 3, 0, 2, 3, 2, 3, 2, 3, 3, 0, 1, 2, 3, 3, 1, 0, 1, 0, 3, 2, 0, 3, 3, 1, 2, 0, 2, 2, 0, 0, 1, 0, 3, 0, 1, 2, 0, 2, 3, 1, 1, 3, 0, 1, 3, 1, 0, 0, 2, 0, 2, 1, 0, 3, 3, 3, 3, 0, 3, 3, 0, 2, 2, 2, 2, 2, 3, 2, 0, 2, 2, 0, 2, 2, 2, 1, 1, 3, 0, 0, 2, 1, 1, 0, 2, 0, 2, 0, 3, 2, 2, 1, 1, 2, 1, 1, 1, 2, 0, 0, 2, 3, 2, 3, 3, 0, 2, 0, 1, 0, 2, 1, 3, 2, 1, 0, 3, 2, 0, 1, 2, 2, 3, 0, 2, 2, 1, 0, 1, 3, 3, 3, 3, 3, 0, 0, 2, 1, 3, 2, 0, 3, 0, 3, 3, 3, 3, 3, 3, 2, 1, 1, 0, 1, 2, 0, 3, 3, 2, 3, 0, 1, 3, 1, 2, 3, 2, 3, 1, 1, 1, 3, 2, 1, 3, 0, 0, 3, 1, 2, 0, 2, 3, 3, 3, 2, 1, 0, 0, 1, 2, 2, 1, 2, 2, 0, 1, 0, 3, 2, 2, 2, 3, 0, 0, 1, 1, 2, 0, 1, 0, 1, 0, 0, 0, 1, 2, 0, 2, 1, 3, 2, 1, 0, 1, 0, 0, 3, 3, 3, 1, 2, 1, 3, 2, 3, 0, 3, 2, 3, 0, 2, 2, 2, 2, 0, 2, 0, 1, 1, 0, 2, 1, 1, 2, 0, 1, 3, 0, 1, 1, 0, 2, 1, 2, 3, 3, 2, 3, 3, 0, 1, 2, 1, 3, 1, 1, 0, 2, 0, 1, 0, 0, 2, 0, 3, 1, 0, 2, 1, 0, 1, 1, 1, 0, 1, 1, 1, 2, 1, 2, 0, 2, 3, 2, 3, 3, 0, 0, 2, 0, 2, 2, 3, 1, 1, 0, 3, 3, 1, 1, 2, 0, 2, 1, 3, 3, 0, 3, 0, 3, 1, 0, 1, 2, 1, 2, 0, 0, 3, 0, 3, 0, 2, 1, 0, 1, 2, 3, 1, 3, 2, 2, 1, 0, 0, 1, 2, 0, 0, 2, 2, 3, 1, 0, 2, 0, 0, 2, 0, 1, 0, 2, 3, 3, 1, 2, 0, 2, 2, 1, 1, 2, 1, 0, 1, 3, 3, 0, 2, 1, 3, 0, 0, 1, 3, 2, 1, 1, 0, 2, 1, 1, 3, 0, 1, 3, 3, 1, 1, 0, 2, 3, 0, 2, 2, 2, 0, 0, 2, 0, 1, 3, 3, 2, 0, 0, 0, 2, 1, 0, 3, 3, 1, 3, 0, 2, 3, 2, 1, 0, 3, 0, 2, 1, 1, 1, 2, 0, 1, 1, 0, 2, 2, 1, 0, 2, 2, 1, 3, 3, 0, 2, 3, 0, 2, 2, 2, 2, 1, 2, 3, 1, 0, 1, 3, 1, 2, 3, 2, 1, 1, 3, 2, 3, 0, 0, 1, 0, 2, 3, 1, 0, 0, 0, 3, 0, 3, 0, 1, 0, 2, 2, 1, 3, 1, 0, 1, 0, 1, 0, 1, 0, 3, 0, 0, 1, 2, 3, 2, 2, 0, 1, 3, 3, 2, 2, 1, 1, 1, 1, 3, 2, 3, 3, 3, 3, 0, 0, 0, 2, 3, 3, 2, 0, 1, 1, 3, 0, 3, 0, 3, 1, 0, 2, 0, 3, 0, 2, 0, 1, 1, 3, 3, 0, 1, 3, 2, 1, 2, 2, 0, 2, 0, 2, 3, 3, 3, 0, 3, 0, 1, 3, 0, 2, 0, 3, 2, 1, 1, 2, 3, 1, 3, 0, 0, 3, 1, 1, 3, 1, 2, 1, 1, 3, 2, 2, 2, 3, 2, 1, 3, 1, 1, 2, 0};
	cout<<removeElement(A, 3)<<endl;
	for(auto& a : A){
		cout<<a<<" ";
	}
}

void test_removeDuplicates(){
	vector<int> A{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	cout<<removeDuplicates(A);

	cout<<endl;
	for(auto & a: A){
		cout<<a<<" ";
	}
}

void test_diffPossible(){
	vector<int> A{1, 3, 5};
	cout<<diffPossible(A, 4);
}

void test_nTriang(){
	vector<int> A{1, 11, 12};
	auto start = chrono::high_resolution_clock::now();
	cout<<nTriang(A);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout<<" Execution time: " << duration.count();
}

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

