/*
Trees.cpp
 *
 Created on: Jul 8, 2020
     Author: messam
 */
#include "Headers.hpp"
#include "tree.hpp"

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

TreeNode* newNode(int data)
{
	TreeNode* node = new TreeNode(data);
    node->left = node->right = NULL;
    return node;
}

void removeHalfNode(TreeNode* current, TreeNode* prev){
	if(current == nullptr) return;

	removeHalfNode(current->left, current);

	if(current->left == nullptr && current->right == nullptr){}
	else if(prev != nullptr){
		if(current->right == nullptr){
			prev->left = current->left;
			//delete current;
		}else if(current->left == nullptr){
			prev->right = current->right;
			//delete current;
		}
	}

	removeHalfNode(current->right, current);
}

void inOrderTraversal(struct TreeNode* current){  //recursive code to print in-order
    if(current == NULL)  // reaches end of any leaf and can’t go any deeper in tree
       return;

    inOrderTraversal(current->left);
    cout<<current->val<<" ";
    inOrderTraversal(current->right);
}


TreeNode* solve(TreeNode* A) {
	removeHalfNode(A, nullptr);
	return A;
}

void diagonalConstruct(TreeNode* A, int distance, map<int, vector<int>>& diagonalValues){
	if(A == nullptr)	return;
	diagonalValues[distance].push_back(A->val);

	diagonalConstruct(A->left, distance + 1, diagonalValues);
	diagonalConstruct(A->right, distance, diagonalValues);
}

vector<int> solveDiagonalTree(TreeNode* A) {
	map<int, vector<int>> diagonalValues;
	vector<int> result;
	diagonalConstruct(A, 0, diagonalValues);

	for(map<int, vector<int>>::iterator it = diagonalValues.begin(); it != diagonalValues.end(); ++it){
		for(auto i = 0u; i < it->second.size(); ++i)
			result.push_back(it->second[i]);
	}

	return result;
}

enum class nextActionType{LEFT, RIGHT, GO_BACK};
vector<int> inorderTraversal(TreeNode* A) {
    TreeNode* currentNode = A, *root = A;
    stack<TreeNode*> currentPath;
    vector<int> values;
    while(currentNode != nullptr || !currentPath.empty()){
        while(currentNode != nullptr){
            currentPath.push(currentNode);
            currentNode = currentNode->left;
        }

        currentNode = currentPath.top();
        currentPath.pop();

        values.push_back(currentNode->val);

        currentNode = currentNode->right;
    }
    return values;
}

int getNodeLevel(TreeNode* node, int val, int level){
    if(!node) return 0;
    if(node->val == val) return level;

    int l = getNodeLevel(node->left, val, level + 1);
    if(l != 0) return l;

    return getNodeLevel(node->right, val, level + 1);
}

bool isSibling(TreeNode* node, int a, int b){
    if(!node) return false;
    if((node->left && node->right) &&((node->left->val == a && node->right->val == b) ||
        (node->left->val== b && node->right->val == a) ||
        isSibling(node->left, a, b) ||
        isSibling(node->right, a, b))){
            return true;
        }
}

void inorderTraversal(TreeNode* node, int B, int level, int desiredLevel, TreeNode* root, vector<int>& result){
    if(!node) return;
    inorderTraversal(node->left, B, level + 1, desiredLevel, root, result);
    if(node->val != B && level == desiredLevel && !isSibling(root, node->val, B) &&
    !isSibling(root, node->val, B)){
        result.push_back(node->val);
        return;
    }
    inorderTraversal(node->right, B, level + 1, desiredLevel, root, result);
}

vector<int> solve(TreeNode* A, int B) {
    int nodeLevel = getNodeLevel(A, B, 0);
    vector<int> result;
    inorderTraversal(A, B, 0, nodeLevel, A, result);

    return result;
}

int kthsmallest_1(TreeNode* A, int& B){
	if(!A) return numeric_limits<int>::max();

	int value_left = kthsmallest_1(A->left, B);

	B--;
	if(B == 0) return A->val;

	int value_right = kthsmallest_1(A->right, B);


	return (value_left != numeric_limits<int>::max()) ? value_left : value_right;
}

int kthsmallest(TreeNode* A, int B) {
	return kthsmallest_1(A, B);
}

void t2sum_1(TreeNode* A, int B, unordered_set<int>& uset, bool& found){
	if(!A || found) return;

	t2sum_1(A->left, B, uset, found);
	if(uset.empty()){
		uset.insert(A->val);
	}else{
		int temp = B - A->val;
		if(uset.find(temp) != uset.end()){
			found = true;
			return;
		}else{
			uset.insert(A->val);
		}
	}
	t2sum_1(A->right, B, uset, found);
}

int t2Sum(TreeNode* A, int B) {
	unordered_set<int> uset;
	bool found = false;

	t2sum_1(A, B, uset, found);

	return found;
}

