#pragma once
#include<iostream>
#include<string>
#include"pcb.h"
using namespace std;
typedef struct LNode {
	pcb e;
	struct LNode *next;

}LinkNode;
void arange(pcb A[], int num);//��������
void deletehead(LinkNode *&L, pcb &T);//ɾ������ĵ�һ�����,���������T��
void insertend(LinkNode *&L, LinkNode *&R, pcb T);//��T���뵽�����β��

int main() {
	
	cout << "��ֱ�����5�����̵����֡�����ʱ������������ÿո���ָ��������ԣ��ûس�ȷ��"<<endl;
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
	

	for (int j = 5; j >= 1; j--)  //��pcb���а�����������������
	{
		arange(p, 5);
	}

	cout << "��ʼ״̬��" << endl;
	for (int i = 0; i < 5; i++) {
		p[i].show();
	}
	
	
	
	//pcb���ӳɵ�����β�巨��
	LNode *S, *R;
	L = new LinkNode();
	R = L;
	for (int i = 0; i < 5; i++) {
			S = new LinkNode();
			S->e = p[i];
			R->next = S;
			R = S;
	}
	R->next = NULL;//Rָ��β���


	

	int k = 1;
	do {
		L->next->e.run_once();
		//cout << L->next->e.no << endl;
		if(L->next->e.time==0){//�׽ڵ��˳����У���״̬��ΪE
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
		else {//����β��
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
		cout << "�ִ�"<<k <<"��"<< endl;
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
	//ɾ����һ���ڵ�
	LinkNode *P = L, *Q;
	Q = P->next;
	P->next = Q->next;
	//����T��
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

