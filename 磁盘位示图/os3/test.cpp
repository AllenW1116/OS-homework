

//ʵ�ʵ�λʾͼ�У�һ���洢��¼ֻռһλ��0��1�������˴�Ϊ�˷���۲죬��һ���ṹ������ʾһ��λ
//�����м�¼�������ַ�������ģ���������һ����ʼ��ַ���;�����0��
// " 0"��ʾδ���伴���� " 1"��ʾ����λʾͼ��С���������ȵķ��䷽ʽ���з����ʼ��ȫΪδ����" 0"
#include <iostream>
#include<string>
using namespace std;

typedef struct Bit {
	string fileName;//ռ�д˿���ļ���
	bool occupied = false;//�Ƿ���У���ֵ��Ϊ
}Bit;

Bit(*bitmap)[8] = new Bit[8][8];

//������п���
int getFreeNum(int fileLen) {
	int freeNum = 0;//���п���
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (!bitmap[i][j].occupied)
				freeNum++;
	return freeNum;
}

//�����ڴ�
void memReq() {
	string fileName;
	int fileLen;
	cout << "�����봴�����ļ�����";
	cin >> fileName;
	cout << "��������Ҫ�Ĵ��̿���(���ó��������64)��";
	cin >> fileLen;
	//�ж��ܷ����
	if (fileLen > getFreeNum(fileLen))
		cout << "������̿������󣬷���ʧ�ܣ�" << endl;
	else
	{
		cout << "����������ַ��" << endl;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!bitmap[i][j].occupied) {
					bitmap[i][j].occupied = true;
					bitmap[i][j].fileName = fileName;
					fileLen--;
					cout << "����ţ�" << i << "\t�ŵ��ţ�" << j / 4 << "\t�����¼�ţ�" << j % 4 << endl;
				}
				if (fileLen <= 0) {
					return;
				}
			}
		}
	}
}

//�ͷſռ�
bool memFree() {
	string fileName;
	cout << "�������ͷſռ���ļ�����";
	cin >> fileName;
	cout << "����ʱ���ֽںź�λ��: " << endl;
	bool isFind = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (bitmap[i][j].fileName == fileName) {
				isFind = true;
				bitmap[i][j].occupied = false;
				bitmap[i][j].fileName = ' ';
				cout << "�ֽں�" << i << "\tλ��" << j << endl;
			}

		}
	}
	if (!isFind) {
		cout << "δ�ҵ��ļ�!" << endl;
	}
	return isFind;
}

//��ӡλʾͼ
void showBitmap() {
	cout << "-----------------------���̴洢λʾͼ---------------------" << endl;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (bitmap[i][j].occupied) {
				cout << "1\t";
			}
			else {
				cout << "0\t";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	while (true) {
		int command;
		cout << "ѡ���ܣ�[1]�鿴λʾͼ��[2]�ռ����룻[3]�ռ���գ�[4]�˳�" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			showBitmap();
			break;
		case 2:
			memReq();
			break;
		case 3:
			memFree();
			break;
		case 4:
			break;
		default:
			break;
		}
	}
	return 0;
}
