/*
 * main.cpp
 *
 *  Created on: 2020年3月9日
 *      Author: LuYonglei
 */
#include "SkipList.h"

#include <stdio.h>


int comp(int left, int right) {
	return (left > right ? 1 : (left < right ? -1 : 0));
}

int main(int argc, char **argv) {
	SkipList<int, int> a(comp);

	a.put(1,2);
	a.put(2,3);
	a.put(2,7);
	a.put(-1,4);
	a.put(3,5);
	a.put(0,-1);
	a.put(3,5);



	a.put(9,72);
	a.put(10,5);
	a.put(-12,56);
	a.put(0,12);
	a.put(3,-1);
//	a.remove(3);
	a.put(89,90);
	a.remove(-12);
//	printf("%d",a.get(3));
	a.show();
}

