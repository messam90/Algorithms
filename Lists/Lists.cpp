/*
Lists.cpp
 *
 Created on: Jul 6, 2020
     Author: messam
 */
#include "Headers.hpp"

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

unsigned int getListSize(ListNode* A){
	ListNode* currentNode = A;
	unsigned int count = 0;
	if(A != nullptr){
		count++;
	}
	while(currentNode->next != nullptr){
		count++;
		currentNode = currentNode->next;
	}

	return count;
}

ListNode* getListMidNode(ListNode* A, unsigned int lSize){
	ListNode* midNodePtr = A;

	for(auto i = 0u; i < lSize/2; ++i){
		midNodePtr = midNodePtr->next;
	}

	return midNodePtr;
}

bool compareLists(ListNode* A, ListNode* midPtr, unsigned int lSize){
	ListNode* leftNode = A, *rightNode = midPtr->next;
	while(1){
		if(leftNode->val != rightNode->val){
			return false;
		}

		if(rightNode->next == nullptr)	{
			leftNode = leftNode->next;
			break;
		}
		leftNode = leftNode->next;
		rightNode = rightNode->next;
	}

	if(lSize % 2 == 0){
		if(leftNode->val != midPtr->val){
			return false;
		}
	}

	return true;
}

void reverseList(ListNode* nodePtr, unsigned int traverseCount){
	ListNode* currentNode = nodePtr, *nextNode, *temp, *temp1;

	while(traverseCount > 0){
		nextNode = currentNode->next;
		for(auto i = 0u; i < traverseCount - 1; ++i){
			nextNode = nextNode->next;
		}
		temp = currentNode->next;
		temp1 = nextNode->next;
		nextNode->next = temp;
		currentNode->next->next = temp1;
		currentNode->next = nextNode;
		currentNode = nextNode;
		traverseCount--;
	}
}

int lPalin(ListNode* A) {
	unsigned int lSize = getListSize(A);
	ListNode* midPtr = getListMidNode(A, lSize);
	reverseList(midPtr, (lSize%2 == 0) ? lSize/2-1 : lSize/2);

	bool match = compareLists(A, midPtr, lSize);
	return match;
}




