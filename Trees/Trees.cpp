/*
Trees.cpp
 *
 Created on: Jul 8, 2020
     Author: messam
 */
#include "Headers.hpp"

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

