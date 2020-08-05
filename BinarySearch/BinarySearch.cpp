/*
 * CountElementOccurance.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int findOccurance(const vector<int>& A, int B, bool findFirst){
	int low = 0, high = A.size() - 1, result = -1;
	while(low <= high){
		int mid = (high + low / 2);
		if(A[mid] == B){
			result = mid;
			if(findFirst){
				high = mid - 1;
			}else{
				low = mid + 1;
			}
		}else if(B > A[mid]){
			low = mid + 1;
		}else{
			high = mid - 1;
		}
	}
	return result;
}

int findCount(const vector<int> &A, int B){
	int count;
	int firstOccur = findOccurance(A, B, true);
	int lastOccur = findOccurance(A, B, false);
	if(firstOccur == -1 && lastOccur == -1){
		count = 0;
	}else if(firstOccur == -1 || lastOccur == -1){
		count = 1;
	}else{
		count = lastOccur - firstOccur + 1;
	}
	return count;
}

int findMin(const vector<int> &A){
	int low = 0, high = A.size() - 1;
	while(low <= high){
		int mid = (high + low) / 2;
		if(A[low] <= A[high]){
			return A[low];
		}else{
			int prev = (mid + A.size() - 1) % A.size(), next = (mid + 1) % A.size();
			if(A[prev] > A[mid] && A[next] > A[mid]){
				return A[mid];
			}else if(A[low] < A[mid]){
				low = mid + 1;
			}else{
				high = mid - 1;
			}
		}
	}
	return -1;
}

int sqrt(int A){
	int low = 0, high = A, ans = 0;
	if(A == 0) ans = 0;
	else if(A == 1) ans = 1;
	else
	while(low <= high){
		int mid = (low + high) / 2;
		if((mid * mid) == A){
			ans = mid;
			break;
		}
		if((mid * mid) > A){
			high = mid - 1;
		}else if((mid * mid) < A){
			ans = mid;
			low = mid + 1;
		}
	}
	return ans;
}

int searchMatrix(vector<vector<int> > &A, int B){
	int i = 0, j = A[0].size() - 1, result = 0;
	while(i < A.size()){
		if(B == A[i][j]){
			result = 1;
			break;
		}else if(B < A[i][j]){
			j--;
			if(j < 0){
				i++;
				j = A[i].size() - 1;
			}
		}else{
			i++;
		}
	}

	return result;
}

int power(int x, int n){
	if(n == 0){
		return 1;
	}else if(n % 2 == 0){
		return power(x, n / 2) * power(x, n / 2);
	}else{
		return x * power(x, n / 2) * power(x, n / 2);
	}
}
int remainder(int a, int b)
{
    return a - (a / b) * b;
}
int pow(int x, int n, int d){
	int result = remainder(power(x, n), d);
	return (result < 0) ? d + result : result;
}

int search(const vector<int> &A, int B){
	int low = 0, high = A.size() - 1, ans = -1, pivotIndex = 0;
	while(low <= high){
		int mid = low + high / 2;
		if(A[low] <= A[high]){
			pivotIndex = low;
			break;
		}else{
		int next = (mid + 1) %A.size(), prev = (mid + A.size() - 1) % A.size();
		if(A[mid] < A[next] && A[mid] < A[prev]){
			pivotIndex = mid;
			break;
		}else if(A[mid] > A[next]){
			low = next;
		}else if(A[mid] < A[prev]){
			high = prev;
		}
		}
	}

	low = 0;
	high = A.size() - 1;
	int mid = pivotIndex;
	while(low <= high){
		if(B == A[mid]){
			ans = mid;
			break;
		}
		else if(B <= A[mid - 1] && B >= A[low]){
			high = mid - 1;
		}else{
			low = mid + 1;
		}

		mid = (low + high) / 2;
	}

	return ans;
}
