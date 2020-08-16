/*
 * Stacks&Quesus.cpp
 *
 *  Created on: Jul 6, 2020
 *      Author: messam
 */
#include "Headers.hpp"
#include "Stacks_Queues.hpp"

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

int largestRectangleArea(vector<int> &A) {
	/*queue<int> s;
	int i = 0, max_area = 0;

	 while(i < A.size()){
		 if(s.empty() || A[s.back()] <= A[i]){
			 s.push(i++);
		 }else{
			 int tp = s.front();
			 s.pop();

			 int temp_area = A[tp] *  (i - tp);
			 max_area = (temp_area > max_area) ? temp_area : max_area;
		 }
	 }

	 while(!s.empty()){
		 int tp = s.back();
		 s.pop();

		 int temp_area = A[tp] *  (i - tp);
		 max_area = (temp_area > max_area) ? temp_area : max_area;
	 }

	 return max_area;*/
    // Create an empty stack. The stack holds indexes
    // of hist[] array. The bars stored in stack are
    // always in increasing order of their heights.
    /*stack<int> s;

    int max_area = 0; // Initialize max area
    int tp;  // To store top of stack
    int area_with_top; // To store area with top bar
                       // as the smallest bar

    // Run through all bars of given histogram
    int i = 0;
    while (i < A.size())
    {
        // If this bar is higher than the bar on top
        // stack, push it to stack
        if (s.empty() || A[s.top()] <= A[i])
            s.push(i++);

        // If this bar is lower than top of stack,
        // then calculate area of rectangle with stack
        // top as the smallest (or minimum height) bar.
        // 'i' is 'right index' for the top and element
        // before top in stack is 'left index'
        else
        {
            tp = s.top();  // store the top index
            s.pop();  // pop the top

            // Calculate the area with hist[tp] stack
            // as smallest bar
            area_with_top = A[tp] * (s.empty() ? i :
                                   i - s.top() - 1);

            // update max area, if needed
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }

    // Now pop the remaining bars from stack and calculate
    // area with every popped bar as the smallest bar
    while (s.empty() == false)
    {
        tp = s.top();
        s.pop();
        area_with_top = A[tp] * (s.empty() ? i :
                                i - s.top() - 1);

        if (max_area < area_with_top)
            max_area = area_with_top;
    }

    return max_area;*/

    stack<int> s;
    int i = 0, max_area = 0;

    while(i < A.size()){
        if(s.empty() || A[i] >= A[s.top()]){
            s.push(i++);
        }else{
            int top = s.top();
            s.pop();

            int temp_area = A[top] * ((s.empty())? i : i - s.top() - 1);
            max_area = (temp_area > max_area)? temp_area : max_area;
        }
    }

    while(!s.empty()){
        int top = s.top();
        s.pop();

        int temp_area = A[top] * ((s.empty())? i : i - s.top() - 1);
        max_area = (temp_area > max_area) ? temp_area : max_area;
    }

    return max_area;
}

int braces(string A) {
	/*int num_opens = 0;
	bool wait_for_closing = false;

	for(auto i = 0u; i < A.length(); ++i){
		if(!(A[i] >= 'a' && A[i] <= 'z' && A[i] == ' ')){
			if(A[i] == '('){
				if(!wait_for_closing) num_opens++;
				else num_opens--;
			}else if(A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/'){
				wait_for_closing = true;
			}else if(A[i] == ')' && wait_for_closing){
				num_opens--;
				wait_for_closing = false;
			}
		}
	}

	if(num_opens > 0){
		return 1;
	}

	return 0;*/

	stack<char> s;

	for(auto i = 0u; i < A.length(); ++i){
		if(!(A[i] >= 'a' && A[i] <= 'z' || A[i] == ' ')){
			if(A[i] != ')'){
				s.push(A[i]);
			}else{
				if(!s.empty() && s.top() == '('){
					return 1;
				}else{
					while(!s.empty() && s.top() != '('){
						s.pop();
					}
					s.pop();
				}
			}
		}
	}

	return 0;
}

/*stack<int> values;
int min_value;

MinStack::MinStack() {
	min_value = 0;
}

void MinStack::push(int x) {
	int value = 0;
	if(values.empty()){
		min_value = x;
		value = x;
	}else if(x < min_value){
		value = 2 * x - min_value;
		min_value = x;
	}else{
		value = x;
	}
	values.push(value);
}

void MinStack::pop() {
	int top = values.top();
	if(top < min_value){
		min_value = 2 * min_value - top;
	}
	values.pop();
}

int MinStack::top() {
	if(values.top() < min_value){
		return min_value;
	}else{
		return values.top();
	}
}

int MinStack::getMin() {
	return min_value;
}*/

