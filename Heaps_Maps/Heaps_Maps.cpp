/*
 * Heaps_Maps.cpp
 *
 *  Created on: Jul 7, 2020
 *      Author: messam
 */
#include "Headers.hpp"
#include "Heaps_Maps.hpp"

vector<int> solveMaps(vector<int> A, vector<int> B) {
    int i = A.size() - 1;
    int j = B.size() - 1;
    int N = A.size();
    vector<int> result;
    multiset<int, greater<int>> arraysSum;

    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    while(i >= 0){
    	arraysSum.insert(A[i] + B[j]);
        j--;
        if(j < 0){
            j = N - 1;
            i--;
        }

        if(arraysSum.size() > N){
        	multiset<int, greater<int>>::iterator it = arraysSum.begin();
        	advance(it, N + 1);
            arraysSum.erase(it, arraysSum.end());
        }
    }

    set<int>::iterator it = arraysSum.begin();
    for(auto index = 0u; index < A.size(); index++){
        result.push_back(*it);
        ++it;
    }

    return result;
}

int nchoc(int A, vector<int> &B) {
	unsigned long long numChoc = 0;
	multiset<int, greater<int>> bags;

	//Fill the muti set descending order
	for(auto i = 0u; i < B.size(); ++i){
		bags.insert(B[i]);
	}

	for(auto i = 0u; i < A; ++i){
		int chocsInBag = *bags.begin();
		numChoc += chocsInBag;
		bags.erase(bags.begin());
		bags.insert(chocsInBag / 2);
	}

	unsigned long long temp = pow(10, 9) + 7;
	return (numChoc % temp);
}

ListNode* mergeKLists(vector<ListNode*> &A) {
	multiset<int> tempResult;
	ListNode* result;

	for(auto i =0u; i < A.size(); ++i){
		ListNode* currentNode = A[i];
		while(currentNode != nullptr){
			tempResult.insert(currentNode->val);
			currentNode = currentNode->next;
		}
	}

	multiset<int>::iterator it = tempResult.begin();
	ListNode* prevNode = new ListNode(*it);
	result = prevNode;
	++it;
	for(; it != tempResult.end(); ++it){
		ListNode* tempNode = new ListNode(*it);
		prevNode->next = tempNode;
		prevNode = tempNode;
	}
	return result;
}

map<int, cacheEntry> cache;
multimap<int, int> entries;
int cacheCapacity = 0, timeStep = 0;

LRUCache::LRUCache(int capacity) {
	cacheCapacity = capacity;
	timeStep = 0;
	cache.clear();
	entries.clear();
}

void updateAccessTime(int key, int timeStep, bool get){
	auto it = cache.find(key);
	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> entriesIt = entries.equal_range(it->second.timeStep);
	multimap<int, int>::iterator rangeIt = entriesIt.first;
	while(rangeIt != entriesIt.second){
		if(rangeIt->second == key){
			break;
		}
		++rangeIt;
	}
	entries.erase(rangeIt);
	entries.insert(pair<int, int>(timeStep, key));
	if(get){
		cacheEntry temp{it->second.key, it->second.value, timeStep};
		cache.erase(it);
		cache.insert(pair<int, cacheEntry>(temp.key, temp));
	}
}

int LRUCache::get(int key) {
	map<int, cacheEntry>::iterator cacheIt = cache.find(key);
	if(cacheIt != cache.end()){
		updateAccessTime(key, timeStep++, true);
		return cacheIt->second.value;
	}
	return -1;
}

void LRUCache::set(int key, int value) {
	map<int, cacheEntry>::iterator it = cache.find(key);
	if(it != cache.end()){
		updateAccessTime(key, timeStep, false);
		auto it = cache.find(key);
		cache.erase(it);
	}else{
		if(cache.size() == cacheCapacity){
			multimap<int, int>::iterator entryIt = entries.begin();
			map<int, cacheEntry>::iterator it = cache.find(entryIt->second);
			entries.erase(entryIt);
			cache.erase(it);
		}
		entries.insert(pair<int, int>(timeStep, key));
	}
	cache.insert(pair<int, cacheEntry>(key, cacheEntry{key, value, timeStep}));
	timeStep++;
}



void testLRUCache(){
	char array[1000];
	cin.getline(array, 1000);
	string s(array);
	stringstream ss(s);
	int num, numOps;
	char ch;
	ss>>numOps;//num operations
	ss>>num; //capcaity
	LRUCache c(num);
	for(auto i =0u; i < numOps; ++i){
		char op;
		ss>>op;
		switch(op){
		case 'S':{
			int x, y;
			ss>>x; //first arg
			ss>>y; //second arg
			c.set(x, y);
		}
		break;
		case 'G':{
			int x;
			ss>>x; //arg
			cout<<c.get(x)<<" ";
			cout.flush();
		}
		}
	}
}

///////////////////////////////////////////////////////
void testmergeKLists(){
	ListNode A{1}, B{4}, C{3};
	A.next = new ListNode(10);
	A.next->next = new ListNode(20);
	B.next = new ListNode(11);
	B.next->next = new ListNode(13);
	C.next = new ListNode(8);
	C.next->next = new ListNode(9);
	vector<ListNode*> ListNodes{&A, &B, &C};
	ListNode* result = mergeKLists(ListNodes);

	while(result){
		cout<<result->val<<" ";
		result = result->next;
	}
}

void testSolveMaps(){
	vector<int> A{1}, B{1};

	vector<int> result = solveMaps(A, B);

	for(auto a: result){
		cout<<a<<" ";
	}
}

void testNchoc(){
	vector<int> A{2147483647, 2000000014, 2147483647 };
	cout<<nchoc(10, A);
}

