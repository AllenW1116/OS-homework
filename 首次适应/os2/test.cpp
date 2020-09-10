#pragma once
#include<iostream>
#include"Block.h"
using namespace std;
typedef struct LNode {
	Block b;
	struct LNode *next;

}LinkNode;
void listdelete(LinkNode *&L,int i);//ɾ������ĵ�i�����
void listinsert(LinkNode *&L, int i, Block T);//�����T����Ϊ��i�����
void listdelete1(LinkNode *&L, int i, Block &t);
void listinsert1(LinkNode *&L, LNode *T, int Address, int Length, int No);
void listedit(LinkNode *&L, int i,Block t);//�޸������е�i�����
void main() {
	bool flag = true;
	int p_len;
	int i = 0;
	int func;
	int k=1;
	int ini_end[128] = {24,60,87,120};
	int new_end[128];
	LinkNode *L;//����Block����
	LinkNode *O;//��ռ��Block����
	LNode *T;
	Block B1(0, 0, 25);
	Block B2(1, 30, 31);
	Block B3(2, 72, 16);
	Block B4(3, 100, 21);
	//�ڴ��ʼ״̬�����ڴ���ʼ��ַ��0��ʼ
	Block B[128] = { B1,B2,B3,B4 };

	


	//����Block���ӳɵ�����β�巨��
	LNode *S, *R;
	L = new LinkNode();
	R = L;
	for (int i = 0; B[i].length!=0; i++) {
		S = new LinkNode();
		S->b = B[i];
		R->next = S;
		R = S;
	}
	R->next = NULL;//Rָ��β���

	//��ռ�õ��������ӳɵ�����β�巨������ʼ״̬��û�м�����
	LNode *OS, *OR;
	O= new LinkNode();
	OR = O;
	OR->next = NULL;//ORָ��β���
	//LNode *T = O->next;
	

	

	LNode *W = L->next;
	cout << "�ڴ��ʼ���������" << endl;
	while (W != NULL) {
		W->b.show();
		W = W->next;
	}

//�����ڴ�
label1:		cout << "�������������ڴ泤�ȣ�";
		cin >> p_len;
		W = L->next;
		int count = 1;
		LNode *editno_temp;
		while (W != NULL) {
			if (W->b.length < p_len) {
				W = W->next; count++;
			}
			else {
				W->b.length = W->b.length - p_len; //����ɹ�
				//�ѽڵ��е����ݱ���һ��
				int tempaddress = W->b.address;
				int templength = W->b.length;

				if (W->b.length == 0) {
					/*��ɾ��L�еĵ�i�����ʱ��������ÿ����㣨i+1��ʼ���ı��--��
					�����L�еĵ�i�����ʱ��������ÿ����㣨i+1��ʼ���ı��++��
					������ȷ����L�����ȷ����Ϊÿ�����ڴ�����ʱ�������count��ֵΪ1��
					����L�еĵ�һ����㿪ʼ�ң��ҵ���count����ֻҪ��ɾ��count����㼴�ɡ�*/
					editno_temp = W->next;
					while(editno_temp!=NULL){
						editno_temp->b.no--;
						editno_temp = editno_temp->next;
					}
					ini_end[W->b.no] = -2;
					//������ɾ������ڵ�
					listdelete(L, count);

				}

				cout << "��ǰ�ڴ���������" << endl;
				T = L->next;
				while (T != NULL) {
					T->b.show();
					T = T->next;
				}
				cout << endl;
				//���η����ȥ���ڴ棨��ռ�õ�Block��Ҫ����һ��������
				Block o(k, tempaddress + templength, p_len);
				
				OS = new LinkNode();
				OS->b = o;
				OR->next = OS;
				OR = OS;
				OR->next = NULL;
				k++;

				//��ini_end�����ж�Ӧ�Ľ���޸�
				int key = 0;
				int newi = 0;

				for (int i = 0; ini_end[i] != 0 && i < count; i++) {
					if (ini_end[i] > 0) { newi++; }

				}
				ini_end[newi - 1] = ini_end[newi - 1] - p_len;
				break;
			}
			//W = W->next;
		}
		if (W == NULL) { cout << "��������ʧ�ܣ�" << endl; }
		cout << "������Ҫ�����ڴ滹���ͷ��ڴ棿1�������ڴ棬2���ͷ��ڴ�";
		cin >> func;
		if (func == 1) { goto label1; }
		else { goto label2; }
	

//�ͷ��ڴ�
	label2:		LNode *Ocu = O->next;
		int ocu_address=0;
		int ocu_length = 0;
		int end;
		cout << "��ǰ�ѱ�ռ�õ��ڴ������" << endl;
		if (Ocu == NULL) { cout << "��û���ڴ汻ռ�ã�" << endl; goto label1; }
		while (Ocu != NULL) {
			Ocu->b.show();
			Ocu = Ocu->next;
		}
		Ocu = O->next;

		int a;
		cout << "�����ͷ��ĸ��ڴ�?�������ţ�";
		cin >> a;
		Block t;
		//����O�еı��
		
		while (Ocu != NULL ) {
			if (Ocu->b.no < a) { goto jump; }
			else if (Ocu->b.no == a) {
				ocu_address = Ocu->b.address; ocu_length = Ocu->b.length; 
				 goto jump;
			}//�ҵ�����Ҫɾ���Ľ��ʱ��������Ϣ���
			else { Ocu->b.no--; }
jump:			Ocu = Ocu->next;
		}


		listdelete1(O, a,t);//�ӡ��ѷ���block������ɾ�����Ϊa�Ľڵ�
	    
		//ʲôʱ���ͷ��ڴ�ʱ��Ҫ�½�L�����أ����ҽ�������O������ʼ��ַ����������Ŀ���block����ĩ��ַ + 1


		T = L->next;//��L�еĵ�һ����㿪ʼѰ��

		if (T->b.address > 0 && T->next->b.address > ocu_address) {//�²���Ľ��Ҫ��Ϊ��һ�����
			Block Temp(0, ocu_address, ocu_length);
			listinsert(L, 1, Temp);//���½��Ľ�����Ϊ��һ�����
			//����L�еı��
			LNode *Tt = L->next->next;
			while (Tt != NULL) { Tt->b.no++; Tt = Tt->next; }
		}


		else {
			while (T != NULL) {
				if (T->next->b.address > ocu_address) { break; }
				T = T->next;

			}//�ҵ��˾�������Ŀ���block
			if (ocu_address > T->b.address + 1) {
				int tool = T->b.no + 1;
				listinsert1(L, T, ocu_address, ocu_length, tool);//���½��Ľ����뵽T������
				//����L�еı��
				LNode *Tt = T->next->next;
				while (Tt != NULL) { Tt->b.no++; Tt = Tt->next; }
			}


			else listedit(L, count, t);//���ô����±�������
		}

		cout << "��ǰ�ڴ���������" << endl;
		T = L->next;
		while (T != NULL) {
			T->b.show();
			T = T->next;
		}
		cout << endl;
		cout << "������Ҫ�����ڴ滹���ͷ��ڴ棿1�������ڴ棬2���ͷ��ڴ�";
		cin >> func;
		if (func == 1) { goto label1; }
		else { goto label2; }

	
}

