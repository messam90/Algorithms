/*
 * BitManipulation.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int numSetBits(unsigned int A) {
	int count = 0;
	while(A != 0){
		A &= (A - 1);
		count++;
	}
	return count;
}

int findMinXor(vector<int> &A) {
	unsigned int minXor = (unsigned int)~0;
	vector<int> tempA(A);

	sort(tempA.begin(), tempA.end());

	for(auto i = 0u; i < tempA.size() - 1; ++i){
		unsigned int tempXor = tempA[i] ^ tempA[i + 1];
		minXor = min(minXor, tempXor);
	}

	return minXor;
}

int singleNumber(const vector<int> &A) {
	int result = 0;

	for(auto i = 0u; i < sizeof(int) * 8; ++i){
		int mask = 1 << i, sum = 0;

		for(auto j = 0u; j < A.size(); ++j){
			if(A[j] & mask){
				sum++;
			}
		}

		if(sum % 2 != 0){
			result |= mask;
		}
	}

	return result;
}

unsigned int reverse(unsigned int A) {
	for(auto i = 0; i < ((sizeof(A) * 8) / 2); ++i){
		bool bit_right = A & (0x00000001 << i), bit_left = A & (0x80000000 >> i);
		if(bit_right){
			A |= 0x80000000 >> i;
		}else{
			A &= ~(0x00000001 << (31 - i));
		}

		if(bit_left){
			A |= 0x00000001 << i;
		}else{
			A &= ~(0x00000001 << i);
		}
	}

	return A;
}

int divide(int A, int B) {
	bool neg_result = ((A < 0 && B > 0) || (A > 0 && B < 0)) ? true : false;
	int result = 0;
	int A_1 = abs((long long)A), B_1 = abs((long long)B);

	if(B_1 == 1){
		if(A == numeric_limits<int>::min()){
			if(neg_result) return A;
			else return numeric_limits<int>::max();
		}else{
			if(neg_result){
				if(A < 0){
					return A;
				}else{
					return -1 * A;
				}
			}else{
				if(A < 0){
					return -1 * A;
				}else{
					return A;
				}
			}
		}
	}

    int count = 0, temp_B = B;
    while(temp_B != 0){
        temp_B &= (temp_B - 1);
        count++;
    }
    temp_B = B;
    int num_shifts = 0;
    if(count == 1){
    	while(temp_B > 1){
    		temp_B /= 2;
    		num_shifts++;
    	}

    	int result = A_1 >> num_shifts;
    	return (neg_result) ? -1 * result : result;
    }

	if(A == numeric_limits<int>::min()){
		A_1	= numeric_limits<int>::max();
	}
	if(B == numeric_limits<int>::min()){
		B_1 = numeric_limits<int>::max();
	}

	while(A_1 > 0){
		A_1 -= B_1;
		result++;
	}

	if(A < 0 && B < 0){
		result--;
	}

	return (neg_result) ? -1 * result : result;
}

int totalSetBits(int A){
	int result = 0;

	for(auto i = 0; i < 32; ++i){
		bool first_bit = false;

		long long count = 0, prev_count = 0;
		long long change = pow(2, i);

		while(count <= A){
			/*count++;

			if(count == prev_count + change){
				first_bit = !first_bit;
				prev_count = count;
			}
			if(first_bit){
				result++;
			}*/

			prev_count = count;
			count += change;
			first_bit = !first_bit;

			if(!first_bit){
				if(count <= A){
					result += count - prev_count;
				}else{
					result += A + 1 - prev_count;
				}
			}
		}
	}

	return result;
}

int singleNumber_2(const vector<int> &A) {
	int result = 0;

	for(auto i = 0u ; i < sizeof(int) * 8; ++i){
		int sum = 0;
		for(auto j = 0u ; j < A.size(); ++j){
			if(A[j] & (1 << i)){
				sum++;
			}
		}

		if(sum % 3 != 0){
			result |= (1 << i);
		}
	}

	return result;
}


//////////////////////////////////////
void test_singleNumber_2(){
	vector<int> A{1, 2, 4, 3, 3, 2, 2, 3, 1, 1};
	cout<<singleNumber_2(A);
}

void test_totalSetBits(){
	cout<<totalSetBits(4);
}

void test_divide(){
	cout<<divide(-2147483647, -10000000);
}

void test_reverse(){
	cout<<reverse(111593685);
}