queue<int> values_queue;

void fill_queue(TreeNode* A, queue<int>& values_queue){
	if(!A) return;

	fill_queue(A->left, values_queue);
	values_queue.push(A->val);
	fill_queue(A->right, values_queue);
}

class BSTIterator {
public:
	BSTIterator(TreeNode *root){
		fill_queue(root, values_queue);
	}
	bool hasNext() {
		return !values_queue.empty();
	}
	int next() {
		int value = values_queue.front();
		values_queue.pop();
		return value;
	}
};

enum child_position_t{LEFT, RIGHT, NONE};

bool is_half_node(TreeNode* node, child_position_t& child_position){
	int num_children = 0;
	if(node->left) {
		num_children++;
		child_position = LEFT;
	}
	if(node->right) {
		num_children++;
		child_position = RIGHT;
	}

	return (num_children == 1) ? true : false;
}

void removehalfnodes_internal(TreeNode* current_node, TreeNode** prev_node){
	if(!current_node)	return;

	removehalfnodes_internal(current_node->left, &current_node);

	child_position_t child_position;
	if(is_half_node(current_node, child_position)){
		//remove the node
		if(child_position == LEFT){
			if(*prev_node) (*prev_node)->left = current_node->left;
			else *prev_node = new TreeNode(current_node->left->val);
		}else{
			if(*prev_node) (*prev_node)->right = current_node->right;
			else *prev_node = new TreeNode(current_node->left->val);
		}

		delete current_node;
	}

	removehalfnodes_internal(current_node->right, &current_node);
}

TreeNode* removehalfnodes_1(TreeNode* A) {
	TreeNode* temp_node{nullptr};
	removehalfnodes_internal(A, &temp_node);

	return (temp_node) ? temp_node : A;
}



void path_to_node_internal(TreeNode* A, int B, vector<int>& path, bool& found){
	if(!A || found) return;

	path.push_back(A->val);

	path_to_node_internal(A->left, B, path, found);

	if(A->val == B){
		found = true;
		return;
	}

	path_to_node_internal(A->right, B, path, found);

	if(!found)
	path.pop_back();
}

vector<int> pathToNode(TreeNode* A, int B) {
	vector<int> result;
	bool found = false;
	path_to_node_internal(A, B, result, found);
	return result;
}

void recover_tree_internal_1(TreeNode* A, set<int>& values_set){
	if(!A) return;

	recover_tree_internal_1(A->left, values_set);
	values_set.insert(A->val);
	recover_tree_internal_1(A->right, values_set);
}

void recover_tree_internal_2(TreeNode* A, int& index, const set<int>& values_set, vector<int>& result){
	if(!A) return;

	recover_tree_internal_2(A->left, index, values_set, result);

	auto it = values_set.begin();
	advance(it, index);
	if(it != values_set.end()){
		if(*it != A->val){
			result.push_back(*it);
		}
		++index;
	}
	recover_tree_internal_2(A->right, index, values_set, result);
}

void recover_tree_internal(TreeNode* current, TreeNode* prev, child_position_t child_position, vector<int>& result){
	if(!current) return;

	recover_tree_internal(current->left, current, LEFT, result);

	if(child_position == LEFT){
		if(current->val > prev->val){
			result.push_back(current->val);
		}
	}else if(child_position == RIGHT){
		if(current->val < prev->val){
			result.push_back(current->val);
		}
	}else{

		if(current->left && current->val < current->left->val){
			result.push_back(current->val);
		}
		if(current->right && current->val > current->right->val){
			result.push_back(current->val);
		}
	}

	recover_tree_internal(current->right, current, RIGHT, result);
}

vector<int> recoverTree(TreeNode* A) {
	set<int> values_set;
	vector<int> result;
	int index = 0;

	recover_tree_internal_1(A, values_set);
	recover_tree_internal_2(A, index, values_set, result);

	return result;

	/*vector<int> result;
	recover_tree_internal(A, A, NONE, result);
	return result;*/
}

void verticalOrderTraversal_internal(TreeNode* A, int column_id, set<int>& dict, int& offset, vector<vector<int>>& result){
	if(!A) return;

	auto it = dict.find(column_id);
	if(it != dict.end()){
		result[column_id + offset].push_back(A->val);
	}else{
		vector<int> temp(1, A->val);
		if(!dict.empty() && column_id < *dict.begin()){
			result.insert(result.begin(), temp);
			offset++;
		}else{
			result.insert(result.end(), temp);
		}

		dict.insert(column_id);
	}

	verticalOrderTraversal_internal(A->left, column_id - 1, dict, offset, result);
	verticalOrderTraversal_internal(A->right, column_id + 1, dict, offset, result);
}

vector<vector<int> > verticalOrderTraversal(TreeNode* A) {
	vector<vector<int>> result;
	set<int> dict;
	int offset = 0;
	verticalOrderTraversal_internal(A, 0, dict, offset, result);

	return result;
}

