/*
 * LinkedLists.cpp
 *
 *  Created on: Aug 11, 2020
 *      Author: messam
 */
#include "Headers.hpp"
#include "LinkedLists.hpp"

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};


ListNode* deleteDuplicates_2(ListNode* A) {
	unordered_set<int> values;
	ListNode *current = A, *prev = A, *head = A;
	bool delete_again = false;

	while(current){
		if((current->next && current->val == current->next->val) || delete_again){
			if(current->next && current->val == current->next->val)
				delete_again = true;
			else delete_again = false;

			if(current == head){
				head = current->next;
			}else{
				prev->next = current->next;
			}
		}else{
			prev = current;
		}
		current = current->next;
	}

	return head;
}

ListNode* deleteDuplicates(ListNode* A) {
	unordered_set<int> values;
	ListNode *current = A, *prev = A;

	while(current){
		if(values.find(prev->val) != values.end()){
			prev->next = current->next;
			//remove current
		}else{
			values.insert(current->val);
			prev = current;
		}

		current = current->next;
	}

	return A;
}

ListNode* mergeTwoLists(ListNode* A, ListNode* B) {
	ListNode *current_A = A, *current_B = B, *head = nullptr, *current;

	if(current_A->val < current_B->val){
		head = current_A;
		current_A = current_A->next;
	}else{
		head = current_B;
		current_B = current_B->next;
	}
	current = head;

	while(current_A != nullptr && current_B != nullptr){
		if(current_A->val < current_B->val){
			current->next = current_A;
			current_A = current_A->next;
		}else{
			current->next = current_B;
			current_B = current_B->next;
		}
		current = current->next;
	}

	while(current_A){
		current->next = current_A;
		current_A = current_A->next;
		current = current->next;
	}

	while(current_B){
			current->next = current_B;
			current_B = current_B->next;
			current = current->next;
	}

	return head;
}

ListNode* removeNthFromEnd(ListNode* A, int B) {
	ListNode *current = A, *head = A;
	int size = 0;

	while(current){
		size++;
		current = current->next;
	}

	int delete_at = size - B - 1, index = 0;
	current = A;

	while(current){
		if(delete_at > 0 && delete_at == index){
			if(current->next)
				current->next = current->next->next;
			else current->next = nullptr;
			break;
		}else if(delete_at < 0){
			head = A->next;
			break;
		}
		index++;
		current = current->next;
	}

	return head;
}

ListNode* reverse(ListNode* current, ListNode* prev, int a, ListNode** temp_head){
	if(a == 1 || current == nullptr)
		return nullptr;

	ListNode* temp = reverse(current->next, current, a - 1, temp_head);
	temp = (a != 2) ? temp : current->next;
	*temp_head = (*temp_head == nullptr) ? current : *temp_head;
	current->next = prev;

	return temp;
}

ListNode* reverseList(ListNode* A, int B) {
	ListNode * current = A, *prev = A, *head = A, *temp_head = nullptr;
	int size = 0;

	while(current){
		size++;
		current = current->next;
	}

	current = A;
	for(auto i = 0; i < (size / B) && B > 1; ++i){
		current->next = reverse(current->next, current, B, &temp_head);
		if(i == 0){
			head = temp_head;
		}else{
			prev->next = temp_head;
		}
		prev = current;
		current = current->next;
		temp_head = nullptr;
	}

	return head;
}

ListNode* rotateRight(ListNode* A, int B) {
	deque<ListNode*> prev_nodes;
	ListNode* current = A, *head = A, *new_head = A;
	int size = 0;

	while(current){
		size++;
		current = current->next;
	}

	B = B % size;
	if(size == 1 || B == 0) return A;
	current = A;


	while(current){
		if(prev_nodes.size() == B + 1){
			prev_nodes.pop_front();
		}
		prev_nodes.push_back(current);
		current = current->next;
	}

	prev_nodes.front()->next = nullptr;
	prev_nodes.pop_front();
	new_head = prev_nodes.front();
	prev_nodes.back()->next = head;

	return new_head;
}

ListNode* addTwoNumbers(ListNode* A, ListNode* B) {
	ListNode* current_a = A, *current_b = B, *result_head = new ListNode(0), *result = result_head;
	int carry_over = 0;

	while(current_a && current_b){
		int sum = current_a->val + current_b->val + carry_over;
		result->val = (sum > 9) ? sum - 10 : sum;
		carry_over = (sum > 9) ? 1 : 0;

		current_a = current_a->next;
		current_b = current_b->next;
		if(current_a || current_b){
			result->next = new ListNode(0);
			result = result->next;
		}
	}

	while(current_a){
		int sum = current_a->val + carry_over;
		result->val = (sum > 9) ? sum - 10 : sum;
		carry_over = (sum > 9) ? 1 : 0;

		current_a = current_a->next;
		if(current_a){
			result->next = new ListNode(0);
			result = result->next;
		}
	}

	while(current_b){
		int sum = current_b->val + carry_over;
		result->val = (sum > 9) ? sum - 10 : sum;
		carry_over = (sum > 9) ? 1 : 0;

		current_b = current_b->next;
		if(current_b){
			result->next = new ListNode(0);
			result = result->next;
		}
	}

	if(carry_over){
		result->next = new ListNode(carry_over);
	}

	return result_head;
}

