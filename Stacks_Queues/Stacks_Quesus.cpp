/*
 * Stacks&Quesus.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: messam
 */
#include "Headers.hpp"

vector<int> prevSmaller(vector<int> &A) {
	stack<int> tempStack;
	vector<int> result;

	for(auto i = 0u; i < A.size() ; ++i){
		while(!tempStack.empty() && tempStack.top() >= A[i]){
					tempStack.pop();
		}

		if(tempStack.empty()){
			result.push_back(-1);
		}else if(tempStack.top() < A[i]){
			result.push_back(tempStack.top());
		}

		tempStack.push(A[i]);
	}

	return result;
}

vector<int> slidingMaximum(const vector<int> &A, int B) {
	auto i = 0u;
	vector<int> result;
	deque<int> tempDeque(B);

	for(; i < B; ++i){
		while(!tempDeque.empty() && A[i] > tempDeque.back()){
			tempDeque.pop_back();
		}
		tempDeque.push_back(i);
	}

	for(; i < A.size(); ++i){
		result.push_back(A[tempDeque.front()]);

		while(!tempDeque.empty() && tempDeque.front() <= i - B){
			tempDeque.pop_front();
		}

		while(!tempDeque.empty() && A[i] > A[tempDeque.back()]){
			tempDeque.pop_back();
		}

		tempDeque.push_back(i);
	}

	result.push_back(tempDeque.front());

	return result;
}

string simplifyPath(string A) {
	string result;
	stack<char> tempStack;

	for(auto i =0u; i < A.length(); ++i){
		if(!tempStack.empty() && tempStack.top() == '/' && A[i] == '/'){}
		else if (!tempStack.empty() && tempStack.top() == '.' && A[i] == '/'){
			tempStack .pop();
		}else if(A[i] == '.' && tempStack.top() == '.'){
			if(tempStack.size() != 2){
				tempStack.pop();
				tempStack.pop();
				while(tempStack.top() != '/') tempStack.pop();
			}else{
				tempStack.pop();
			}
		}else tempStack.push(A[i]);
	}

	while((tempStack.top() == '/' || tempStack.top() == '.') && tempStack.size() != 1) tempStack.pop();

	auto stackSize = tempStack.size();
	result.resize(stackSize);
	for(auto i = 0u; i < stackSize; ++i){
		result[stackSize - i - 1] = tempStack.top();
		tempStack.pop();
	}

	return result;
}

int calculateExpression(stack<char>& opStack, deque<int>& results);
void extractOpValues(stack<char>& opStack, deque<int>& results, vector<string>& A);

int evalRPN(vector<string> &A) {
	stack<char> opStack;
	deque<int> results;

	extractOpValues(opStack, results, A);
	return calculateExpression(opStack, results);
}
