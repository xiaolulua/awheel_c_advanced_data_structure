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
//在原有基础上实现路径压缩
#ifndef SRC_UNIONFIND_H_
#define SRC_UNIONFIND_H_
#include <assert.h>
#include <stack>
#define DEFAULT_CAPACITY 10
using namespace std;

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

#if 0
	//递归实现路径压缩
	int findParent(int value) {
		assert(value < capacity_ && value >= 0);
		if (parents[value] != value) {
			parents[value] = findParent(parents[value]);
		}
		return parents[value];
	}
#elif 0
	//迭代实现路径压缩1
	int findParent(int value) {
		assert(value < capacity_ && value >= 0);
		stack<int> s;
		while (value != parents[value]) {
			s.push(value);
			value = parents[value];
		}
		int preIndex = 0;
		while (s.size() != 0) {
			preIndex = s.top();
			parents[preIndex] = value;
			s.pop();
		}
		return value;
	}

#else
	//迭代实现路径压缩2
	int findParent(int value) {
		assert(value < capacity_ && value >= 0);
		int begin = value;
		while (value != parents[value]) {
			value = parents[value];
		}
		int tmpBegin = 0;
		while (begin != value) {
			tmpBegin = parents[begin];
			parents[begin] = value;
			begin = tmpBegin;
		}
		return value;
	}

#endif

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
