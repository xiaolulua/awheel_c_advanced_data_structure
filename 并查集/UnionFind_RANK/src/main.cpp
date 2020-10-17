/*
 * main.cpp
 *
 *  Created on: 2020年2月13日
 *      Author: LuYonglei
 */

#include<iostream>
#include"UnionFind.h"
using namespace std;


int main(int argc, char **argv) {
	UnionFind a(12);
	a.unionValue(0,1);
	a.unionValue(0,3);
	a.unionValue(0,4);
	a.unionValue(2,3);
	a.unionValue(2,5);
	a.unionValue(6,7);
	a.unionValue(8,10);
	a.unionValue(9,10);
	a.unionValue(9,11);
	cout<<"连接前:"<<!a.isSame(2,7)<<endl;
	a.unionValue(4,6);
	cout<<"连接后:"<<a.isSame(2,7)<<endl;
}



