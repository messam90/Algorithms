/*
Heaps_Maps.hpp
 *
 Created on: Jul 12, 2020
     Author: messam
 */

#ifndef HEAPS_MAPS_HEAPS_MAPS_HPP_
#define HEAPS_MAPS_HEAPS_MAPS_HPP_

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

struct cacheEntry {
	int key;
	int value;
	int timeStep;
	cacheEntry(int key, int value, int timeStep) : key(key), value(value), timeStep(timeStep){}
};

class LRUCache{
public:
	LRUCache(int);
	int get(int key);
	void set(int key, int value);
};

void testSolveMaps();
void testNchoc();
void testmergeKLists();
void testLRUCache();

#endif /* HEAPS_MAPS_HEAPS_MAPS_HPP_ */