void diagonal_traverse_internal(TreeNode* A, int distance, map<int, vector<int>>& values){
	if(!A) return;

	values[distance].push_back(A->val);

	diagonal_traverse_internal(A->left, distance + 1, values);
	diagonal_traverse_internal(A->right, distance, values);
}

/*void diagonal_traverse_internal(TreeNode* A, int column_id, int height, unordered_map<int, multimap<int, int>>& nodes){
	if(!A) return;

	auto it = nodes.find(column_id);
	if(it != nodes.end()){
		it->second.insert(make_pair(height, A->val));
	}else{
		multimap<int, int> temp;
		temp.insert(make_pair(height, A->val));
		nodes.insert(make_pair(column_id, temp));
	}

	diagonal_traverse_internal(A->left, column_id - 1, height + 1, nodes);
	diagonal_traverse_internal(A->right, column_id + 1, height + 1, nodes);
}*/

vector<int> diagonal_traverse(TreeNode* A){
	/*unordered_map<int, multimap<int, int>> nodes;
	vector<int> result;

	diagonal_traverse_internal(A, 0, 0, nodes);
node_cousins_internal
	int start_column = 0;
	while(nodes.find(start_column) != nodes.end()){
		int column_id = start_column;
		auto it = nodes.find(column_id);
		while(it != nodes.end()){
			result.push_back(it->second.begin()->second);
			it->second.erase(it->second.begin());
			it = nodes.find(column_id);
			while(it != nodes.end()){
				result.push_back(it->second.begin()->second);
				it->second.erase(it->second.begin());
				it = nodes.find(column_id);
			}
			column_id++;
		}
		start_column--;
	}

	return result;*/

	vector<int> results;
	map<int, vector<int>> values;
	diagonal_traverse_internal(A, 0, values);
	for(auto it = values.begin(); it != values.end(); ++it){
		for(auto& a : it->second){
			results.push_back(a);
		}
	}

	return results;
}

void inorder_traversal_internal(TreeNode* A, vector<int>& result){
	if(!A) return;

	inorder_traversal_internal(A->left, result);
	result.push_back(A->val);
	inorder_traversal_internal(A->right, result);
}

void dig_left(TreeNode* A, stack<TreeNode*>& nodes){
	while(A){
		nodes.push(A);
		A = A->left;
	}
}

vector<int> inorder_traversal(TreeNode*A){
	vector<int> result;
	stack<TreeNode*> nodes_stack;

	while(A || !nodes_stack.empty()){
		if(!A && !nodes_stack.empty()){
			A = nodes_stack.top();
			nodes_stack.pop();
			result.push_back(A->val);
			A = A->right;
		}else{
			nodes_stack.push(A);
			A = A->left;
		}
	}

	return result;
}

struct node{
	TreeNode* A{nullptr};
	bool done{false};
	node(TreeNode* A): A(A), done(false){};
};

vector<int> postorder_traversal(TreeNode* A){
	vector<int> result;
	stack<node> nodes_stack;
	node node_A{nullptr};

	while(A || !nodes_stack.empty()){
		if(!A && !nodes_stack.empty()){
			node_A = nodes_stack.top();
			nodes_stack.pop();
			if(node_A.done)	{
				result.push_back(node_A.A->val);
				A = nullptr;
			}else{
				A = node_A.A->right;
				node_A.done = true;
				nodes_stack.push(node_A);
			}
		}else{
			nodes_stack.push(node{A});
			A = A->left;
		}
	}

	return result;
}

vector<int> preorder_traversal(TreeNode* A){
	vector<int> result;
	stack<TreeNode*> nodes_stack;

	while(A || !nodes_stack.empty()){
		if(!A && !nodes_stack.empty()){
			A = nodes_stack.top();
			nodes_stack.pop();
			A = A->right;
		}else{
			result.push_back(A->val);
			nodes_stack.push(A);
			A = A->left;
		}
	}

	return result;
}



/*
 * int getNodeLevel(TreeNode* node, int val, int level){
    if(!node) return 0;
    if(node->val == val) return level;

    int l = getNodeLevel(node->left, val, level + 1);
    if(l != 0) return l;

    return getNodeLevel(node->right, val, level + 1);
}

void getLevelNodes(TreeNode* node, int B, int level, vector<int>& result){
    if(node == nullptr, level < 2) return;

    if(level == 2){
        if((node->left && node->left->val == B) || (node->right && node->right->val == B))
            return;
        if(node->left)
            result.push_back(node->left->val);
        if(node->right)
            result.push_back(node->right->val);
    }else{
        getLevelNodes(node->left, B, level - 1, result);
        getLevelNodes(node->right, B, level - 1, result);
    }
}

    int nodeLevel = getNodeLevel(A, B, 1);
    vector<int> result;
    getLevelNodes(A, B, nodeLevel, result);

    return result;
 */

