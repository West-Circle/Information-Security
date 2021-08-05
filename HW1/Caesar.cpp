#include<iostream>
#include<cstring>
using namespace std;

int main()
{
	char str[100] = "yfqpnxhmjfuxmtbrjymjhtij";
	cout << "密文：" << str << endl;
	int count_shift = 0;
	for(int i = 0; i <= 25 ; i++){
		//test 26 type of possible , shift 1 / 2 / 3 / 4 / ... 
		for(int j = 0; j < strlen(str) ; j++){
			if(str[j] == 'z') { //如果遇到字母 Z ，则换成字母 A ，已经加一了所以跳到下一个循环 
				str[j] = str[j] - 'z' + 'a';
				continue;	
			}
			str[j] = str[j] + 1;
		}
		count_shift++;
		cout << "shift = " << count_shift << " 明文：" << str << endl << endl;
	}
	
	//ENCRYPT MY NAME
	char name[20] = "YAPXIYUAN";
	for(int k = 0; k < strlen(name) ; k++){
		//1.A 2.B 3.C 4.D ...
		//如果位移后大于26则除以26得余数再加'A' 
		name[k] = ( name[k] - 'A' + 16 ) % 26 + 'A' ;
	}
	cout << "我的名字的密文：" << name << endl;
}
