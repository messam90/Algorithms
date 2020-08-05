/*
 Hashing.cpp
 *
  Created on: Jul 15, 2020
      Author: messam
 */
#include "Headers.hpp"
#include "Hashing.hpp"

int colorful(int A) {
	stringstream ss;
	ss<<A;
	string num = ss.str();
	int i = 0, j = num.length() - 1;
	int multiplyResult = 1;
	unordered_set<int> multiplyResults;

	if(num.length() == 1)	return 1;
	while(i < num.length()){
		multiplyResult *= num[j] - '0';
		auto it = multiplyResults.find(multiplyResult);
		if(it != multiplyResults.end()){
			return 0;
		}else{
			multiplyResults.insert(multiplyResult);
		}
		j--;
		if(j < 0){
			i++;
			j = num.length() - 1 - i;
			multiplyResult = 1;
		}
	}

	return 1;
}

vector<int> lszero(vector<int> &A) {
	unordered_map<int, int> sums;
	int sum = 0, max_len, index1 = -1, index2 = -1, prev_index2 = -1, prev_index1 = -1;

	sums[0] = -1;
	for(auto i = 0; i < A.size(); ++i){
		sum += A[i];

		if(sum == 0 && i == 0){
			prev_index2 = 0;
			prev_index1 = 0;
		}

		auto it = sums.find(sum);
		if(it != sums.end()){
			index1 = it->second + 1;
			index2 = i;
			if(prev_index2 == -1){
				prev_index2 = index2;
				prev_index1 = index1;
			}else if(index2 - index1 > prev_index2 - prev_index1){
				prev_index2 = index2;
				prev_index1 = index1;
			}
		}else{
			sums[sum] = i;
		}
	}

	vector<int> result;

	if(prev_index2 != -1)
		copy(A.begin() + prev_index1, A.begin() + prev_index2 + 1, back_inserter(result));
	return result;
}

vector<int> twoSum(const vector<int> &A, int B) {
	unordered_map<int, int> valuesMap;

	for(auto i = 0; i < A.size(); ++i){
		int tempDiff = B - A[i];
		auto it = valuesMap.find(tempDiff);
		if(it == valuesMap.end()){
			valuesMap.insert(pair<int, int>(A[i], i));
		}else{
			int j = it->second;
			if(i < j){
				vector<int> result{i+ 1, j + 1};
				return result;
			}
			else{
				vector<int> result{j + 1, i + 1};
				return result;
			}
		}
	}

	return vector<int>();
}

bool condition_check(int a, int b, int c, int d){
	if(a != c && a != d &&
			b != c && b != d){
		return true;
	}
	return false;
}
vector<vector<int> > fourSum(vector<int> &A, int B) {
	int i = 0, j = 1;
	unordered_map<int, pair<int, int>> sumsMap;
	vector<vector<int>> result;

	while(i < A.size() - 1){
		sumsMap[A[i] + A[j]] = {i , j};
		j++;
		if(j == A.size()){
			i++;
			j = i + 1;
		}
	}

	j = A.size() - 1;
	i = j - 1;
	while(j > 0){
		int sum = A[i] + A[j], diff = B - sum;
		auto it = sumsMap.find(diff);
		if(it != sumsMap.end()){
			if(condition_check(it->second.first, it->second.second, i, j)){
				multiset<int> temp_set;
				temp_set.insert(A[it->second.first]);
				temp_set.insert(A[it->second.second]);
				temp_set.insert(A[i]);
				temp_set.insert(A[j]);
				if(temp_set.size() == 4){
					vector<int> temp;
					auto it_1 = temp_set.begin();
					temp.push_back(*it_1);
					advance(it_1, 1);
					temp.push_back(*it_1);
					advance(it_1, 1);
					temp.push_back(*it_1);
					advance(it_1, 1);
					temp.push_back(*it_1);
					result.push_back(temp);
				}
				sumsMap.erase(it);
			}
		}
		auto it_2 = sumsMap.find(sum);
		if(it_2 != sumsMap.end()) sumsMap.erase(it_2);
		i--;
		if(i < 0){
			j--;
			i = j - 1;
		}
	}

	return result;
}

