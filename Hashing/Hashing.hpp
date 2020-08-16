/*
 * Hashing.hpp
 *
 *  Created on: Jul 15, 2020
 *      Author: messam
 */

#ifndef HASHING_HASHING_HPP_
#define HASHING_HASHING_HPP_

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

void testColorful();
void testLszero();
void testtwoSum();
void testfourSum();
void testisValidSudoku();
void testdiffPossible();
void testanagrams();
void test_equal();
void test_copyRandomList();
void test_lengthOfLongestSubstring();
void test_minWindow();
void test_fractionToDecimal();
void test_maxPoints();
void test_findSubstring();

#endif /* HASHING_HASHING_HPP_ */
