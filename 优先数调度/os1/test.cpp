#pragma once
#include<iostream>
#include<string>
#include"pcb.h"
using namespace std;
typedef struct LNode {
	pcb e;
	struct LNode *next;

}LinkNode;
void arange(pcb A[], int num);//用于排序
void deletehead(LinkNode *&L, pcb &T);//删掉链表的第一个结点,并将其存入T中
void insertend(LinkNode *&L, LinkNode *&R, pcb T);//将T插入到链表的尾部

int main() {
	
	cout << "请分别输入5个进程的名字、运行时间和优先数；用空格键分隔三个属性，用回车确定"<<endl;
	string name;
	int time = 0;
	int no = 0;
	state s = R;
	pcb p[5];
	LinkNode *L;
	pcb T;
	for (int i = 0; i < 5; i++) {
		cin >> name >> time >> no ;
		p[i].init(name, time, no, s);
	}
	

	for (int j = 5; j >= 1; j--)  //将pcb队列按照优先数降序排列
	{
		arange(p, 5);
	}

	cout << "初始状态：" << endl;
	for (int i = 0; i < 5; i++) {
		p[i].show();
	}
	
	
	
	//pcb链接成单链表（尾插法）
	LNode *S, *R;
	L = new LinkNode();
	R = L;
	for (int i = 0; i < 5; i++) {
			S = new LinkNode();
			S->e = p[i];
			R->next = S;
			R = S;
	}
	R->next = NULL;//R指向尾结点


	

	int k = 1;
	do {
		L->next->e.run_once();
		//cout << L->next->e.no << endl;
		if(L->next->e.time==0){//首节点退出队列，其状态改为E
			L->next->e.s = E;
			deletehead(L, T);
			LinkNode *key = L->next;
			for (int i = 0; i < 5; i++) {
				if (key != NULL) {
					p[i] = key->e; 
				}
				else { p[i]=T; break; }
				key = key->next;
			}
		}
		else {//加入尾部
			deletehead(L, T);
			insertend(L, R, T);
			LinkNode *key=L->next;
			for (int i = 0; i < 5; i++) {
				if (key != NULL) {
					p[i] = key->e; 
				}
				else break;
				key = key->next;
			}

		}
		cout << "轮次"<<k <<"："<< endl;
		for (int i = 0; i < 5; i++) {
			p[i].show();
		}
		cout << endl;
		k++;
	} while (1);
	

	return 0;


}

void arange(pcb A[], int num)
{
	for (int i = 0; i < num - 1; i++)
	{
		if (A[i].no < A[i + 1].no)
		{
			pcb temp;
			temp = A[i]; A[i] = A[i + 1];
			A[i + 1] = temp;
		}
	}
}

void deletehead(LinkNode *&L,pcb &T) {
	//删除第一个节点
	LinkNode *P = L, *Q;
	Q = P->next;
	P->next = Q->next;
	//存入T中
	T = Q->e;
	free(Q);
}

void insertend(LinkNode *&L, LinkNode *&R, pcb T) {
	LinkNode *P = L, *S;
	P =R;
	S = new LinkNode();
	S->e = T;
	S->next = P->next;
	P->next = S;
	R = S;
}

