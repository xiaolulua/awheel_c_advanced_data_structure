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
	a.add(55);
	a.add(87);
	a.add(56);
	a.add(74);
	a.add(96);
	a.add(22);
	a.add(62);
	a.add(20);
	a.add(70);
	a.add(68);
	a.add(90);
	a.add(50);
	a.remove(55);
	a.remove(87);
	a.remove(56);
//	a.inorderTraversal(visitor);
//	cout << endl;
//	cout << a.isComplete() << endl;
//	a.remove(55);
//	a.clear();
	a.levelOrderTraversal(visitor);
	cout << endl;
//	cout<<a.contains(0)<<endl;
}

