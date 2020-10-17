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
	double arr[] = { 48, 3, 63, 6, 7, 21, 41, 60, 25, 82, 44, 90, 45, 23, 16 };
	for (int i = 0; i < sizeof(arr) / sizeof(double); i++)
		a.add(arr[i]);
//	a.inorderTraversal(visitor);
//	cout << endl;
//	cout << a.isComplete() << endl;
//	a.remove(21);
//	a.remove(44);
//	a.remove(48);
//	a.remove(45);
//	a.remove(26);
//	a.remove(3);
//	a.remove(60);
//	a.clear();
	a.postorderTraversal(visitor);
//	cout << endl;
//	a.levelOrderTraversal(visitor);
//	cout << endl;
//	cout<<a.contains(0)<<endl;
}

