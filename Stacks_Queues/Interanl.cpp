/*
 * Interanl.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: messam
 */
#include "Headers.hpp"

void extractOpValues(stack<char>& opStack, deque<int>& results, vector<string>& A){
	for(int i = A.size() - 1; i >= 0; --i){
		if(A[i] != string("+") && A[i] != string("-") && A[i] != string("/")){
			int value;
			stringstream ss(A[i]);
			ss>>value;
			results.push_back(value);
		}else{
			opStack.push(A[i][0]);
		}
	}
}

int performOp(char op, int y, int x){
	switch(op){
	case '+': return x + y;
	case '-': return x - y;
	case '/': return x / y;
	}

	return -1;
}

int calculateExpression(stack<char>& opStack, deque<int>& results){
	char op;
	int result = 0;
	while(!opStack.empty()){
		op = opStack.top();
		opStack.pop();
		int y = results.front();
		results.pop_front();
		int x = results.front();
		results.pop_front();
		result = performOp(op, y, x);
		results.push_back(result);
	}

	return result;
}



