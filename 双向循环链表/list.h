/*
 * list.h
 *
 *  Created on: 2020年2月23日
 *      Author: LuYonglei
 */

#ifndef SRC_LIST_H_
#define SRC_LIST_H_
#include <stddef.h>
#include <stdint.h>

typedef unsigned long ListLength;

#if 1
typedef uint32_t TickType;
#define MAX_DELAY (TickType) 0xffffffffUL
#else
typedef uint16_t TickType;
#define MAX_DELAY (TickType) 0xffff
#endif

//链表节点
typedef struct list_item {
	TickType itemValue; //用于帮助节点做升序排列
	struct list_item *nextItem; //指向链表的下一个节点
	struct list_item *previousItem; //指向链表的前一个节点
	void *itemOwner; //指向拥有该节点的内核对象(通常是TCB)
	void *listHeader; //指向该节点所在的链表
} ListItem;

//链表尾节点
typedef struct mini_list_item {
	TickType itemValue; //用于帮助节点做升序排列
	struct list_item *nextItem; //指向链表的下一个节点
	struct list_item *previousItem; //指向链表的前一个节点
} ListEnd;

//链表头节点
typedef struct list_header {
	ListLength numberOfListItems; //计算链表节点的数量
	ListItem *itemIndex; //链表节点索引指针
	ListEnd listEnd; //链表最后一个节点
} ListHeader;

void initListItem(ListItem *const listItem); //初始化链表节点
void initListHeader(ListHeader *const listHeader); //初始化链表头节点
void insertItemToListEnd(ListHeader *const listHeader,
		ListItem *const newListItem); //把一个链表节点插入到链表的尾部
void insertItemToList(ListHeader *const listHeader, ListItem *const newListItem); //把一个节点按照升序排列插入到链表，若itemValue相同，则新节点在旧节点的后面
ListLength listRemove(ListItem *const itemToRemove); //把一个节点从链表中删除，返回链表中存在的节点的个数

//小函数，也可以用宏定义实现
void setOwnerOFListItem(ListItem *const listItem, void *const itemOwner); //设置拥有该节点的内核对象(通常是TCB)
void* getOwnerOFListItem(ListItem *const listItem); //获得拥有该节点的内核对象(通常是TCB)
void setValueOFListItem(ListItem *const listItem, TickType const itemValue); //设置链表节点的排序辅助值
TickType getValueOfListItem(ListItem *const listItem); //获取链表节点的排序辅助值
ListItem* getNextItemOfListItem(ListItem *const listItem); //获取节点的下一个节点

//ListHeadEntry就是listEnd的nextItem
ListLength getLengthOfList(ListHeader *const listHeader); //获取链表的节点数
TickType getItemValueOfListHeadEntry(ListHeader *const listHeader); //获取链表头入口节点的排序辅助值
ListItem* getHeadEntryItemOfList(ListHeader *const listHeader); //获取链表头入口节点
void* getOwnerOfNextEntry(ListHeader *const listHeader); //获取下一个入口节点的内核对象(通常是TCB)
ListItem* getEndMarkerOfList(ListHeader *const listHeader); //获取链表的最后一个节点

#endif /* SRC_LIST_H_ */
