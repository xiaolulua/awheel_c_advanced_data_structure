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
//本文件基于rank实现优化
//在原有基础上实现路径减半
#ifndef SRC_UNIONFIND_H_
#define SRC_UNIONFIND_H_
#include <assert.h>
#define DEFAULT_CAPACITY 10

class UnionFind {
public:
	UnionFind(int capacity) :
			capacity_(capacity > 0 ? capacity : DEFAULT_CAPACITY), parents(
					new int[capacity > 0 ? capacity : DEFAULT_CAPACITY]), ranks(
					new int[capacity > 0 ? capacity : DEFAULT_CAPACITY]) {
		//初始化构造函数
		for (int i = 0; i < capacity_; i++) {
			parents[i] = i;
			ranks[i] = 1; //以i为根节点的树的高度
		}
	}

	~UnionFind() {
		//析构函数
		delete[] parents;
		delete[] ranks;
	}

	int findParent(int value) {
		assert(value < capacity_ && value >= 0);
		while (value != parents[value]) {
			parents[value] = parents[parents[value]];
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
		if (ranks[leftParent] < ranks[rightParent]) {
			parents[leftParent] = rightParent;
		} else if (ranks[rightParent] > ranks[leftParent]) {
			parents[rightParent] = leftParent;
		} else {
			parents[leftParent] = rightParent;
			ranks[rightParent] += 1;
		}
	}

	bool isSame(int leftValue, int rightValue) {
		return findParent(leftValue) == findParent(rightValue);
	}

private:
	int capacity_;
	int *parents;
	int *ranks;
};

#endif /* SRC_UNIONFIND_H_ */
