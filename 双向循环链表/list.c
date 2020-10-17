/*
 * list.c
 *
 *  Created on: 2020年2月23日
 *      Author: LuYonglei
 */

#include "list.h"

void initListItem(ListItem *const listItem) {
	//初始化链表节点,表示节点还没有插入任何节点
	listItem->listHeader = NULL;
}

void initListHeader(ListHeader *const listHeader) {
	//初始化链表头节点
	//将链表索引指针指向链表尾节点
	listHeader->itemIndex = (ListItem*) (&(listHeader->listEnd));
	//将链表最后一个节点的辅助排序的值设置为最大
	listHeader->listEnd.itemValue = MAX_DELAY;
	//将最后一个节点的nextItem和previousItem均指向自身，表示链表为空
	listHeader->listEnd.nextItem = (ListItem*) (&(listHeader->listEnd));
	listHeader->listEnd.previousItem = (ListItem*) (&(listHeader->listEnd));
	//初始化链表节点计数器的值为0
	listHeader->numberOfListItems = (ListLength) 0;
}

void insertItemToListEnd(ListHeader *const listHeader,
		ListItem *const newListItem) {
	ListItem *const itemIndex = listHeader->itemIndex;
	newListItem->nextItem = itemIndex;
	newListItem->previousItem = itemIndex->previousItem;
	itemIndex->previousItem->nextItem = newListItem;
	itemIndex->previousItem = newListItem;
	//新插入的节点记录该节点所在的链表的头节点
	newListItem->listHeader = (void*) listHeader;
	//链表头节点计数器+1
	(listHeader->numberOfListItems)++;
}

void insertItemToList(ListHeader *const listHeader, ListItem *const newListItem) {
	ListItem *listItemIterator;
	//获取新插入节点的排序辅助值
	const TickType itemValueOfInsertion = newListItem->itemValue;
	//寻找节点要插入的位置
	if (itemValueOfInsertion == MAX_DELAY) {
		listItemIterator = listHeader->listEnd.previousItem;
	} else {
		//寻找节点要插入的位置
		listItemIterator = (ListItem*) (&(listHeader->listEnd));
		while (listItemIterator->nextItem->itemValue <= itemValueOfInsertion)
			listItemIterator = listItemIterator->nextItem;
	}
	//根据升序排列，将节点插入
	newListItem->nextItem = listItemIterator->nextItem;
	newListItem->nextItem->previousItem = newListItem;
	newListItem->previousItem = listItemIterator;
	listItemIterator->nextItem = newListItem;
	//新插入的节点记录该节点所在的链表的头节点
	newListItem->listHeader = (void*) listHeader;
	//链表头节点计数器+1
	(listHeader->numberOfListItems)++;
}

ListLength listRemove(ListItem *const itemToRemove) {
	//获取节点所在的链表
	ListHeader *listHeader = (ListHeader*) (itemToRemove->listHeader);
	//将节点从链表删除
	itemToRemove->nextItem->previousItem = itemToRemove->previousItem;
	itemToRemove->previousItem->nextItem = itemToRemove->nextItem;
	//调整链表头节点的索引指针
	if (listHeader->itemIndex == itemToRemove) {
		listHeader->itemIndex = itemToRemove->previousItem;
	}
	//初始化该节点所在的链表为空
	itemToRemove->listHeader = NULL;
	//链表节点计数器-1
	(listHeader->numberOfListItems)--;
	return listHeader->numberOfListItems;
}

void setOwnerOFListItem(ListItem *const listItem, void *const itemOwner) {
	//设置拥有该节点的内核对象(通常是TCB)
	listItem->itemOwner = itemOwner;
}
void* getOwnerOFListItem(ListItem *const listItem) {
	//获得拥有该节点的内核对象(通常是TCB)
	return listItem->itemOwner;
}
void setValueOFListItem(ListItem *const listItem, TickType const itemValue) {
	//设置链表节点的排序辅助值
	listItem->itemValue = itemValue;
}
TickType getValueOfListItem(ListItem *const listItem) {
	//获取链表节点的排序辅助值
	return listItem->itemValue;
}
ListItem* getNextItemOfListItem(ListItem *const listItem) {
	//获取节点的下一个节点
	return listItem->nextItem;
}

ListLength getLengthOfList(ListHeader *const listHeader) {
	//获取链表的节点数
	return listHeader->numberOfListItems;
}
TickType getItemValueOfListHeadEntry(ListHeader *const listHeader) {
	//获取链表头入口节点的排序辅助值
	return listHeader->listEnd.nextItem->itemValue;
}
ListItem* getHeadEntryItemOfList(ListHeader *const listHeader) {
	//获取链表头入口节点
	return listHeader->listEnd.nextItem;
}
void* getOwnerOfNextEntry(ListHeader *const listHeader) {
	//获取下一个入口节点的内核对象(通常是TCB)
	listHeader->itemIndex = listHeader->itemIndex->nextItem;
	if (((void*) (listHeader->itemIndex))
			== ((void*) (&(listHeader->listEnd)))) {
		listHeader->itemIndex = listHeader->itemIndex->nextItem;
	}
	return listHeader->itemIndex->itemOwner;
}
ListItem* getEndMarkerOfList(ListHeader *const listHeader) {
	//获取链表的最后一个节点
	return (ListItem*) (&(listHeader->listEnd));
}
