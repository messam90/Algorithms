/*
 * String.cpp
 *
 *  Created on: Jul 5, 2020
 *      Author: messam
 */
#include "Headers.hpp"

int stringisPalindrome(string A){
	int low = 0, high = A.length() - 1, ans = 1;
	while(low <= high){
		bool indexMod = false;
		if(!(A[low] >= 'a' && A[low] <= 'z') && !(A[low] >= 'A' && A[low] <= 'Z') && !(A[low] >= '0' && A[low] <= '9')){
			low++;
			indexMod = true;
		}
		if(!(A[high] >= 'a' && A[high] <= 'z') && !(A[high] >= 'A' && A[high] <= 'Z') && !(A[high] >= '0' && A[high] <= '9')){
			high--;
			indexMod = true;
		}
		if(!indexMod && tolower(A[low++]) != tolower(A[high--])){
			ans = 0;
			break;
		}
	}

	return ans;
}

string longestCommonPrefix(vector<string> &A){
	if(A.size() == 0){
		return "";
	}else if(A.size() == 1){
		return A[0];
	}else{
		sort(A.begin(), A.end());

		int leastLen = min(A[0].length(), A[A.size() - 1].length());
		int i = 0;
		while(i < leastLen && A[0][i] == A[A.size() - 1][i]){
			i++;
		}

		string common = A[0].substr(0, i);

		return common;
	}
}

int strStr(const string A, const string B){
	int AIndex = 0, BIndex = 0, possiblePos = -1;
	while(AIndex < A.size() && BIndex < B.size()){
		if(A[AIndex] == B[BIndex]){
			possiblePos = (possiblePos == -1) ? BIndex : possiblePos;
			AIndex++;
		}else if(A[AIndex] != B[BIndex] && possiblePos != -1){
			possiblePos = -1;
			AIndex = 0;
		}
		BIndex++;
	}

	return possiblePos;
}

int solve(string A) {
	int ans = 0;
	while(!stringisPalindrome(A)){
		A.erase(A.end() - 1);
		ans++;
	}
	return ans;
}

int lengthOfLastWord(const string A) {
	int chrCount = 0, prevChrCount = 0;
	for(int i = 0; i < A.length(); ++i){
		if(A[i] == ' '){
			prevChrCount = (chrCount == 0) ? prevChrCount : chrCount;
			chrCount = 0;
		}else if(A[i] != ' '){
			chrCount++;
		}
	}

	return (chrCount > 0) ? chrCount : prevChrCount;
}

int compareVersion(string A, string B) {
	unsigned long long num1 = 0, num2 = 0, i = 0, j = 0;
	while(i < A.length() || j < B.length()){
		while(i < A.length() && A[i] != '.'){
			num1 = num1 * 10 + A[i++] - '0';
		}

		while(j < B.length() && B[j] != '.'){
			num2 = num2 * 10 + B[j++] - '0';
		}

		if(num1 > num2) return 1;
		else if(num1 < num2) return -1;
		else if(num1 == num2){
			i++;
			j++;
			num1 = 0;
			num2 = 0;
		}
	}
	return 0;
}

int romanNumMap(char r);

int romanToInt(string A) {
	int result = 0;
	unsigned int i = 0;
	for(; i < A.length() - 1; ++i){
		int num1 = romanNumMap(A[i]);
		int num2 = romanNumMap(A[i + 1]);

		if(num1 >= num2){
			result += num1;
		}else{
			result += num2 - num1;
			i++;
		}
	}
	if(i < A.length()) result += romanNumMap(A[i]);

	return result;
}

void justifyText(string& line, unsigned int wordsInLine, unsigned int maxLineLen);

vector<string> fullJustify(vector<string> &A, int B) {
	string line;
	unsigned int wordsInLine = 0;
	bool justify = false;
	vector<string> result;

	for(unsigned int index = 0; index < A.size(); ++index){
		string tempLine;
		tempLine = A[index] + " ";
		if(line.length() + tempLine.length() <= (B + 1)){
			line += tempLine;
			wordsInLine++;
		}else{
			//can not fit more - start justifying
			line.erase(line.end() - 1); //remove last space
			justifyText(line, wordsInLine, B);
			result.push_back(line);

			line.clear();
			wordsInLine = 0;
			index--; //a word was discarded as it exceeded max length, re do it
		}
	}

	if(line.length() > 0){
		//last sentence
		line.erase(line.end() - 1); //remove last space
		//justifyText(line, wordsInLine, B);
		result.push_back(line);
	}

	return result;
}
