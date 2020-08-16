/*
 * Stacks_Queues.hpp
 *
 *  Created on: Aug 9, 2020
 *      Author: messam
 */

#ifndef STACKS_QUEUES_STACKS_QUEUES_HPP_
#define STACKS_QUEUES_STACKS_QUEUES_HPP_

class MinStack{
public:
	MinStack();
	void push(int);
	void pop();
	int top();
	int getMin();
};

void test_largestRectangleArea();
void test_braces();
void test_MinStack();
void test_solve_nrc();
void test_maxSpecialProduct();


#endif /* STACKS_QUEUES_STACKS_QUEUES_HPP_ */