int check_box(const vector<string>& A, int i, int j){
	int temp_i = i, temp_j = j;
	unordered_set<int> temp_set;

	while(temp_i < i + 3){
		if(A[temp_i][temp_j] != '.'){
			if(temp_set.find(A[temp_i][temp_j]) != temp_set.end()){
				return 0;
			}
			temp_set.insert(A[temp_i][temp_j]);
		}
		temp_j++;
		if(temp_j == j + 3){
			temp_j = j;
			temp_i++;
		}
	}

	return 1;
}

int isValidSudoku(const vector<string> &A) {
	int i = 0, j = 0;
	unordered_set<int> temp_set;

	//check rows
	while(i < A.size()){
		if(A[i][j] != '.'){
			if(temp_set.find(A[i][j]) != temp_set.end()){
				return 0;
			}
			temp_set.insert(A[i][j]);
		}
		j++;
		if(j == A[i].length()){
			j = 0;
			i++;
			temp_set.clear();
		}
	}

	//check columns
	i = 0;
	j = 0;
	while(j < A.size()){
		if(A[i][j] != '.'){
			if(temp_set.find(A[i][j]) != temp_set.end()){
				return 0;
			}
			temp_set.insert(A[i][j]);
		}
		i++;
		if(i == A.size()){
			j++;
			i = 0;
			temp_set.clear();
		}
	}

	//check boxes
	i = 0;
	j = 0;
	while(i < A.size()){
		if(!check_box(A, i, j)){
			return 0;
		}
		j += 3;
		if(j == A.size()){
			j = 0;
			i += 3;
		}
	}

	return 1;
}

int diffPossible(const vector<int> &A, int B) {
	unordered_set<int> temp_set;
	vector<int> C(A);
	sort(C.begin(), C.end());

	for(auto i = 0u; i < C.size(); ++i){
		auto it = temp_set.find(C[i]);
		if(it != temp_set.end()){
			return 1;
		}
		temp_set.insert(B + C[i]);
	}

	return 0;
}

vector<vector<int> > anagrams(const vector<string> &A) {
	vector<vector<int>> result;
	map<int, vector<int>> result_map;
	multimap<string, int> temp_map;

	for(auto i = 0u; i < A.size(); ++i){
		string temp_string = A[i];
		sort(temp_string.begin(), temp_string.end());
		auto it = temp_map.find(temp_string);
		if(it != temp_map.end()){
			result_map[it->second].push_back(i + 1);
		}else{
			result_map[i + 1] = vector<int>{i + 1};
		}
		temp_map.insert(pair<string, int>(temp_string, i + 1));
	}

	for(auto it = result_map.begin(); it != result_map.end(); ++it){
		result.push_back(it->second);
	}

	return result;
}

vector<int> equal(vector<int> &A) {
	int i = 0, j = 1, sum = 0;
	unordered_map<int, pair<int, int>> sum_map;

	while(i < A.size() - 1){
		sum = A[i] + A[j];
		sum_map.insert(pair<int, pair<int, int>>(sum, pair<int, int>(i , j)));

		j++;
		if(j == A.size()){
			i++;
			j = i + 1;
		}
	}

	j = A.size() - 1;
	i = j - 1;
	sum = 0;
	while(j > 0){
		sum = A[i] + A[j];

		auto it = sum_map.find(sum);

		if(it != sum_map.end() && it->second.first != i && it->second.second != j){
			vector<int> temp_vector{it->second.first, it->second.second, i, j};
			return temp_vector;
		}

		i--;
		if(i < 0){
			j--;
			i = j - 1;
		}
	}

	return vector<int>();
}



RandomListNode* copyRandomList(RandomListNode* A) {
	RandomListNode* current_node = A, *new_list_node, *new_list_head;
	unordered_map<int, RandomListNode*> nodes_map;

	while(current_node){
		RandomListNode* temp_node = new RandomListNode(current_node->label);
		nodes_map[temp_node->label] = temp_node;

		current_node = current_node->next;
	}

	current_node = A;
	new_list_node = nodes_map[current_node->label];
	new_list_head = new_list_node;
	while(current_node){
		if(current_node->next)
			new_list_node->next = nodes_map[current_node->next->label];
		if(current_node->random)
		new_list_node->random = nodes_map[current_node->random->label];

		current_node = current_node->next;
		new_list_node = new_list_node->next;
	}

	return new_list_head;
}