stack<int> values;
int min_value;

MinStack::MinStack() {
    while(!values.empty()){
        values.pop();
    }
    min_value = std::numeric_limits<int>::min();
}

void MinStack::push(int x) {
    int value = -1;
    if(values.empty()){
        value = x;
        min_value = value;
    }else if(x < min_value){
        value = 2 * x - min_value;
        min_value = x;
    }else{
        value = x;
    }
    values.push(value);
}

void MinStack::pop() {
    if(!values.empty()){
    	if(values.top() < min_value){
            min_value = 2 * min_value - values.top();
        }
    	values.pop();
    }
    if(values.empty()){
        min_value = -1;
    }
}

int MinStack::top() {
    if(values.empty()){
        return -1;
    }else if(values.top() < min_value){
        return min_value;
    }else{
        return values.top();
    }
}

int MinStack::getMin() {
    return min_value;
}

string solve_nrc(string A) {
	//https://www.interviewbit.com/problems/first-non-repeating-character-in-a-stream-of-characters/
	int i = 0, j = 1;
	unordered_multimap<char, int> temp_map;
	string result(1, A[0]);

	for(auto i = 0u; i < A.length(); ++i){
		temp_map.insert(pair<char, int>(A[i], i));
	}

	while(j < A.length()){
		bool rep_char = false;
		auto it_range = temp_map.equal_range(A[i]);
		for(auto it = it_range.first; it != it_range.second; ++it){
			if(i != it->second && it->second <= j){
				rep_char = true;
				break;
			}
		}

		if(!rep_char){
			result += A[i];
		}

		i++;
		if(i > j || !rep_char){
			i = 0;
			j++;
			if(rep_char){
				result += '#';
			}
		}
	}

	return result;
}

int maxSpecialProduct(vector<int> &A) {
	set<int, greater<int>> max_product;

	for(auto i = 1u; i < A.size() - 1; ++i){
		int max_left_id = i - 1, max_right_id = i + 1, max_left = -1, max_right = -1;
		int exit = 0;

		while(exit != 3){
			if(A[max_left_id] > A[i] && max_left == -1){
				max_left = A[max_left_id];
			}

			if(A[max_right_id] > A[i] && max_right == -1){
				max_right = A[max_right_id];
			}

			if(max_left == -1){
				max_left_id--;
			}
			if(max_left != -1 || max_left_id < 0){
				exit |= 1;
			}
			if(max_right == -1){
				max_right_id++;
			}
			if(max_right != -1 || max_right_id == A.size()){
				exit |= 2;
			}
		}

		int prod = (max_left < 0 || max_right < 0) ? 0 : ((max_left_id * max_right_id) %((int)pow(10, 9) + 7));
		max_product.insert(prod);
	}
	return *max_product.begin();
}


/////////////////////////////////////////////////
void test_maxSpecialProduct(){
	vector<int> A{1950, 9417, 7760, 1939, 8551, 5184, 2187, 1097, 9686, 525, 7923, 364, 9182, 3013, 3252, 2203, 5496, 1537, 3455, 2209, 6981, 8032, 831, 2096, 6715, 3113, 2137, 9938, 2010, 5686, 2920, 4382, 9611, 9909, 1610};
	cout<<maxSpecialProduct(A);
}

void test_solve_nrc(){
	cout<<solve_nrc("abcabc");
}

void test_MinStack(){
	MinStack min_stack;
	/*min_stack.push(3);
	min_stack.push(5);
	cout<<min_stack.getMin()<<" ";
	min_stack.push(2);
	min_stack.push(1);
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.top();*/

	/*min_stack.push(10);
	min_stack.push(9);
	cout<<min_stack.getMin()<<" ";
	min_stack.push(8);
	cout<<min_stack.getMin()<<" ";
	min_stack.push(7);
	cout<<min_stack.getMin()<<" ";
	min_stack.push(6);
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.getMin()<<" ";
	min_stack.pop();
	cout<<min_stack.getMin()<<" ";*
	*/

	min_stack.pop();
	min_stack.pop();
}

void test_braces(){
	cout<<braces("((a))");
}

void test_largestRectangleArea(){
	vector<int> A{6, 2, 5, 4, 5, 1, 6};
	cout<<largestRectangleArea(A);
}