int get_height_siblings(TreeNode* A, int node_value, int height){
	if(!A) return numeric_limits<int>::min();

	if(A->val == node_value) {
		return height;
	}
	int ret_1 = get_height_siblings(A->left, node_value, height + 1);
	int ret_2 = get_height_siblings(A->right, node_value, height + 1);

	return (ret_1 == numeric_limits<int>::min()) ? ret_2 : ret_1;
}

bool is_sibling(TreeNode* A, int B){
	if(A->left->val == B || A->right->val == B) return true;
	return false;
}

void node_cousins_internal(TreeNode* A, TreeNode* prev, int level, int desired_level, vector<int>& result, int B){
	if(!A) return;

	if(desired_level == 0&& level == 0){
		return;
	}
	if(level == desired_level && !is_sibling(prev, B)){
		result.push_back(A->val);
	}

	node_cousins_internal(A->left, A, level + 1, desired_level, result, B);
	node_cousins_internal(A->right, A, level + 1, desired_level, result, B);
}

void node_cousins_internal_1(TreeNode* A, TreeNode* prev, int& sibling, int B, int height_of_val, int& level, unordered_multimap<int, int>& nodes){
	if(!A) return;

	if(A->val == B){
		if(height_of_val == 0) return;
		level = height_of_val;
		if(prev->left == A && prev->right) sibling = prev->right->val;
		else if(prev->right == A && prev->right) sibling = prev->left->val;
	}

	nodes.insert(make_pair(height_of_val, A->val));
	node_cousins_internal_1(A->left, A, sibling, B, height_of_val + 1, level, nodes);
	node_cousins_internal_1(A->right, A, sibling, B, height_of_val + 1, level, nodes);
}
vector<int> node_cousins(TreeNode* A, int B){
	/*int height = 0;
	vector<int> result;
	height = get_height_siblings(A, B, 0);
	node_cousins_internal(A, A, 0, height, result, B);
	return result;*/

	unordered_multimap<int, int> nodes;
	vector<int> result;
	int level = 0, sibling;
	node_cousins_internal_1(A, A, sibling, B, 0, level, nodes);
	auto it_range = nodes.equal_range(level);
	for(auto it = it_range.first; it != it_range.second; ++it){
		if(it->second != B && it->second != sibling)
			result.push_back(it->second);
	}
	return result;
}

void zigzagLevelOrder_internal(TreeNode* A, int height, unordered_map<int, vector<int>>& levels_map){
	if(!A) return;

	levels_map[height].push_back(A->val);
	zigzagLevelOrder_internal(A->left, height + 1, levels_map);
	zigzagLevelOrder_internal(A->right, height + 1, levels_map);
}

vector<vector<int> > zigzagLevelOrder(TreeNode* A) {
	vector<vector<int>> result;
	unordered_map<int, vector<int>> levels_map;
	bool flip = false;

	zigzagLevelOrder_internal(A, 0, levels_map);

	for(int i = 0; i < levels_map.size(); ++i){
		if(flip){
			reverse(levels_map[i].begin(), levels_map[i].end());
		}
		result.push_back(levels_map[i]);
		flip = (flip) ? false : true;
	}

	return result;
}

void print_level(TreeNode* A, int level){
	if(!A) return;

	if(level == 1) cout<<A->val<<" ";
	else{
		print_level(A->left, level - 1);
		print_level(A->right, level - 1);
	}
}

int get_height(TreeNode* A, int level){
	if(!A) return numeric_limits<int>::min();

	int h_1 = get_height(A->left, level + 1);
	int h_2 = get_height(A->right, level + 1);

	return (h_1 > h_2) ? h_1 : h_2;
}

void level_order_traversal(TreeNode* A){
	int tree_height = get_height(A, 1);

	for(auto i = 1; i < tree_height; ++i){
		print_level(A, i);
		cout<<endl;
	}
}

