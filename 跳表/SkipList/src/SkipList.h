/*
 * SkipList.h
 *
 *  Created on: 2020年3月9日
 *      Author: LuYonglei
 */

#ifndef SRC_SKIPLIST_H_
#define SRC_SKIPLIST_H_
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LEVEL 5

template<typename K, typename V>
class SkipList {
public:
	SkipList(int (*cmp_)(K leftKey, K rightKey)) :
			size_(0), maxLevel(MAX_LEVEL), cmp(cmp_), first(maxLevel, 0, 0) {

	}
	~SkipList() {
		//析构函数
		while ((first.nexts)[0] != nullptr) {
			NODE *temp = (first.nexts)[0];
			(first.nexts)[0] = (((first.nexts)[0])->nexts)[0];
			delete temp;
		}
	}
	int size() {
		//返回跳表元素个数
		return size_;
	}

	void show() {
		//分层显示跳表中的数据
		for (int i = maxLevel - 1; i >= 0; i--) {
			NODE *temp = (first.nexts)[i];
			if (temp == nullptr)
				continue;
			while (temp != nullptr) {
				printf("%3d:%-3d ", temp->key,temp->value);
				temp = (temp->nexts)[i];
			}
			printf("\n");
		}
		printf("\n");
		NODE *temp = (first.nexts)[0];
		while (temp != nullptr) {
			printf("%7d ", temp->level);
			temp = (temp->nexts)[0];
		}
	}
	bool isEmpty() {
		//判断跳表是否为空
		return size_ == 0;
	}

	V put(K k, V v) {
		//返回k原先对应的value
		int i;
		int ret;
		NODE *Header = &first;
		NODE *NextNode;
		V tempValue; //保存k之前的value值
		NODE **previousNode = new Node*[maxLevel] { nullptr }; //记录之前的节点

		for (i = maxLevel - 1; i >= 0; i--) {
			ret = -1;
			//1. 从首节点开始查找
			NextNode = (Header->nexts)[i];
			while (NextNode != nullptr && ((ret = cmp(k, NextNode->key)) > 0)) {
				//如果要查找的值大于下一个节点的key,就继续向下一个节点搜索
				Header = NextNode;
				NextNode = (Header->nexts)[i];
			}
			if (ret == 0) { //此处找到k对应的节点
				tempValue = NextNode->value;
				NextNode->value = v;
				delete[] previousNode;
				return tempValue;
			}
			//此处记录之前的节点的node
			previousNode[i] = Header;
		}
		//没有找到k对应的节点,创建新节点
		int newLevel = 1;
		while ((rand() % 11) <= 5 && newLevel < maxLevel) {
			newLevel++;
		}
		NODE *newNode = new NODE(newLevel, k, v);
		for (i = newLevel - 1; i >= 0; i--) {
			NODE *previousNodeNext = (previousNode[i]->nexts)[i];
			(newNode->nexts)[i] = previousNodeNext;
			(previousNode[i]->nexts)[i] = newNode;
		}
		delete[] previousNode;
		size_++;
		return 0;
	}

	V get(K k) {
		//获取k对应的value
		int i;
		int ret;
		NODE *Header = &first;
		NODE *NextNode;

		for (i = maxLevel - 1; i >= 0; i--) {
			ret = -1;
			//1. 从首节点开始查找
			NextNode = (Header->nexts)[i];
			while (NextNode != nullptr && (ret = cmp(k, NextNode->key)) > 0) {
				//如果要查找的值大于下一个节点的key,就继续向下一个节点搜索
				Header = NextNode;
				NextNode = (Header->nexts)[i];
			}
			if (ret == 0) //此处找到k对应的节点
				return NextNode->value;
		}
		//没有找到k对应的节点
		return 0;
	}

	V remove(K k) {
		//删除k对应的value
		int i;
		int ret;
		NODE *Header = &first;
		NODE *NextNode;
		NODE *toBeDeleted;
		V tempValue; //保存k之前的value值
		NODE **previousNode = new Node*[maxLevel] { nullptr }; //记录之前的节点
		bool exist = false; //判断要删除的节点是否存在

		for (i = maxLevel - 1; i >= 0; i--) {
			ret = -1;
			//1. 从首节点开始查找
			NextNode = (Header->nexts)[i];
			while (NextNode != nullptr && ((ret = cmp(k, NextNode->key)) > 0)) {
				//如果要查找的值大于下一个节点的key,就继续向下一个节点搜索
				Header = NextNode;
				NextNode = (Header->nexts)[i];
			}
			if (ret == 0) { //此处找到k对应的节点
				exist = true;
				toBeDeleted = NextNode;
			}
			//此处记录之前的节点的node
			previousNode[i] = Header;
		}
		if (exist) {
			//如果要删除的key存在
			for (i = toBeDeleted->level - 1; i >= 0; i--) {
				(previousNode[i]->nexts)[i] = (toBeDeleted->nexts)[i];
			}
			tempValue = toBeDeleted->value;
			delete toBeDeleted;
			delete[] previousNode;
			size_--;
			return tempValue;
		}
		delete[] previousNode;
		return 0;
	}

private:
	int size_; //跳表中存储的元素个数
	int maxLevel; //有效层数的最高层数
	typedef struct Node {
		int level; //当前节点层数
		K key;
		V value;
		Node **nexts;

		Node(int level_, K k, V v) :
				level(level_), key(k), value(v), nexts(
						level_ > 0 ? new Node*[level_] { nullptr } : nullptr) {

		}
		~Node() {
			assert(nexts != nullptr);
			delete[] nexts;
		}
	} NODE;
	int (*cmp)(K leftKey, K rightKey);
	NODE first;
};

#endif /* SRC_SKIPLIST_H_ */
