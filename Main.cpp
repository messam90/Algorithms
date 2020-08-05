/*
 * Main.cpp
 *
 *  Created on: Jul 3, 2020
 *      Author: messam
 */
#include "Headers.hpp"
#include "Heaps_Maps.hpp"
#include "Hashing.hpp"

int main(){
	//testSolveMaps();
	//testNchoc();
	//testmergeKLists();
	//testLRUCache();
	//testColorful();
	//testLszero();
	//testtwoSum();
	//testfourSum();
	//testisValidSudoku();
	//testdiffPossible();
	//testanagrams();
	//test_equal();
	//test_copyRandomList();
	//test_lengthOfLongestSubstring();
	test_minWindow();
}


/*int main() {*/
  /*vector<vector<int>> matrix = generateMatrix(4);

  for(auto& a : matrix){
    for(auto& b : a){
      cout<<b<<", ";
    }

    cout<<endl;
  }*/

  /*vector<vector<int>> triangle = generateTriangle(8);
  for(auto& a : triangle){
    for(auto& b : a){
      cout<<b<<", ";
    }

    cout<<endl;
  }*/

	/*vector<int> triangleRow = generateRow_2(6);
	for(auto& a : triangleRow){
		cout<<a<<", ";
	}
	cout<<endl;*/
	/*vector<vector<int>> A{{1,2,3}, {4,5,6}, {7,8,9}};
	vector<vector<int>> diagonalOutput = diagonal_2(A);
	for(auto& a : diagonalOutput){
		for(auto& b : a){
			cout<<b<<", ";
	    }
int search(const vector<int> &A, int B)
	    cout<<endl;
	}*/
	/*vector<int> primeSumValues = primesum(16777214);
	for(auto& a : primeSumValues){
		cout<<a<<" ";
	}
	cout<<endl;*/

	/*vector<string> fizzBuzzRet = fizzBuzz(5);
	for(auto& a : fizzBuzzRet){
		cout<<a<<", ";
	}*/

	//cout<<titleToNumbstruct TreeNode {

	//cout<<isPalindrome(1);

	//cout<<reverseInt(-1146467285);

	//cout<<gcd(1, 0);

	//cout<<trailingZeroes(9250);

	//cout<<cpFact(1, 1);

	/*vector<int> A{1, 2, 7, 0, 9, 3, 6, 8, 5, 4 };
	arrange(A);
	for(auto& a : A){
		cout<<a<<" ";
	}*/

	//cout<<uniquePaths(3,3);
	/*vector<int> A{2, 8, 8, 8, 8, 9};
	cout<<findCount(A, 9);*/
	/*vector<int> A{4, 5, 6, 7, 0, 1, 2};
	cout<<findMin(A);*/

	//cout<<sqrt(2147483647);

	/*vector<vector<int>> A{{1,3,5,7}, {10,11,16,20}, {23,30,34,50}};
	cout<<searchMatrix(A, 23);*/

	//cout<<pow(2, 3, 3);

	/*vector<int> A{4,5,6,7,0,1,2,3};
	cout<<search(A, 0);*/

	/*string s{"1a2"};
	cout<<stringisPalindrome(s);*/

	/*vector<string> A{"abcdefgh", "aefghijk", "abcefgh"};
	cout<<longestCommonPrefix(A);*/

	//cout<<strStr("needle", "needlahaystackneedla");

	//cout<<solve("AACECAAAA");

	//cout<<lengthOfLastWord("HelloWorld  ");

	//cout<<compareVersion("4444371174137455", "5.168");

	//cout<<romanToInt("XX");

	/*vector<string> inText{"What", "must", "be", "shall", "be."};
	vector<string> outText = fullJustify(inText, 12);
	  for(auto& a : outText){
		  cout<<"\"";
	    for(auto& b : a){
	      cout<<b;
	    }
	    cout<<"\"";
	    cout.flush();
	    cout<<endl;
	  }*/

	//cout<<numSetBits(11);
	/*vector<int> A{0, 4, 7, 9};
	cout<<findMinXor(A);*/

	//cout<<singleNumber({1, 2, 2, 3, 1});
	/*vector<int> A{1, 5, 8};
	vector<int> B{6, 9};
	merge(A, B);
	for(auto& a : A){
		cout<<a<<" ";
	}*/
	/*vector<int> A{2147483647, -2147483648, -2147483648, 0, 1};
	cout<<threeSumClosest(A, 0);*/
	/*ListNode A(1), B(2), C(2), D(2), E(1);
	A.next = &B;
	B.next = &C;
	C.next = &D;
	//D.next = &E;
	cout<<lPalin(&A);*/
	/*vector<int> A{34, 35, 27, 42, 5, 28, 39, 20, 28};
	auto result = prevSmaller(A);

	for(auto& a : result){
		cout<<a<<" ";
	}*/
	/*vector<int> A{1, 3, -1, -3, 5, 3, 6, 7};
	auto result = slidingMaximum(A, 3);
	for(auto &a : result){
		cout<<a<<" ";
	}*/

	/*string result = simplifyPath("/a/./b/../../c/");
	cout<<result;*/

	/*vector<string> A{"4", "13", "5", "/", "+"};
	cout<<evalRPN(A);*/
	/*vector<int> A{}, B{2,5,1,6};
	vector<int> result = solve(A, B);
	for(auto& a : result){
		cout<<a<<" ";
	}*/

    /*struct TreeNode l2_0{4, nullptr, nullptr}, l2_1{5, nullptr, nullptr}, l2_2{6, nullptr, nullptr},
	l1_0{2, &l2_0, &l2_1}, l1_1{3, nullptr, &l2_2},
	l0{1, &l1_0, &l1_1};

    TreeNode* result = solve(&l0);
    inOrderTraversal(&l0);*/

    /*TreeNode* root = newNode(8);
    root->left = newNode(3);
    root->right = newNode(10);
    root->left->left = newNode(1);
    root->left->right = newNode(6);
    root->right->right = newNode(14);
    root->right->right->left = newNode(13);
    root->left->right->left = newNode(4);
    root->left->right->right = newNode(7);
    vector<int> result = solveDiagonalTree(root);
	for(auto& a : result){
		cout<<a<<" ";
	}*/

	/*TreeNode A{1};
	A.left = new TreeNode{2};
	A.left->left = new TreeNode{4};
	A.left->right = new TreeNode{5};
	A.right = new TreeNode{3};
	A.right->left = new TreeNode{6};
	A.right->right = new TreeNode{7};
    vector<int> result = solve(&A, 5);
    for(auto& a : result){
    	cout<<a<<" ";
    }*/
	/*testSolveMaps();
}*/

