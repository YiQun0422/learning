#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode_ {
	int data;
	struct LNode* next;
}LNode,*LinkList;

LinkList array_from_LinkList(int* array, int array_length) {
	LinkList head = malloc(sizeof(LNode));
	head->next = NULL;
	LNode* p = head;//尾指针指向头结点(带头结点的链表)
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

int LinkList_get_length(LinkList L) {
	int length = 0;
	LNode* p = L->next;//带头结点 从第二个元素开始算
	while (p)
	{
		p = p->next;
		length++;
	}
	return length;
}

void LinkList_print(LinkList L) {
	LNode* p = L->next;//带头结点 从第二个元素开始算
	for (int i = 0; i < LinkList_get_length(L); i++)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

//已知两个链表A和B分别表示两个集合，其元素递增排列。请设计一个算法求出A与B的交集，并存放在A链表中
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

//设计一个算法，通过一趟遍历确定长度为 n的单链表中值最大的结点
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

//设计一个算法，将链表中所有结点的链接方向“原地”逆转(头插法）
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

//设计一个算法，删除递增有序链表中值大于mink且小于maxk的所有元素
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

//设计一个算法删除线性表中所有值为 item的数据元素
int* Delete_item(int* array, int item)
{
	int index = 3;
	int sum = 0;
	for (int i = 0; i < 8; i++)
	{
		if (array[i] != index)
		{
			array[sum] = array[i];
			sum += 1;
		}
	}
	return array[8-sum];
}

int main()
{
	int arrA[5] = { 0,1,2,5,12};
	int arrB[5] = { 0,1,3,5,12 };
	int arrC[8] = { 1,2,2,3,3,4,5,7 };
	LinkList la = array_from_LinkList(arrA, 5);
	LinkList lb = array_from_LinkList(arrB, 5);
	printf("LinkList la is: ");
	LinkList_print(la);
	printf("LinkList lb is: ");
	LinkList_print(lb);
	printf("\n");
	
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

	printf("数组arrC中的元素为：");
	for (int i = 0; i < 8; i++)
	{
		printf("%d ", arrC[i]);
	}
	printf("\n\n");

	printf("删除arrC中所有值为3元素后数组为：");
	Delete_item(arrC, 3);
	for (int i = 0; i < 6; i++)
	{
		printf("%d ", arrC[i]);
	}
	printf("\n");

	return 0;
}
