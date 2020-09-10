#pragma once
#include<iostream>
#include"Block.h"
using namespace std;
typedef struct LNode {
	Block b;
	struct LNode *next;

}LinkNode;
void listdelete(LinkNode *&L,int i);//删掉链表的第i个结点
void listinsert(LinkNode *&L, int i, Block T);//将结点T插入为第i个结点
void listdelete1(LinkNode *&L, int i, Block &t);
void listinsert1(LinkNode *&L, LNode *T, int Address, int Length, int No);
void listedit(LinkNode *&L, int i,Block t);//修改链表中第i个结点
void main() {
	bool flag = true;
	int p_len;
	int i = 0;
	int func;
	int k=1;
	int ini_end[128] = {24,60,87,120};
	int new_end[128];
	LinkNode *L;//空闲Block链表
	LinkNode *O;//被占用Block链表
	LNode *T;
	Block B1(0, 0, 25);
	Block B2(1, 30, 31);
	Block B3(2, 72, 16);
	Block B4(3, 100, 21);
	//内存初始状态，设内存起始地址从0开始
	Block B[128] = { B1,B2,B3,B4 };

	


	//空闲Block链接成单链表（尾插法）
	LNode *S, *R;
	L = new LinkNode();
	R = L;
	for (int i = 0; B[i].length!=0; i++) {
		S = new LinkNode();
		S->b = B[i];
		R->next = S;
		R = S;
	}
	R->next = NULL;//R指向尾结点

	//被占用单链表链接成单链表（尾插法），初始状态下没有加入结点
	LNode *OS, *OR;
	O= new LinkNode();
	OR = O;
	OR->next = NULL;//OR指向尾结点
	//LNode *T = O->next;
	

	

	LNode *W = L->next;
	cout << "内存初始分配情况：" << endl;
	while (W != NULL) {
		W->b.show();
		W = W->next;
	}

//分配内存
label1:		cout << "输入请求分配的内存长度：";
		cin >> p_len;
		W = L->next;
		int count = 1;
		LNode *editno_temp;
		while (W != NULL) {
			if (W->b.length < p_len) {
				W = W->next; count++;
			}
			else {
				W->b.length = W->b.length - p_len; //分配成功
				//把节点中的数据保存一下
				int tempaddress = W->b.address;
				int templength = W->b.length;

				if (W->b.length == 0) {
					/*当删除L中的第i个结点时：其后面的每个结点（i+1开始）的编号--；
					当添加L中的第i个结点时：其后面的每个结点（i+1开始）的编号++；
					这样做确保了L编号正确。因为每次有内存申请时，都会把count赋值为1，
					即从L中的第一个结点开始找，找到第count个。只要增删第count个结点即可。*/
					editno_temp = W->next;
					while(editno_temp!=NULL){
						editno_temp->b.no--;
						editno_temp = editno_temp->next;
					}
					ini_end[W->b.no] = -2;
					//链表中删除这个节点
					listdelete(L, count);

				}

				cout << "当前内存分配情况：" << endl;
				T = L->next;
				while (T != NULL) {
					T->b.show();
					T = T->next;
				}
				cout << endl;
				//本次分配出去的内存（被占用的Block）要链入一个新链表
				Block o(k, tempaddress + templength, p_len);
				
				OS = new LinkNode();
				OS->b = o;
				OR->next = OS;
				OR = OS;
				OR->next = NULL;
				k++;

				//把ini_end数组中对应的结点修改
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
		if (W == NULL) { cout << "分配请求失败！" << endl; }
		cout << "接下来要分配内存还是释放内存？1：分配内存，2：释放内存";
		cin >> func;
		if (func == 1) { goto label1; }
		else { goto label2; }
	

//释放内存
	label2:		LNode *Ocu = O->next;
		int ocu_address=0;
		int ocu_length = 0;
		int end;
		cout << "当前已被占用的内存情况：" << endl;
		if (Ocu == NULL) { cout << "还没有内存被占用！" << endl; goto label1; }
		while (Ocu != NULL) {
			Ocu->b.show();
			Ocu = Ocu->next;
		}
		Ocu = O->next;

		int a;
		cout << "你想释放哪个内存?请输入编号：";
		cin >> a;
		Block t;
		//处理O中的编号
		
		while (Ocu != NULL ) {
			if (Ocu->b.no < a) { goto jump; }
			else if (Ocu->b.no == a) {
				ocu_address = Ocu->b.address; ocu_length = Ocu->b.length; 
				 goto jump;
			}//找到本次要删除的结点时，将其信息存好
			else { Ocu->b.no--; }
jump:			Ocu = Ocu->next;
		}


		listdelete1(O, a,t);//从《已分配block链表》中删除编号为a的节点
	    
		//什么时候释放内存时需要新建L表项呢？当且仅当：该O结点的起始地址》距离最近的可用block的终末地址 + 1


		T = L->next;//从L中的第一个结点开始寻找

		if (T->b.address > 0 && T->next->b.address > ocu_address) {//新插入的结点要作为第一个结点
			Block Temp(0, ocu_address, ocu_length);
			listinsert(L, 1, Temp);//将新建的结点插入为第一个结点
			//处理L中的编号
			LNode *Tt = L->next->next;
			while (Tt != NULL) { Tt->b.no++; Tt = Tt->next; }
		}


		else {
			while (T != NULL) {
				if (T->next->b.address > ocu_address) { break; }
				T = T->next;

			}//找到了距离最近的可用block
			if (ocu_address > T->b.address + 1) {
				int tool = T->b.no + 1;
				listinsert1(L, T, ocu_address, ocu_length, tool);//将新建的结点插入到T结点后面
				//处理L中的编号
				LNode *Tt = T->next->next;
				while (Tt != NULL) { Tt->b.no++; Tt = Tt->next; }
			}


			else listedit(L, count, t);//不用创建新表项的情况
		}

		cout << "当前内存分配情况：" << endl;
		T = L->next;
		while (T != NULL) {
			T->b.show();
			T = T->next;
		}
		cout << endl;
		cout << "接下来要分配内存还是释放内存？1：分配内存，2：释放内存";
		cin >> func;
		if (func == 1) { goto label1; }
		else { goto label2; }

	
}

void listdelete(LinkNode *&L, int i    ) {//删除第i个结点
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
void listdelete1(LinkNode *&L, int i,Block &t) {//删除第i个结点,并将其存入t中
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

