#pragma once
#include<iostream>
#include<string>
using namespace std;
enum state  { R,E };
class pcb {
public:
	pcb(string name,int time,int no,state s);
	pcb(pcb &p);
	void run_once();
	void init(string name, int time, int no, state s);
	void show();

	string name;//进程名字
	int time;//执行时间
	int no;//进程优先数
	state s = R;//进程状态
};
pcb::pcb(string name="", int time=0, int no=0, state s=R) {
	name = name;
	time = time;
	no = no;
	s = s;
}
pcb::pcb(pcb &p) {
	name = p.name;
	time = p.time;
	no = p. no;
	s = p.s;
}
void pcb::run_once() {
	time = time - 1;
	no = no - 1;

}
void pcb::init(string n, int t, int c, state S) {
	name = n;
	time = t;
	no = c;
	s = S;
}
void pcb::show() {
	cout << "进程" << name << ":" << "剩余所需时间：" << time << "  进程优先数：" << no;
	if (s == R) cout << "  进程状态：R（就绪）";
	else cout << "  进程状态：E（结束）";
	cout << endl;
}



            
/*typedef struct LNode {
	pcb e;
	struct LNode *next;

}LinkNode;

//头插法建立单链表
void CreatListL(LinkNode *&L, pcb A[], int n) {
	LNode *s;
	L = (LinkNode*)malloc(sizeof(LinkNode));
	L->next = NULL;
	for (int i = 0; i < n; i++) {
		s = (LinkNode*)malloc(sizeof(LinkNode));
		s->e = A[i];
		s->next = L->next;
		L->next = s;
	}
}*/


