/*
 * main.cpp
 *
 *  Created on: 2020年1月29日
 *      Author: LuYonglei
 */

#include "BinarySearchTree.h"
#include <iostream>
#include <time.h>

using namespace std;

template<typename Element>
int compare(Element e1, Element e2) {
	//比较函数,相同返回0,e1<e2返回-1,e1>e2返回1
	return e1 == e2 ? 0 : (e1 < e2 ? -1 : 1);
}

template<typename Elemnet>
bool visitor(Elemnet e) {
	cout << e << " ";
//	cout << endl;
	return false; //若返回true，则在遍历时会退出
}

int main(int argc, char **argv) {
	BinarySearchTree<double> a(compare);
	a.add(85);
	a.add(19);
	a.add(69);
	a.add(3);
	a.add(7);
//	a.add(99);
//	a.add(95);
//	a.add(2);
//	a.add(1);
//	a.add(70);
//	a.add(44);
//	a.add(58);
//	a.add(11);
//	a.add(21);
//	a.add(14);
//	a.add(93);
//	a.add(57);
//	a.add(4);
//	a.add(56);
//	a.remove(99);
//	a.remove(85);
//	a.remove(95);
//	clock_t start = clock();
//	for (int i = 0; i < 1000000; i++) {
//		a.add(i);
//	}
//	for (int i = 0; i < 1000000; i++) {
//		a.remove(i);
//	}
//	a.inorderTraversal(visitor);
//	clock_t end = clock();
//	cout << end - start << endl;
//	cout <<a.height()<< endl;
//	cout << a.isComplete() << endl;
//	a.remove(7);
//	a.clear();
	a.levelOrderTraversal(visitor);
	cout << endl;
	a.preorderTraversal(visitor);
	cout << endl;
	a.inorderTraversal(visitor);
	cout << endl;
	a.postorderTraversal(visitor);
	cout << endl;
//	cout << endl;
//	cout<<a.contains(0)<<endl;
}

