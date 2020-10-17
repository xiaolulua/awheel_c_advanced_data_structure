/*
 * main.cpp
 *
 *  Created on: 2020年1月29日
 *      Author: LuYonglei
 */

#include "BinarySearchTree.h"
#include <iostream>

using namespace std;

template<typename Element>
int compare(Element e1, Element e2) {
	//比较函数,相同返回0,e1<e2返回-1,e1>e2返回1
	return e1 == e2 ? 0 : (e1 < e2 ? -1 : 1);
}

template<typename Elemnet>
bool visitor(Elemnet e) {
	cout << e << " ";
	return false; //若返回true，则在遍历时会退出
}

int main(int argc, char **argv) {
	BinarySearchTree<double> a(compare);
	a.add(7);
	a.add(4);
	a.add(9);
	a.add(2);
	a.add(5);
	a.add(8);
	a.add(11);
	a.add(3);
	a.add(12);
	a.add(1);
	a.inorderTraversal(visitor);
	cout << endl;
//	cout << a.isComplete() << endl;
	a.remove(7);
//	a.clear();
	a.levelOrderTraversal(visitor);
	cout << endl;
	cout << a.contains(0) << endl;
}

