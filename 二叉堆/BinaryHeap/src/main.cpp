/*
 * main.cpp
 *
 *  Created on: 2020年2月3日
 *      Author: LuYonglei
 */

#include <iostream>
#include "BinaryHeap.h"
using namespace std;

template<typename Element>
int compare(Element e1, Element e2) {
	//比较函数,相同返回0,e1<e2返回-1,e1>e2返回1
	return e1 == e2 ? 0 : (e1 < e2 ? -1 : 1);
}

int main(int argc, char **argv) {
	BinaryHeap<int> a(compare);
	a.add(68);
	a.add(72);
	a.add(43);
	a.add(50);
	a.add(38);
	a.add(10);
	a.add(90);
	a.add(65);
	cout << a.repalce(70);
}