/////////////////////////////////////////////////////////////////////////////////////
void test_copyRandomList(){
	string command = "66 290 229 136 74 260 41 79 87 177 77 228 232 276 185 35 242 28 178 77 206 226 10 234 52 67 33 104 144 190 160 70 6 191 211 4 217 6 28 195 107 34 220 144 75 67 129 4 253 103 140 168 211 280 291 218 127 147 42 266 8 142 73 138 36 20 70 52 264 195 94 76 63 217 18 53 136 132 62 73 83 66 222 250 213 196 129 31 296 184 252 172 58 188 37 142 272 254 205 165 42 271 159 167 181 217 79 163 219 286 93 112 189 94 169 223 99 138 253 28 205 106 281 254 130 294 193 215 253 218 213 221 73";
	stringstream ss(command);
	unordered_map<int, RandomListNode*> nodes_map;
	int num_nodes, first_node_label;
	ss>>num_nodes;
	ss>>first_node_label;
	RandomListNode* node, *first_node;
	node = new RandomListNode(first_node_label);
	first_node = node;
	nodes_map[first_node_label] = first_node;
	for(auto i = 0u; i < num_nodes - 1; ++i){
		int label;
		ss>>label;
		node->next = new RandomListNode(label);
		nodes_map[label] = node->next;
		node = node->next;
	}

	node = first_node;
	for(auto i = 0u; i < nodes_map.size(); ++i){
		int random_node_index;
		ss>>random_node_index;

		auto it = nodes_map.begin();
		if(random_node_index > nodes_map.size()){
			random_node_index %= (nodes_map.size() + 1);
		}
		advance(it, random_node_index);

		if(random_node_index == nodes_map.size()){
			node->random = nullptr;
		}else{
			node->random = it->second;
		}
		node = node->next;
	}

	/*RandomListNode A{1}, B{2}, C{3};
	A.next = &B;
	A.random = &C;
	B.next = &C;
	B.random = &A;
	C.random = &A;*/

	auto result = copyRandomList(first_node);
	while(result){
		cout<<result->label<<" Random: "<<result->random->label<<endl;
		result = result->next;
	}
}

void test_equal(){
	vector<int> A{3, 4, 7, 1, 2, 9, 8};
	auto result = equal(A);
	for(auto& a : result){
		cout<<a<<" ";
	}
}
void testanagrams(){
	vector<string> A{"caat", "taac", "dog", "god", "acta"};
	auto result = anagrams(A);
	for(auto& a : result){
		for(auto& b : a){
			cout<<b<<" ";
		}
		cout<<endl;
	}
}

void testdiffPossible(){
	vector<int> A{1, 5, 3};
	cout<<diffPossible(A, 2);
}

void testisValidSudoku(){
	vector<string> A{"53..7....", "6..195...", ".98....6.", "8...6...3", "4..8.3..1", "7...2...6", ".6....28.", "...419..5", "....8..79"};
	cout<<isValidSudoku(A);
}

void testfourSum(){
	vector<int> A{1, 0, -1, 0, -2, 2};
	auto result = fourSum(A, 0);
	for(auto& a : result){
		for(auto& b : a){
			cout<<b<<" ";
		}
		cout<<endl;
	}
}

void testtwoSum(){
	vector<int> A{4, 7, -4, 2, 2, 2, 3, -5, -3, 9, -4, 9, -7, 7, -1, 9, 9, 4, 1, -4, -2, 3, -3, -5, 4, -7, 7, 9, -4, 4, -8 };
	auto result = twoSum(A, -3);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void testLszero(){
	vector<int> A{10, 13, -1, 8, 29, 1, 24, 8, 21, 20, 21, -23, -21, 0  };
	vector<int> result = lszero(A);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void testColorful(){
	cout<<colorful(2345)<<endl;
}