struct TreeLinkNode {
 int val;
 TreeLinkNode *left, *right, *next;
 TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

int get_tree_height(TreeLinkNode* A, int level){
	if(!A) return numeric_limits<int>::min();

	int h1 = get_tree_height(A->left, level + 1);
	int h2 = get_tree_height(A->right, level + 1);

	return (h1 > h2) ? h1 : h2;
}

void get_level_nodes(TreeLinkNode* A, int level, vector<TreeLinkNode*>& nodes){
	if(!A) return;
	if(level == 1) {
		nodes.push_back(A);
	}else{
		get_level_nodes(A->left, level - 1, nodes);
		get_level_nodes(A->right, level - 1, nodes);
	}
}

void connect(TreeLinkNode* A) {
	int tree_height = get_tree_height(A, 1);
	vector<TreeLinkNode*> nodes;

	for(auto i = 1; i < tree_height; ++i){
		get_level_nodes(A, i, nodes);

		for(auto j = 0; j < nodes.size() - 1; ++j){
			nodes[j]->next = nodes[j + 1];
		}

		nodes.clear();
	}
}

void isSameTree_internal(TreeNode* A, TreeNode* B, bool& same){
	if(!A && !B) return;
	if(!A && B) {
		same = false;
		return;
	}
	if(A && !B){
		same = false;
		return;
	}

	isSameTree_internal(A->left, B->left, same);
	if(A->val != B->val) same = false;
	isSameTree_internal(A->right, B->right, same);
}

int isSameTree(TreeNode* A, TreeNode* B) {
	bool same = true;
	isSameTree_internal(A, B, same);
	return same;
}

inline bool is_mirror(vector<TreeNode*>& nodes){
	int i = (nodes.size() - 1) / 2, j = i + 1;

	while(i >= 0 && j < nodes.size()){
		if(nodes[i] && !nodes[j]) return false;
		if(!nodes[i] && nodes[j]) return false;
		if(nodes[i]->val != nodes[j]->val) return false;
		i--;
		j++;
	}

	return true;
}

void get_level_nodes_1(TreeNode* A, int level, int actual_level, unordered_map<int, vector<TreeNode*>>& nodes, bool& mirror){
	if(level == 0) return;
	if(level == 1) {
		nodes[actual_level].push_back(A);
		if(nodes[actual_level].size() == pow(2, actual_level) && !is_mirror(nodes[actual_level])) mirror = false;
	}else{
		get_level_nodes_1(A->left, level - 1, actual_level, nodes, mirror);
		get_level_nodes_1(A->right, level - 1, actual_level, nodes, mirror);
	}
}

int get_tree_height_1(TreeNode* A, int level){
	if(!A) return level - 1;

	int h1 = get_tree_height_1(A->left, level + 1);
	int h2 = get_tree_height_1(A->right, level + 1);

	return (h1 > h2) ? h1 : h2;
}


int isSymmetric(TreeNode* A) {
	int tree_height = get_tree_height_1(A, 1);
	bool mirror = true;
	unordered_map<int, vector<TreeNode*>> nodes;

	for(int i = 1; i <= tree_height; ++i){
		get_level_nodes_1(A, i, i - 1, nodes, mirror);
	}

	return mirror;
}

void get_root(const vector<int>& A, int start, int end, TreeNode** root){
	if(start > end) return;

	int mid = (start + end) / 2;
	*root = new TreeNode(A[mid]);

	get_root(A, start, mid - 1, &((*root)->left));
	get_root(A, mid + 1, end, &((*root)->right));
}

TreeNode* sortedArrayToBST(const vector<int> &A) {
	TreeNode* root;
	get_root(A, 0, A.size() - 1, &root);
	return root;
}

void get_root(vector<int>& A, vector<int>& B, int start, int end, TreeNode** root){
	if(start > end) return;

	if(start == end){
		*root = new TreeNode(A[start]);
		return;
	}

	int end_b = 0;
	for(int i = start; i <= end; ++i){
		int temp = find(B.begin(), B.end(), A[i]) - B.begin();
		end_b = (temp > end_b) ? temp : end_b;
	}

	vector<int>::iterator it_start = A.begin();
	vector<int>::iterator it_end = A.begin();
	advance(it_start, start);
	advance(it_end, end + 1);
	auto root_it = find(it_start, it_end, B[end_b]);
	*root = new TreeNode(*root_it);

	get_root(A, B, start, (root_it - A.begin()) - 1, &(*root)->left);
	get_root(A, B, (root_it - A.begin()) + 1, end, &(*root)->right);
}

void get_root_1(vector<int>& A, vector<int>& B, int start, int end, int& root_index, unordered_map<int, int>& nodes, TreeNode** root){
	if(start > end) return;

	if(start == end) {
		*root = new TreeNode(A[start]);
		return;
	}
	*root = new TreeNode(B[root_index]);
	int A_index = nodes[B[root_index]];
	if(start == 0 && end == B.size() - 1) root_index--;
	else root_index -= (end - start) + 1;

	get_root_1(A, B, A_index + 1, end, root_index, nodes, &(*root)->right);
	get_root_1(A, B, start, A_index - 1, root_index, nodes, &(*root)->left);
}

TreeNode* buildTree(vector<int> &A, vector<int> &B) {
	TreeNode* root;
	unordered_map<int, int> nodes;
	int root_index = B.size() - 1;
	for(int i = 0; i < A.size(); ++i){
		nodes[A[i]] = i;
	}

	//get_root(A, B, 0, A.size() - 1, &root);

	get_root_1(A, B, 0, A.size() - 1, root_index, nodes, &root);

	return root;
}

void get_root_2(vector<int>& in_order, vector<int>& pre_order, int start, int end, int& root_in_pre, unordered_map<int, int> nodes, TreeNode** root){
	if(start > end) return;
	if(start == end){
		*root = new TreeNode(in_order[start]);
		return;
	}
	*root = new TreeNode(pre_order[root_in_pre]);
	if(start == 0 && end == pre_order.size() - 1) root_in_pre++;
	else root_in_pre += (end - start) + 1;

	get_root_2(in_order, pre_order, start, nodes[(*root)->val] - 1, root_in_pre, nodes, &(*root)->left);
	get_root_2(in_order, pre_order, nodes[(*root)->val] + 1, end, root_in_pre, nodes, &(*root)->right);
}

TreeNode* buildTree_PreIn(vector<int> &A, vector<int> &B) {
	TreeNode* root;
	int root_in_pre = 0;
	unordered_map<int, int> nodes;
	for(int i = 0; i < A.size(); ++i){
		nodes[B[i]] = i;
	}
	get_root_2(B, A, 0, A.size() - 1, root_in_pre, nodes, &root);

	return root;
}


void inorder_print(TreeNode* A){
	if(!A) return;

	inorder_print(A->left);
	cout<<A->val<<" ";
	inorder_print(A->right);
}

inline bool is_leaf(TreeNode* A){
	if(!A->left && !A->right) return true;
	return false;
}

void hasPathSum_internal(TreeNode* A, int desired_sum, int sum, bool& sum_exists){
	if(!A) return;

	sum += A->val;
	if(is_leaf(A) && sum == desired_sum){
		sum_exists = true;
		return;
	}

	hasPathSum_internal(A->left, desired_sum, sum, sum_exists);
	hasPathSum_internal(A->right, desired_sum, sum, sum_exists);
}

int hasPathSum(TreeNode* A, int B) {
	bool sum_exists = false;
	hasPathSum_internal(A, B, 0, sum_exists);
	return sum_exists;
}

void hasPathSum_internal_1(TreeNode* A, int desired_sum, int sum, int root_val, vector<vector<int>>& paths){
	if(!A) return;

	paths[paths.size() - 1].push_back(A->val);
	sum += A->val;
	if(is_leaf(A) && sum == desired_sum){
		paths.push_back(vector<int>(1, root_val));
		return;
	}

	hasPathSum_internal_1(A->left, desired_sum, sum, root_val, paths);
	hasPathSum_internal_1(A->right, desired_sum, sum, root_val, paths);
	if(paths[paths.size() - 1].size() > 1) paths[paths.size() - 1].pop_back();
}

vector<vector<int> > pathSum(TreeNode* A, int B) {
	vector<vector<int>> paths;
	paths.push_back(vector<int>());
	hasPathSum_internal_1(A, B, 0, A->val, paths);
	paths.pop_back();
	return paths;
}

void min_depth_internal(TreeNode* A, int depth, int& min_depth){
	if(!A) return;
	depth++;
	if(is_leaf(A) && depth < min_depth) {
		min_depth = depth;
		return;
	}

	min_depth_internal(A->left, depth, min_depth);
	min_depth_internal(A->right, depth, min_depth);
}

int minDepth(TreeNode* A) {
	int min_depth = numeric_limits<int>::max();
	min_depth_internal(A, 0, min_depth);
	return min_depth;
}

void get_path(TreeNode* A, int value, int height, unordered_map<int, int>& path, bool& found){
	if(!A || found) return;

	path[height] = A->val;
	if(A->val == value) {
		found = true;
		return;
	}

	get_path(A->left, value, height + 1, path, found);
	get_path(A->right, value, height + 1, path, found);

	if(!found) path.erase(height);
}

int get_common_node(unordered_map<int, int>& A, unordered_map<int, int>& B){
	for(int i = B.size() - 1; i >= 0; --i){
		int temp = B[i];
		auto it = A.find(i);
		if(it != A.end()){
			if(it->second == temp){
				return temp;
			}
		}
	}
	return -1;
}

int lca(TreeNode* A, int B, int C) {
	bool found = false;
	unordered_map<int, int> path_B, path_C;
	get_path(A, B, 0, path_B, found);
	if(path_B[path_B.size() - 1] != B) return -1;
	found = false;
	get_path(A, C, 0, path_C, found);
	if(path_C[path_C.size() - 1] != C) return -1;

	return get_common_node(path_B, path_C);
}

void flatten_internal(TreeNode* A, stack<TreeNode*>& nodes_stack){
	if(!A) return;

	if(A->left){
		if(A->right){
			nodes_stack.push(A->right);
		}
		A->right = A->left;
	}else if(is_leaf(A) && !nodes_stack.empty()){
		A->right = nodes_stack.top();
		nodes_stack.pop();
	}

	flatten_internal(A->left, nodes_stack);
	flatten_internal(A->right, nodes_stack);

	A->left = nullptr;
}

void flatten_internal_1(TreeNode* A){
	if(!A || is_leaf(A)) return;

	if(A->left){
		if(A->right){
			TreeNode* temp_node = A->right;
			A->right = A->left;
			TreeNode* t = A->right;
			while(t->right){
				t = t->right;
			}
			t->right = temp_node;
		}else{
			A->right = A->left;
		}
	}

	flatten_internal_1(A->left);
	flatten_internal_1(A->right);

	A->left = nullptr;
}
TreeNode* flatten(TreeNode* A) {
	/*stack<TreeNode*> nodes_stack;
	flatten_internal(A, nodes_stack);*/
	flatten_internal_1(A);
	return A;
}

void merge_trees_internal(TreeNode* A, TreeNode* B, TreeNode** C){
	if(!A && !B) return;

	if(A){
		if(B){
			*C = new TreeNode(A->val + B->val);
		}else{
			*C = new TreeNode(A->val);
		}
	}else if(B){
		*C = new TreeNode(B->val);
	}

	merge_trees_internal((A) ? A->left : nullptr, (B) ? B->left : nullptr, &(*C)->left);
	merge_trees_internal((A) ? A->right : nullptr, (B) ? B->right : nullptr, &(*C)->right);
}

TreeNode* merge_trees(TreeNode* A, TreeNode* B) {
	TreeNode* C;
	merge_trees_internal(A, B, &C);
	return C;
}

///////////////////////////////////
void test_merge_trees(){
	TreeNode* A ;
	A = new TreeNode(2);
	A->left = new TreeNode(1);
	A->right = new TreeNode(4);
	A->left->left = new TreeNode(5);

	TreeNode* B;
	B = new TreeNode(3);
	B->left = new TreeNode(6);
	B->right = new TreeNode(1);
	B->left->right = new TreeNode(2);
	B->right->right = new TreeNode(7);

	auto result = merge_trees(A, B);

	inorder_print(result);
}
void test_flatten(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(5);
	A->left->left = new TreeNode(3);
	A->left->right = new TreeNode(4);
	A->right->left = new TreeNode(6);

	flatten(A);
	inorder_print(A);
}
void test_lca(){
	TreeNode* A;
	A=  new TreeNode(3);
	A->left = new TreeNode(5);
	A->right = new TreeNode(1);
	A->left->left = new TreeNode(6);
	A->left->right = new TreeNode(2);
	A->left->right->left = new TreeNode(7);
	A->left->right->right = new TreeNode(4);
	A->right->left = new TreeNode(0);
	A->right->right = new TreeNode(8);

	cout<<lca(A, 6, 0);
}
void test_min_depth(){
	TreeNode* A;
	A = new TreeNode(1);
	A->left = new TreeNode(2);

	cout<<minDepth(A);
}

void test_pathSum(){
	//TreeNode* root;
	/*A = new TreeNode(5);
	A->left = new TreeNode(4);
	A->right = new TreeNode(8);
	A->left->left = new TreeNode(11);
	A->left->left->left = new TreeNode(7);
	A->left->left->right = new TreeNode(2);
	A->right->left = new TreeNode(13);
	A->right->right = new TreeNode(4);
	A->right->right->left = new TreeNode(5);
	A->right->right->right = new TreeNode(1);*/
	TreeNode* root  = new TreeNode(10);
	    root->left  = new TreeNode(28);
	    root->right = new TreeNode(13);

	    root->right->left   = new TreeNode(14);
	    root->right->right  = new TreeNode(15);

	    root->right->left->left   = new TreeNode(21);
	    root->right->left->right  = new TreeNode(22);
	    root->right->right->left  = new TreeNode(23);
	    root->right->right->right = new TreeNode(24);

	auto result = pathSum(root, 38);
	for(auto& a: result){
		for(auto& b : a){
			cout<<b<<" ";
		}
		cout<<endl;
	}
}
void test_hasPathSum(){
	TreeNode* A;
	A = new TreeNode(5);
	A->left = new TreeNode(4);
	A->right = new TreeNode(8);
	A->left->left = new TreeNode(11);
	A->left->left->left = new TreeNode(7);
	A->left->left->right = new TreeNode(2);
	A->right->left = new TreeNode(13);
	A->right->right = new TreeNode(4);
	A->right->right->right = new TreeNode(1);

	cout<<hasPathSum(A, 3);
}

void test_buildTree_PreIn(){
	vector<int> A{3,2,1,4,5}, B{1,2,3,4,5};
	auto root = buildTree_PreIn(A, B);
	inorder_print(root);
}

void test_buildTree(){
	vector<int> A{1, 2, 3, 4, 5, 6}, B{1,3,2,6,5,4};
	auto root = buildTree(A, B);
	inorder_print(root);
}

void test_sortedArrayToBST(){
	vector<int> A{1, 2, 3, 4, 5 ,6};
	TreeNode* root = sortedArrayToBST(A);
	inorder_print(root);
}

void test_isSymmetric(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(2);
	A->left->left = new TreeNode(4);
	A->left->right = new TreeNode(5);
	A->right->left = new TreeNode(5);
	A->right->right = new TreeNode(4);

	cout<<isSymmetric(A);
}

void test_isSameTree_internal(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);
	A->left->left = new TreeNode(4);
	A->left->right = new TreeNode(5);
	A->right->left = new TreeNode(6);
	A->right->right = new TreeNode(7);