ListNode* detectCycle(ListNode* A) {
	ListNode* current = A, *compare = A, *cycle_begin = nullptr;
	bool start = true;

	do{
		if(current == compare && !start){
			cycle_begin = current;
		}
		current = current->next;
	}while(compare != A);

	return cycle_begin;
}

ListNode* partition(ListNode* A, int B) {
	ListNode *head = A, *current_before = A, *prev_before = A, *value_node = nullptr, *current_after = nullptr, *prev_after = nullptr;

	while(current_before){
		if(current_before->val == B){
			value_node = current_before;
			current_after = value_node->next;
			prev_after = value_node;
			current_before = A;
			break;
		}
		current_before = current_before->next;
	}

	while(current_after){
		if(current_after->val < B){
			if(current_after->val < current_before->val){
				if(current_before == head){
					prev_after->next = current_after->next;
					current_after->next = head;
					head = current_after;
				}else{
					prev_after->next = current_after->next;
					ListNode *temp = prev_before->next;
					prev_before->next = current_after;
					current_after->next = temp;
				}

				current_after = (!prev_after) ? nullptr : prev_after->next;
				current_before = head;
				prev_before = head;
			}else{
				prev_before = current_before;
				current_before = current_before->next;
			}

			if(current_before == value_node || (current_after && current_after->val >= B)){
				prev_after = current_after;
				current_after = current_after->next;
				current_before = head;
				prev_before = head;
			}
		}
	}

	return head;
}


ListNode* reverseBetween(ListNode* A, int B, int C) {
	ListNode* current = A, *prev = A, *temp_1, *temp_1_1, *temp_2, *temp_3, *temp_3_1, *head = A;
	int i = 0;

	while(current){
		i++;
		if(i == B - 1 || (i == 1 && B == 1)){
			temp_1 = current;
			temp_1_1 = current->next;
		}else if(i > B && i < C){
			temp_2 = current->next;
			current->next = prev;
			prev = current;
			current = temp_2;
		}else if(i == C){
			temp_3 = current;
			temp_3_1 = current->next;
			current->next = prev;
		}else if(i == C + 1){
			if(B == 1){
				head = temp_3;
				temp_1->next = temp_3_1;
			}else{
				temp_1->next = temp_3;
				temp_1_1->next = temp_3_1;
			}
			break;
		}

		if(i <= B){
			prev = current;
			current = current->next;
		}
	}

	return head;
}

ListNode* reorderList(ListNode* A) {
	ListNode *current = A, *temp;
	stack<ListNode*> nodes;

	while(current){
		nodes.push(current);
		current = current->next;
	}

	current = A;

	while(current->next != nodes.top() && current != nodes.top()){
		temp = current->next;
		current->next = nodes.top();
		nodes.pop();
		current->next->next = temp;
		current = temp;
	}

	if(current->next == nodes.top()){
		current->next = nodes.top();
		current->next->next = nullptr;
	}else{
		current->next = nullptr;
	}


	return A;
}


/*
 * 	ListNode A(1);
	A.next = new ListNode(4);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(2);
	A.next->next->next->next = new ListNode(3);
	A.next->next->next->next->next = new ListNode(4);
	A.next->next->next->next->next->next = new ListNode(1);
	A.next->next->next->next->next->next->next = new ListNode(5);
 */
//////////////////////////////////////////
void test_reorderList(){
	ListNode A(1);
	A.next = new ListNode(2);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(4);
	A.next->next->next->next = new ListNode(5);

	auto result = reorderList(&A);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_reverseBetween(){
	ListNode A(1);
	A.next = new ListNode(2);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(4);
	A.next->next->next->next = new ListNode(5);

	auto result = reverseBetween(&A, 1, 5);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_partition(){
	ListNode A(1);
	A.next = new ListNode(4);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(2);
	A.next->next->next->next = new ListNode(5);
	A.next->next->next->next->next = new ListNode(2);

	auto result = partition(&A, 3);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_rotateRight(){
	ListNode A(1);
	A.next = new ListNode(4);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(2);
	A.next->next->next->next = new ListNode(5);

	auto result = rotateRight(&A, 2);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_reverseList(){
	ListNode A(1);
	A.next = new ListNode(2);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(4);
	A.next->next->next->next = new ListNode(5);
	A.next->next->next->next->next = new ListNode(6);

	auto result = reverseList(&A, 2);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_removeNthFromEnd(){
	ListNode A(1);
	A.next = new ListNode(2);
	A.next->next = new ListNode(3);
	A.next->next->next = new ListNode(4);
	A.next->next->next->next = new ListNode(5);

	auto result = removeNthFromEnd(&A, 2);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_mergeTwoLists(){
	ListNode A(1);
	A.next = new ListNode(2);
	A.next->next = new ListNode(3);

	ListNode B(4);
	B.next = new ListNode(5);
	B.next->next = new ListNode(6);

	auto result = mergeTwoLists(&A, &B);
	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_deleteDuplicates_2(){
	ListNode A(1);
	A.next = new ListNode(1);
	A.next->next = new ListNode(2);
	A.next->next->next = new ListNode(3);
	A.next->next->next->next = new ListNode(3);

	ListNode* result = deleteDuplicates_2(&A);

	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void test_deleteDuplicates(){
	ListNode A(1);
	A.next = new ListNode(1);
	A.next->next = new ListNode(2);
	A.next->next->next = new ListNode(3);
	A.next->next->next->next = new ListNode(3);

	ListNode* result = deleteDuplicates(&A);

	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}
