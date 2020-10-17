/*
 * BinaryHeap.h
 *  二叉堆(完全二叉堆)
 *  Created on: 2020年2月3日
 *      Author: LuYonglei
 */

#ifndef SRC_BINARYHEAP_H_
#define SRC_BINARYHEAP_H_
#include <assert.h>

const int DEFAULT_CAPACITY = 10; //默认容量
const float EXPAND = 1.5; //扩容系数

template<typename Element>
class BinaryHeap {
public:
	BinaryHeap(int (*cmp)(Element e1, Element e2)) :
			cmp_(cmp), capacity_(DEFAULT_CAPACITY), size_(0), elements(
					new Element[DEFAULT_CAPACITY]) {
		//构造函数
	}

	~BinaryHeap() {
		//析构函数
		clear();
	}

	int size() {
		//元素的数量
		return size_;
	}

	bool isEmpty() {
		//判断堆是否为空
		return size_ == 0;
	}

	void clear() {
		//清空堆
		size_ = 0;
		capacity_ = size_;
		delete[] elements;
		elements = nullptr;
	}

	void add(Element e) {
		//添加元素
		if (elements == nullptr) {
			elements = new Element[DEFAULT_CAPACITY];
			capacity_ = DEFAULT_CAPACITY;
		}
		if (size_ + 1 > capacity_) {
			capacity_ = int(capacity_ * EXPAND);
			Element *newElements = new Element[capacity_];
			for (int i = 0; i < size(); i++)
				newElements[i] = elements[i];
			delete[] elements;
			elements = newElements;
		}
		elements[size_++] = e;
		siftUp(size_ - 1);
	}

	Element get() {
		//获得堆顶元素f
		assert(size_ != 0);
		assert(elements != nullptr);
		return elements[0];
	}

	Element remove() {
		//删除堆顶元素，并返回堆顶元素
		assert(size_ != 0);
		assert(elements != nullptr);
		//将堆顶元素用最后一个元素替代
		Element top = elements[0];
		elements[0] = elements[--size_];
		siftDown(0);
		return top;
	}

	Element repalce(Element e) {
		//删除堆顶元素的同时插入一个新元素
		assert(size_ != 0);
		assert(elements != nullptr);
		Element top = elements[0];
		elements[0] = e;
		siftDown(0);
		return top;
	}

	void heapify(Element *e, int size) {
		//将原有堆清空，用数组来创建新的堆
		assert(size > 0);
		assert(e != nullptr);
		size_ = size;
		if (size_ > capacity_) {
			capacity_ = size_;
			delete[] elements;
			elements = new Element[capacity_];
		}
		for (int i = 0; i < size_; i++)
			elements[i] = e[i];
		if (size_ == 1)
			return;
		for (int i = size_ / 2 - 1; i >= 0; i--)
			siftDown(i);
	}

private:
	int (*cmp_)(Element, Element); //元素比较函数
	int capacity_; //默认容量
	int size_; //元素个数
	Element *elements; //存放元素的数组

	void siftUp(int index) {
		//让index位置的元素上滤
		Element element = elements[index];
		while (index > 0) {
			int parentIndex = (index - 1) / 2;
			Element parent = elements[parentIndex];
			if (cmp_(parent, element) >= 0)
				break;
			elements[index] = parent;
			index = parentIndex;
		}
		elements[index] = element;
	}

	void siftDown(int index) {
		//让index位置的元素下滤
		Element element = elements[index];
		//必须保证index位置是非叶子节点
		//当index小于第一个叶子节点的索引（第一个叶子节点的索引就是非叶子节点的数量）
		while (index < size_ / 2) {
			//index的节点有两种情况
			//1.只有左子节点
			//2.同时有左子节点和右子节点
			//默认为左子节点的索引
			int childIndex = 2 * index + 1;
			Element child = elements[childIndex];
			//右子节点索引
			int rightIndex = childIndex + 1;
			if (rightIndex < size_ && cmp_(elements[rightIndex], child) > 0) {
				//如果右子节点存在,选出左右子节点最大的
				childIndex = rightIndex;
				child = elements[childIndex];
			}
			if (cmp_(element, child) >= 0)
				break;
			elements[index] = child;
			index = childIndex;
		}
		elements[index] = element;
	}

};

#endif /* SRC_BINARYHEAP_H_ */
