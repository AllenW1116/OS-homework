#pragma once
#include<iostream>
using namespace std;
enum state {E,F};
class Block {
public:
	int no;//������
	int address;//��ʼ��ַ
	int length;//��������
	state s = E;
	Block(int n = 0, int a = 0, int l = 0, state ss = E) {
		; no = n;
		address = a;
		length = l;
		s = ss;
	}
	Block(Block &t);
	void init(int n=0, int a=0, int l=0);//��ʼ��
	bool arrange(int p_len);//���䱾����
	void show();

};

Block::Block(Block &b) {
	no = b.no;
	address = b.address;
	length = b.length;
}
bool Block::arrange(int p_len) {
	if (p_len < length) { length = length - p_len; return true; }
	else return false;
}
void Block::show() {
	cout << "������ţ�" << no << " ��ʼ��ַ��" << address << " ���ȣ�" << length<<endl;
}

