/*
 * UnionFind.h
 * 有两种实现方式,QuickFind和QuickUnion
 * QuickFind:
 *          查找O(1)
 *          合并O(n)
 * QuickUnion：(建议使用)
 *          查找O(logn)可优化至O(a(n)),a(n)<5
 *          合并O(logn)可优化至O(a(n)),a(n)<5
 *  Created on: 2020年2月13日
 *      Author: LuYonglei
 */

//由于QuickFind平均时间复杂度不理想，所以本文件只用QuickUnion来实现
//本文件基于size实现优化
//此优化也可能会存在树不平衡的问题
#ifndef SRC_UNIONFIND_H_
#define SRC_UNIONFIND_H_
#include <assert.h>
#define DEFAULT_CAPACITY 10

class UnionFind {
public:
	UnionFind(int capacity) :
			capacity_(capacity > 0 ? capacity : DEFAULT_CAPACITY), parents(
					new int[capacity > 0 ? capacity : DEFAULT_CAPACITY]), sizes(
					new int[capacity > 0 ? capacity : DEFAULT_CAPACITY]) {
		//初始化构造函数
		for (int i = 0; i < capacity_; i++) {
			parents[i] = i;
			sizes[i] = 1; //以i为根节点的树的元素个数
		}
	}

	~UnionFind() {
		//析构函数
		delete[] parents;
		delete[] sizes;
	}

	int findParent(int value) {
		assert(value < capacity_ && value >= 0);
		while (value != parents[value]) {
			value = parents[value];
		}
		return value;
	}

	void unionValue(int leftValue, int rightValue) {
		//统一实现左边跟随右边
		int leftParent = findParent(leftValue);
		int rightParent = findParent(rightValue);
		if (leftParent == rightParent)
			return;
		if (sizes[leftParent] < sizes[rightParent]) {
			parents[leftParent] = rightParent;
			sizes[rightParent] += sizes[leftParent];
		} else {
			parents[rightParent] = leftParent;
			sizes[leftParent] += sizes[rightParent];
		}
	}

	bool isSame(int leftValue, int rightValue) {
		return findParent(leftValue) == findParent(rightValue);
	}

private:
	int capacity_;
	int *parents;
	int *sizes;
};

#endif /* SRC_UNIONFIND_H_ */
