#include <stdlib.h>
#include <iostream>
#include <iomanip>

using namespace std;



int n = 100; // ������
int m = 100; // ��Դ������
int Available[100] = { 0 };   // ������Դ
int Max[100][100] = { 0 };        // �������
int Allocation[100][100] = { 0 }; // �ѷ�����Դ
int Need[100][100] = { 0 };    // �������
int Work[100] = { 0 };   // ��������
bool Finish[100] = { 0 };    // �Ƿ�����
int Request[100] = { 0 };    // ������Դ
char Name[100] = { 0 }; // ��Դ���� 
int P = 0;  // ������Դ�Ľ��̣�������

void init();
bool safeCheck(bool flag);
void printTable();
void recoverSafe();
void banker();

// ��ʼ�����̺���Դ
void init()
{
	cout << "���������Ľ���������";
	cin >> n;
	cout << "������������Դ������";
	cin >> m;
	for (int i = 0; i < 26; i++)
	{
		Name[i] = i + 65;//����תΪ��ĸ����Դ��Ŵ�A��ʼ
	}
	for (int i = 0; i < m; i++)
	{
		
		cout << "������ϵͳ��" << Name[i] << "��Դ��������";
		cin >> Available[i];
	}
	cout << "����������̶Ը���Դ�������������" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> Max[i][j];
	cout << "����������̵�ǰ�ѷֵø���Դ��������" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> Allocation[i][j];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			Need[i][j] = Max[i][j] - Allocation[i][j];
	// ��ʼ��Available
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			Available[j] = Available[j] - Allocation[i][j];
	// ��ʼ��Work
	recoverSafe();
}

