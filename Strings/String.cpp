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

string countAndSay(int A) {
	vector<string> s{"1", "11", "21"};
	unordered_map<int, string> map{pair<int, string>(1, "11"), pair<int, string>(11, "21"), pair<int, string>(21, "1211")};

	if(A < 4){
		return s[A - 1];
	}


}

int AmazingSubStrings(string A) {
	int count = 0;
	unordered_set<char> temp;

	for(auto i = 0u; i < A.length(); ++i){
		if(A[i] == 'a' || A[i] == 'e' || A[i] == 'i' || A[i] =='o' || A[i] == 'u' ||
				A[i] == 'A' || A[i] == 'E' || A[i] == 'I' || A[i] =='O' || A[i] == 'U'){
			count += A.length() - i;
			if(temp.find(A[i]) != temp.end()){
				count--;
			}else{
				temp.insert(A[i]);
			}
		}
	}

	return count;
}

string ReverseString(string A) {
	string result, temp;

	for(auto i = 0u; i < A.length(); ++i){
		if(A[i] != ' '){
			temp += A[i];
		}else if(temp.length() > 0){
			result.insert(0, temp);
			result.insert(0, " ");
			temp.clear();
		}
	}

	result.insert(0, temp);
	if(result[0] == ' '){
		result.erase(0, 1);
	}
	return result;
}

int atoi_1(const string A) {
	int result = 0, end_of_num = 0, start_of_num = 0, i = 0, neg_index = -1, prev_result = 0;

	while(A[i] < '0' || A[i] > '9'){
		if(A[i] == '-'){
			neg_index = i;
		}
		start_of_num++;
		i++;
	}

	if((neg_index != -1 && neg_index != start_of_num - 1) || (start_of_num > 0 && (A[start_of_num - 1] != '-' && A[start_of_num - 1] != '+'))){
		return 0;
	}

	if(start_of_num > A.length() - 1){
		return 0;
	}

	i = start_of_num;
	end_of_num = i;
	while((A[i] >= '0' && A[i] <= '9') && i < A.length()){
		end_of_num++;
		i++;
	}

	int po = 0;
	for(auto i = end_of_num - 1; i >= start_of_num; --i){
		prev_result = result;
		result += (A[i] - '0') * pow(10, po++);
		if(result < prev_result){
			if(neg_index != -1 && neg_index == start_of_num - 1){
				return numeric_limits<int>::min();
			}else{
				return numeric_limits<int>::max();
			}
		}
	}

	return (neg_index != -1 && neg_index == start_of_num - 1) ? -1 * result : result;
}

int isNumber(const string A) {
	string B(A);
	for(auto i = 0u; i < B.length(); ++i){
		if(B[i] == '.'){
			if((i > 0 && (!isdigit(B[i - 1]) && B[i - 1] != 'e')) ||
					(i < B.length() - 1 && !isdigit(B[i + 1]) || i == B.length())){
				return 0;
			}
		}else if(A[i] == 'e'){
			if(i == 0 || (i > 0 && !isdigit(B[i - 1]))
					|| (i < B.length() - 1 && !(isdigit(B[i + 1]) || B[i + 1] == '.' || B[i + 1] == '+' || B[i + 1] == '-')
							|| i == B.length())){
				return 0;
			}
		}else if(B[i] == '-' || B[i] == '+'){
			if((i != 0 && B[i - 1] != 'e') || B.length() == 1){
				return 0;
			}
		}else if(B[i] < '0' || B[i] > '9'){
			return 0;
		}
	}

	return 1;
}

vector<string> restoreIpAddresses(string A) {
	int missing_digits = 12 - A.length();
	vector<string> result;

	if(missing_digits == 0){
		A.insert(9, ".");
		A.insert(6, ".");
		A.insert(3, ".");
		return vector<string>{A};
	}

	while(missing_digits >= 0){
		int dot_id = 9 - missing_digits;
		string temp_result(A);
		temp_result.insert(dot_id, ".");
		temp_result.insert(6, ".");
		temp_result.insert(3, ".");
		result.push_back(temp_result);
		missing_digits--;
	}


	return result;
}