void listdelete(LinkNode *&L, int i    ) {//ɾ����i�����
	int j = 0;
	LinkNode *P = L, *Q;
	while (j < i - 1 && P != NULL) {
		j++;
		P = P->next;
	}
	Q = P->next;
	P->next = Q->next;
	free(Q);

}
void listdelete1(LinkNode *&L, int i,Block &t) {//ɾ����i�����,���������t��
	int j = 0;
	LinkNode *P = L, *Q;
	while (j < i - 1 && P != NULL) {
		j++;
		P = P->next;
	}
	Q = P->next;
	P->next = Q->next;
	t = Q->b;
	free(Q);

}
void listinsert(LinkNode *&L, int i, Block T) {
	LinkNode *P = L, *S;
	int j = 0;
	while (j < i - 1 && P != NULL) {
		j++;
		P = P->next;
	}
	S = new LinkNode();
	S->b = T;
	S->next = P->next;
	P->next = S;
	
}
void listinsert1(LinkNode *&L, LNode *T, int Address,int Length,int No) {
	LinkNode  *S;
	S = new LinkNode();
	S->b.address = Address; S->b.length = Length; S->b.no = No;
	S->next = T->next;
	T->next = S;

}
void listedit(LinkNode *&L, int i,Block t) {
	LinkNode *P = L;
	int j = 0;
	while (j < i  && P != NULL) {
		j++;
		P = P->next;
	}
	P->b.length = P->b.length + t.length;
}