// ��ȫ�Լ��
bool safeCheck(bool flag)
{
	
	cout << "   DATA  " << setfill(' ') << setw(3 * m + 2) << "Work"  << setw(3 * m + 2) << "Need" << "   " << setw(3 * m + 2) << "Allocation" << " " << setw(3 * m + 2) << "Work+Allo" << "  " << "Finish " << endl;//����

	cout << " RESOURCE  ";

	for (int i = 0; i < m; i++)
		cout << "  " << Name[i];
	cout << "   ";
	for (int i = 0; i < m; i++)
		cout << "  " << Name[i];
	cout << "   ";
	for (int i = 0; i < m; i++)
		cout << "  " << Name[i];
	cout << "   ";
	for (int i = 0; i < m; i++)
		cout << "  " << Name[i];
	cout << "   " << endl;

label:
	for (int i = 0; i < n; i++)
	{
		int count = 0;
		for (int j = 0; j < m; j++)
		{
			if (!Finish[i] && Need[i][j] <= Work[j])
			{
				count++;
			}
			if (count == m)
			{
				cout << "    P" << i << "     ";
				for (int k = 0; k < m; k++)
					cout << " " << setw(2) << Work[k];
				cout << "   ";
				for (int k = 0; k < m; k++)
					cout << " " << setw(2) << Need[i][k];
				cout << "   ";
				for (int k = 0; k < m; k++)
					cout << " " << setw(2) << Allocation[i][k];
				cout << "   ";

				for (int k = 0; k < m; k++)
				{
					Work[k] = Work[k] + Allocation[i][k];
				}
				Finish[i] = true;

				for (int k = 0; k < m; k++)
					cout << " " << setw(2) << Work[k];
				cout << "   ";
				cout << "  " << Finish[i] << "   ";
				cout << endl;
				goto label;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (!Finish[i])
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		cout << "ϵͳ���ڰ�ȫ״̬��" << endl;
		return true;
	}
	else
	{
		cout << "ϵͳ���ڲ���ȫ״̬��" << endl;
		return false;
	}
}

// ��ӡ�����������Դ�����
void printTable()
{
	cout << "   DATA " << setw(4 * m) << "Max" << " " << setw(4 * m) << "Allocation"  << setw(4 * m) << "Need" << " " << setw(4 * m) << "Available" << " " << endl;

	cout << " RESOURCE  ";

	for (int i = 0; i < m; i++)
		cout << " " << Name[i] << "  ";
	cout << " ";
	for (int i = 0; i < m; i++)
		cout << " " << Name[i] << "  ";
	cout << " ";
	for (int i = 0; i < m; i++)
		cout << " " << Name[i] << "  ";
	cout << " ";
	for (int i = 0; i < m; i++)
		cout << " " << Name[i] << "  ";
	cout << " " << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "   P" << i << "      ";
		for (int j = 0; j < m; j++)
		{
			cout << " " << setfill('0') << setw(2) << Max[i][j] << " ";
		}
		cout << " ";
		for (int j = 0; j < m; j++)
		{
			cout << " " << setfill('0') << setw(2) << Allocation[i][j] << " ";
		}
		cout << " ";
		for (int j = 0; j < m; j++)
		{
			cout << " " << setfill('0') << setw(2) << Need[i][j] << " ";
		}
		cout << " ";
		if (i == 0)
		{
			for (int j = 0; j < m; j++)
				cout << " " << setfill('0') << setw(2) << Available[j] << " ";
			cout << " ";
		}
		cout << endl;
	}
}

// ��ȫ�Լ��󣬻ָ�Work������Finish����
void recoverSafe()
{
	// �ָ�Work
	for (int i = 0; i < m; i++)
		Work[i] = Available[i];
	for (int i = 0; i < n; i++)
		Finish[i] = false;
}

// ���м��㷨
void banker()
{
	// �ͻ�����ʾ
	cout << "��������Ҫ������Դ�Ľ��̱�ţ�" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << setfill(' ') << setw(3) << "P" << i << ":" << i << endl;
	}
	// �������Ϸ���
	int tmpP = -1;
	bool flagP = false;
	while (!flagP)
	{
		cout << "���̱��:";
		cin >> tmpP;
		if (tmpP < 0 || tmpP >= n)
		{
			cout << "�˽��̲����ڣ����������룡" << endl;
			flagP = false;
		}
		else
		{
			P = tmpP;
			flagP = true;
		}
	}

	// ȷ��������ԴRequest
	for (int i = 0; i < m; i++)
	{
		cout << "���������P" << P << "�����" << Name[i] << "��Դ��������";
		cin >> Request[i];
	}

	// �жϽ������������Ƿ�С��������������������������
	bool flag = true;
	int countRN = 0;
	for (int i = 0; i < m; i++)
	{
		if (Request[i] <= Need[P][i])
			countRN++;
		if (countRN == m)
			flag = true;
		else
			flag = false;
	}
	if (flag)
	{
		// �������������Ƿ�С��ϵͳ����������
		int countRA = 0;
		for (int i = 0; i < m; i++)
		{
			if (Request[i] <= Available[i])
				countRA++;
			if (countRA == m)
				flag = true;
			else
				flag = false;
		}
		if (flag)
		{
			// ϵ��Դ���������
			for (int i = 0; i < m; i++) {
				Available[i] = Available[i] - Request[i];
				Allocation[P][i] = Allocation[P][i] + Request[i];
				Need[P][i] = Need[P][i] - Request[i];
				Work[i] = Work[i] - Request[i];
			}
			// T0ʱ�̵���Դ�����
			cout << "-----------------------ΪP" << P << "������Դ�����Դ�����------------------------" << endl;
			printTable();
			// ��ȫ���㷨
			cout << "------------------------P" << P << "������Դʱ�İ�ȫ�Լ��-------------------------" << endl;
			flag = safeCheck(flag);

			// �����ȫ�Լ�鲻ͨ��������ս����������Դ
			if (!flag)
			{
				for (int i = 0; i < m; i++) {
					Available[i] = Available[i] + Request[i];
					Allocation[P][i] = Allocation[P][i] - Request[i];
					Need[P][i] = Need[P][i] + Request[i];
					Work[i] = Work[i] + Request[i];
				}
			}
			recoverSafe();
		}
		else
			cout << "********************************ϵͳ�����㹻��Դ********************************" << endl;
	}
	else
		cout << "************************�����ѳ�������P" << P << "�������ֵ************************" << endl;
}

int main(void)
{
	// ��ʼ�����̺���Դ
	cout << "********************************��ʼ�����̺���Դ********************************" << endl;
	init();
	cout << "**********************************��ʼ�������**********************************" << endl;

	// T0ʱ�̵���Դ�����
	cout << "---------------------------T0ʱ�̵���Դ�����----------------------------" << endl;
	printTable();

	// T0ʱ�̵İ�ȫ�Լ��
	cout << "---------------------------T0ʱ�̵İ�ȫ�Լ��----------------------------" << endl;
	bool tmp = true;
	bool flagInit = safeCheck(tmp);
	// �ָ���ȫ�Լ������
	recoverSafe();

	// ���м��㷨
	while (true)
	{
		cout << "�Ƿ�Ҫ����������Դ(1:������2���˳�):" << endl;
		int func;
		cin >> func;
		if (func==2)
			break;


		banker();
	}






	return 0;
}