string addBinary(string A, string B) {
	int i = A.length() - 1, j = B.length() - 1, carry_over = 0;
	string result;

	while(i >= 0 && j >= 0){
		int sum = (A[i--] - '0') + (B[j--] - '0') + carry_over;
		carry_over = (sum > 1) ? 1 : 0;

		result.insert(0, (sum == 1 || sum == 3) ? "1" : "0");
	}

	while(i >= 0){
		int sum = (A[i--] - '0') + carry_over;
		carry_over = (sum > 1) ? 1 : 0;

		result.insert(0, (sum == 1 || sum == 3) ? "1" : "0");
	}

	while(j >= 0){
		int sum = (B[j--] - '0') + carry_over;
		carry_over = (sum > 1) ? 1 : 0;

		result.insert(0, (sum == 1 || sum == 3) ? "1" : "0");
	}

	if(carry_over != 0){
		result.insert(0, "1");
	}

	return result;
}

bool isPalindrome(string S){
	int i = 0, j = S.length() - 1;
	while(i < j){
		if(S[i] != S[j]){
			return false;
		}
		i++;
		j--;
	}
	return true;
}

enum class state_t{INCREMENT_I, DECREMENT_J, NEXT};

string longestPalindrome(string A) {
	int i = 0, j = A.length() - 1, longest_length = 0, min_index = (int)~0;
	string result;


	while(i < A.length()){
		string temp(A.substr(i, j - i + 1));

		if(isPalindrome(temp)){
			if(temp.length() > longest_length){
				min_index = i;
				longest_length = temp.length();
				result = temp;
			}else if(temp.length() == longest_length && i < min_index){
				min_index = i;
				result = temp;
			}
		}

		j--;
		if(j < i){
			i++;
			j = A.length() - 1;
		}
	}

	return result;
}

int power(string A) {
	if(A == "1" || A == "0"){
		return 0;
	}

	while(A != "1"){
		unsigned int i = 0;
		string temp{A[A.length() - 1]}, temp_result;
		if(atoi(temp.c_str()) % 2 != 0){
			return 0;
		}

		while(i < A.length()){
			temp = A[i];
			int num = atoi(temp.c_str());

			while(num % 2 != 0){
				temp += A[++i];
				num = atoi(temp.c_str());
			}

			stringstream ss;
			ss<< num / 2;
			string number(ss.str());

			while(number.length() < temp.length() && temp_result.length() > 0){
				number.insert(0, "0");
			}
			temp_result += number;
			++i;
		}

		A = temp_result;
		temp_result.clear();
	}

	return 1;
}

string multiply(string A, string B) {
	vector<string> temp_results;
	string result;

	for(int i = B.length() - 1; i >= 0; --i){
		string temp;
		int carry = 0;

		while(temp.length() < temp_results.size()){
			temp += "0";
		}

		for(int j = A.length() - 1; j >= 0; --j){
			stringstream ss;
			int sum = atoi(string{B[i]}.c_str()) * atoi(string{A[j]}.c_str()) + carry;
			ss<<sum;
			temp.insert(0, ss.str());

			if(ss.str().length() > 1){
				carry = temp[0];
				temp.erase(0);
			}else{
				carry = 0;
			}
		}

		if(carry){
			temp.insert(0, string(1, (char)(carry + '0')));
		}

		while(temp.length() < B.length() + 1){
			temp.insert(0, "0");
		}

		temp_results.push_back(temp);
	}

	int carry_over = 0;
	for(int i = temp_results[0].length() - 1; i >= 0; --i){
		int sum = 0;
		for(auto j = 0u; j < temp_results.size(); ++j){
			sum += atoi(string{temp_results[j][i]}.c_str());
		}

		sum += carry_over;

		if(sum > 9){
			carry_over = sum / 10;
		}

		stringstream ss;
		ss<<sum % 10;
		result.insert(0, ss.str());
	}

	if(carry_over){
		stringstream ss;
		ss<<carry_over;
		result.insert(0, ss.str());
	}

	return result;
}


////////////////////////////////////////////////////////
void test_multiply(){
	cout<<multiply("96", "28");
}

void test_power(){
	cout<<power("18446744073709551616");
}

void test_longestPalindrome(){
	string S{"a"};
	cout<<longestPalindrome(S);
}

void test_addBinary(){
	cout<<addBinary("100", "111");
}

void test_restoreIpAddresses(){
	auto result = restoreIpAddresses("2552551135");
	for(auto& a: result){
		cout<<a<<" ";
	}
}
void test_isNumber(){
	cout<<isNumber("0.1");
}

void test_atoi(){
	cout<<atoi_1("M7");
}

void test_ReverseString(){
	cout<<ReverseString(" the sky is  blue ");
}
void test_AmazinSubStrings(){
	cout<<AmazingSubStrings("AAB");
}
