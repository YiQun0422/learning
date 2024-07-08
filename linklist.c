#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义链表结构体
typedef struct LNode_ {
	int data;
	struct LNode* next;
}LNode, * LinkList;

// 把数组转为链表(尾插法)
LinkList array_from_LinkList(int* array, int array_length) {
	LinkList head = malloc(sizeof(LNode));
	head->next = NULL;
	LNode* p = head; // 尾指针指向头结点(带头结点的链表)
	for (int i = 0; i < array_length; i++)
	{
		LNode* node = malloc(sizeof(LNode));
		node->data = array[i];
		//node->next=NULL;
		p->next = node;
		p = node;
	}
	p->next = NULL;
	return head;
}

// 释放结构体空间
void free_LinkList(LinkList list) {
	while (list) {
		LNode* p = list->next;
		free(list);
		list = p;
	}
}

// 返回链表长度
int LinkList_get_length(LinkList L) {
	int length = 0;
	LNode* p = L->next; // 带头结点 从第二个元素开始算
	while (p)
	{
		p = p->next;
		length++;
	}
	return length;
}

// 打印链表每个值
void LinkList_print(LinkList L) {
	LNode* p = L->next; // 带头结点 从第二个元素开始算
	for (int i = 0; i < LinkList_get_length(L); i++)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

// 交换两个链表每个的值
void LinkList_swap(LinkList LA, LinkList LB) {
	LNode* pa = LA->next;
	LNode* pb = LB->next;
	while (pa && pb)
	{
		int temp = pa->data;
		pa->data = pb->data;
		pb->data = temp;
		pa = pa->next;
		pb = pb->next;
	}
}

// 合并两个有序链表
struct ListNode* mergeTwoLists(LinkList list1, LinkList list2) {
	if (list1 == NULL)
	{
		return list2;
	}
	else if (list2 == NULL)
	{
		return list1;
	}
	else if (list1->data < list2->data)
	{
		list1->next = mergeTwoLists(list1->next, list2);
		return list1;
	}
	else {
		list2->next = mergeTwoLists(list1, list2->next);
		return list2;
	}
}

// 已知两个链表A和B分别表示两个元素递增排列的集合 求出A与B的交集并存放在A链表中
LNode* FindSame_A(LNode* la, LNode* lb)
{
	LNode* p = la;
	LNode* pa = la->next;
	LNode* pb = lb->next;
	while (pa)
	{
		bool index = true;
		while (pb)
		{
			if (pb->data != pa->data)
			{
				index = false;
				pb = pb->next;
				continue;
			}
			else
				pb = lb->next;
			index = true;
			break;
		}
		if (index)
		{
			p = pa;
			pa = pa->next;
		}
		else
		{
			pa = pa->next;
			p->next = pa;
			pb = lb->next;
		}
	}
	return p;
}

// 通过一趟遍历确定长度为 n的单链表中值最大的结点
int BiggestNode(LNode* la)
{
	LNode* index = la->next;
	LNode* temp = index->next;
	while (index->next)
	{
		if (temp->data > index->data)
		{
			index = temp;
		}
		temp = temp->next;
	}
	return index->data;
}

// 将链表中所有结点的链接方向“原地”逆转(头插法）
LNode* Reversal(LNode* list)
{
	LNode* p = list->next;
	list->next = NULL;
	while (p)
	{
		LNode* q = p->next;
		p->next = list->next;
		list->next = p;
		p = q;
	}
	return list;
}

// 删除递增有序链表中值大于mink且小于maxk的所有元素
LNode* Delete(LNode* list, int mink, int maxk)
{
	LNode* pa = list->next;
	LNode* pb = pa;
	LNode* p = list;
	while (pa && pa->data < mink)
	{
		p = pa;
		pa = pa->next;
	}
	while (pb && pb->data < maxk)
	{
		pb = pb->next;
	}
	p->next = pb;

	return list;
}

// 删除线性表中所有值为 item的数据元素
int* Delete_item(int* array, int item)
{
	int sum = 0;
	for (int i = 0; i < 8; i++)
	{
		if (array[i] != item)
		{
			array[sum] = array[i];
			sum += 1;
		}
	}
	return array;
}

int main()
{
	int arrA[5] = { 1,3,3,5,9 };
	int arrB[5] = { 0,1,5,9,11 };

	LinkList la = array_from_LinkList(arrA, 5);
	LinkList lb = array_from_LinkList(arrB, 5);

	printf("LinkList LA length is: %d\n", LinkList_get_length(la));
	LinkList_print(la);
	printf("LinkList LB length is: %d\n", LinkList_get_length(lb));
	LinkList_print(lb);

	printf("\nLinkList swap: \n\n");
	LinkList_swap(la, lb);

	printf("LinkList LA length is: %d\n", LinkList_get_length(la));
	LinkList_print(la);
	printf("LinkList LB length is: %d\n", LinkList_get_length(lb));
	LinkList_print(lb);

	printf("交集元素la is: ");
	FindSame_A(la, lb);
	LinkList_print(la);
	printf("\n");

	printf("la中最大元素是: %d\n", BiggestNode(la));
	printf("\n");

	printf("原地逆转后的la是: ");
	Reversal(la);
	LinkList_print(la);
	printf("\n");

	printf("删除lb中2 6之间的元素后链表为：");
	Delete(lb, 2, 6);
	LinkList_print(lb);
	printf("\n");


	int arrC[8] = { 1,2,2,3,3,4,5,7 };
	printf("数组arrC中的元素为：");
	for (int i = 0; i < sizeof(arrC) / sizeof(arrC[0]); i++)
	{
		printf("%d ", arrC[i]);
	}
	printf("\n\n");

	printf("删除arrC中所有值为3元素后数组为：");
	Delete_item(arrC, 3);
	for (int i = 0; i < (sizeof(arrC) / sizeof(arrC[0])-2); i++)
	{
		printf("%d ", arrC[i]);
	}
	printf("\n");

	free_LinkList(la);
	free_LinkList(lb);

	return 0;
}
