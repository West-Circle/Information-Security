#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char str[100] = "yfqpnxhmjfuxmtbrjymjhtij";
	cout << "���ģ�" << str << endl;
	int count_shift = 0;
	for(int i = 0; i <= 25 ; i++){
		//test 26 type of possible , shift 1 / 2 / 3 / 4 / ... 
		for(int j = 0; j < strlen(str) ; j++){
			if(str[j] == 'z') { //���������ĸ Z ���򻻳���ĸ A ���Ѿ���һ������������һ��ѭ�� 
				str[j] = str[j] - 'z' + 'a';
				continue;	
			}
			str[j] = str[j] + 1;
		}
		count_shift++;
		cout << "shift = " << count_shift << " ���ģ�" << str << endl << endl;
	}
	
	//ENCRYPT MY NAME
	char name[20] = "YAPXIYUAN";
	for(int k = 0; k < strlen(name) ; k++){
		//1.A 2.B 3.C 4.D ...
		//���λ�ƺ����26�����26�������ټ�'A' 
		name[k] = ( name[k] - 'A' + 16 ) % 26 + 'A' ;
	}
	cout << "�ҵ����ֵ����ģ�" << name << endl;
}