	TreeNode* B ;
	B = new TreeNode(1);
	B->left = new TreeNode(2);
	B->right = new TreeNode(3);
	B->left->left = new TreeNode(4);
	B->left->right = new TreeNode(5);
	B->right->left = new TreeNode(6);

	cout<<isSameTree(A, B);
}

void test_level_order_traversal(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);
	A->left->left = new TreeNode(4);
	A->left->right = new TreeNode(5);
	A->right->left = new TreeNode(6);
	A->right->right = new TreeNode(7);

	level_order_traversal(A);
}

void test_zigzagLevelOrder(){
	TreeNode* A ;
	A = new TreeNode(3);
	A->left = new TreeNode(9);
	A->right = new TreeNode(20);
	A->right->left = new TreeNode(15);
	A->right->right = new TreeNode(7);

	auto result = zigzagLevelOrder(A);
	for(auto& a : result){
		for(auto& b : a){
			cout<<b<<" ";
		}
		cout<<endl;
	}
}
void test_node_cousins(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);
	A->left->left = new TreeNode(4);
	A->left->right = new TreeNode(5);
	A->right->left = new TreeNode(6);
	A->right->right = new TreeNode(7);
	auto result = node_cousins(A, 5);
	for(auto& a : result){
		cout<<a<<" ";
	}
}
void preorder_traversal(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);

	auto result = preorder_traversal(A);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void test_postorder_traversal(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->right = new TreeNode(2);
	A->right->left = new TreeNode(3);

	auto result = postorder_traversal(A);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void test_inordertraversal(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->right = new TreeNode(2);
	A->right->left = new TreeNode(3);

	auto result = inorder_traversal(A);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void test_diagonal_traverse(){
	TreeNode* A ;
	A = new TreeNode(1);
	A->left = new TreeNode(4);
	A->right = new TreeNode(2);
	A->left->left = new TreeNode(8);
	A->left->right = new TreeNode(5);
	A->left->right->left = new TreeNode(9);
	A->left->right->right = new TreeNode(7);
	A->right->right = new TreeNode(3);
	A->right->right->left = new TreeNode(6);

	auto result = diagonal_traverse(A);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void test_verticalOrderTraversal(){
	TreeNode* A ;
	A = new TreeNode(6);
	A->left = new TreeNode(3);
	A->right = new TreeNode(7);
	A->left->left = new TreeNode(2);
	A->left->right = new TreeNode(5);
	A->right->right = new TreeNode(9);
	A->left->right->right = new TreeNode(12);
	A->right->left = new TreeNode(10);
	A->right->left->left = new TreeNode(13);
	/*A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);
	A->left->left = new TreeNode(4);
	A->left->right = new TreeNode(5);*/

	auto result = verticalOrderTraversal(A);

	for(auto& a : result){
		for(auto& b : a){
			cout<<b<<" ";
		}
		cout<<endl;
	}
}

void test_recoverTree(){
	TreeNode* A;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);

	auto result = recoverTree(A);

	for(auto& a : result){
		cout<<a<<" ";
	}
}

void test_pathToNode(){
	TreeNode* A;
	A = new TreeNode(1);
	A->left = new TreeNode(2);
	A->right = new TreeNode(3);
	A->left->left = new TreeNode(4);
	A->left->right = new TreeNode(5);
	A->right->left = new TreeNode(6);
	A->right->right = new TreeNode(7);

	auto result = pathToNode(A, 4);
	for(auto& a : result){
		cout<<a<<" ";
	}
}

void test_removehalfnodes_1(){
	TreeNode* A;
	A = new TreeNode(13);
	A->left = new TreeNode(18);
	A->right = new TreeNode(14);
	A->left->left = new TreeNode(20);
	A->left->right = new TreeNode(10);
	A->right->left = new TreeNode(27);
	A->right->right = new TreeNode(25);

	auto result = removehalfnodes_1(A);
	inorder_print(result);
}

void test_BSTIterator(){
	TreeNode A{2};
	A.left = new TreeNode(1);
	A.right = new TreeNode(3);

	BSTIterator i(&A);
	while (i.hasNext()) cout << i.next();
}
void test_kthsmallest(){
	TreeNode A{2};
	A.left = new TreeNode(1);
	A.right = new TreeNode(3);

	cout<<kthsmallest(&A, 3);
}

void test_t2sum(){
	TreeNode A{10};
	A.left = new TreeNode(9);
	A.right = new TreeNode(20);
	cout<<t2Sum(&A, 40);
}
