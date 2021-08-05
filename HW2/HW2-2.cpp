#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZEARRAY 1000
char result[2*SIZEARRAY];
char remainder[SIZEARRAY];

int cmp(char *a, char *b){
    int len_a = strlen(a);
    int len_b = strlen(b);
    if(len_a > len_b || (len_a == len_b && strcmp(a,b) > 0)) return 1;
    else return 0;
}

void add(char *a, char *b){
    if(strlen(a) < strlen(b)){
        char *temp;
        temp = a;
        a = b;
        b = temp;
    }
    int len_a = strlen(a);
    int len_b = strlen(b);
    int temp1, posA, posB; //position a and b
    int carry = 0; //进位 
    result[len_a] = '\0';
    posA = len_a - 1; posB = len_b - 1;
    while(posA >= 0){
        temp1 = (a[posA] - '0') + carry;
        if(posB >= 0) temp1 = temp1 + (b[posB]-'0');
        if(temp1 >= 10){
            carry = 1; //进位1
            result[posA] = temp1 - 10 + '0'; // + '0' for back to number in char
        }else {
            carry = 0;
            result[posA] = temp1 + '0';
        }
        posA--;
        posB--;
    }
    //after the posA become < 0 , if still got carry then carry in
    if(carry == 1){
        for(int i = len_a ; i >= 0 ; i--){
            result[i+1] = result[i];
        }
        result[0] = '1';
    }
}

void sub(char *a, char *b){
	if(strcmp(a,b) == 0) {
        strcpy(result,"0");
        return;
    }
    if(cmp(a,b) == 0) {
        printf("-");
        char *temp;
        temp = a;
        a = b;
        b = temp;
    }
    int len_a = strlen(a);
    int len_b = strlen(b);
    int temp, posA, posB; //position a and b
    int borrow = 0; //借位 
    result[len_a] = '\0';
    posA = len_a - 1; posB = len_b - 1;
    while(posA >= 0){
        temp = (a[posA] - '0') - borrow;
        if(posB >= 0) temp = temp - (b[posB] - '0');
        if(temp < 0){
            borrow = 1;
            result[posA] = 10 + temp + '0';
        }else{ // temp > 0
            borrow = 0;
            result[posA] = temp + '0';
        }
        posA--;
        posB--;
    }
    //由于上面已经交换过了，现在的a一定比b大且长/等长，所以不考虑会减成负数
    //现在考虑如果a与b等长且a的第一位减去b的第一位等于0的话或第2、3、4...位都等于0的话，就移位
    int postemp = 0; //寻找当前不是0的位置
    while(result[postemp] == '0') postemp++;
    for(int i = 0 ; i <= (len_a - postemp); i++){
        result[i] = result[i+postemp];
    }
}

void mul(char *a, char *b){
	char temp[2*SIZEARRAY];
    char multi[11][SIZEARRAY+1];
    int len_a = strlen(a);
    int len_b = strlen(b);
    strcpy(multi[0],"0");
    strcpy(temp,"0");
    for(int i = 1; i<=9 ; i++){
        //get the multi of a ex:multi[1] = a * 1 , multi[2] = a * 2... multi[9] = a * 9
        add(multi[i-1], a);
        strcpy(multi[i], result);
    }
    strcpy(result,"0");//initial to 0
    for(int i = len_b - 1; i >= 0 ; i--){
        if(b[i] != '0'){
            strcpy(temp, multi[b[i] - '0']);
            for(int j  = 0 ; j < len_b - i - 1 ; j++){
                //乘法进位j次，第一次不用进位
                strcat(temp,"0");
            }
            //进位后再加 
            add(result,temp);
        }
    }
}

void div(char *a, char *b){
	char quotient[SIZEARRAY];
    char tempR[2];//strcat
    int tempQ;
    tempR[1] = '\0';
    char multi[10][SIZEARRAY+1];
    int len_a = strlen(a);
    int len_b = strlen(b);
    
    strcpy(multi[0],"0");
    strcpy(tempR,"0");
    for(int i = 1; i<=9 ; i++){
        //same as mul function
        //get the multi of b ex:multi[1] = b * 1 , multi[2] = b * 2... multi[9] = b * 9
        add(multi[i-1], b);
        strcpy(multi[i], result);
    }
    //initial quotient and remainder to null
    strcpy(quotient,"");
    strcpy(remainder,"");
    int pos = 0;
    while(pos != len_a){
        tempR[0] = a[pos];
        //put in to remainder first
        strcat(remainder, tempR);
        tempQ = 1;
        while(tempQ != 10 && cmp(multi[tempQ], remainder) == 0){
            //get the quotient if the multi of quotient and divisor > dividend
            //ex 5 / 4 , 1*5 > 4 then found quotient(0) and break loop
            tempQ++;
        }
        tempR[0] = tempQ - 1 + '0'; //found quotient*divisor over than dividend then quotient-1 first
        if((tempR[0] == '0' && quotient[0] == '\0') == 0)  
            //if the found quotient is 0 and quotient is null then skip this strcat
            strcat(quotient,tempR);
        sub(remainder, multi[tempQ-1]);
        strcpy(remainder, result);
        if(remainder[0] == '0') remainder[0] = '\0';
        pos++;
    }

    if(quotient[0] == '\0') strcpy(quotient, "0");
    if(remainder[0] == '\0') strcpy(remainder, "0");
}

int main(){
    char p[SIZEARRAY];
    char g[SIZEARRAY];
    int A, B;
    while(1){
    	//DH algorithm
        printf("请输入p,q,A's private key,B's private key : \n");
		printf("p = ");
        scanf("%s",p);
        printf("g = ");
        scanf("%s",g);
		printf("A's private key = ");
        scanf("%d",&A);
        printf("B's private key = ");
        scanf("%d",&B);
		       
        //A's public key
        printf("\nA's public key = ");
        strcpy(result, g); //result get number of g
   		char tempresult[2*SIZEARRAY];     
		if(g[0] == '0') printf("0\n");
        else {
        	//g^a , pow(g,a)
        	for(int i = 1; i < A ; i++){
                strcpy(tempresult,result); //copy result to tempresult
                mul(tempresult, g); //use tempresult to multiply g
        	}
        }
        strcpy(tempresult,result); //pow(g,a) result
        if(p[0] == '0') printf("输入错误,不能除以0!!!\n");
        else if(tempresult[0] == '0') printf("0\n");
        else {
        	div(tempresult,p);
        	printf("%s\n",remainder);
        }
        
        //B's public key
        printf("B's public key = ");
        strcpy(result, g); //result get number of g     
		if(g[0] == '0') printf("0\n");
        else {
        	//g^b , pow(g,b)
        	for(int i = 1; i < B ; i++){
                strcpy(tempresult,result); //copy result to tempresult
                mul(tempresult, g); //use tempresult to multiply g
        	}
        }
        strcpy(tempresult,result); //pow(g,a) result
        if(p[0] == '0') printf("输入错误,不能除以0!!!\n");
        else if(tempresult[0] == '0') printf("0\n");
        else {
        	div(tempresult,p);
        	printf("%s\n",remainder);
        }
        
        //K's session key 
        char B_public[2*SIZEARRAY];
        printf("K's Session key = ");
        strcpy(B_public, result);
        if(B_public[0] == '0') printf("0\n");
        else{
        	//B's public key ^ a mod p
        	for(int i = 1; i < A ; i++){
        		strcpy(tempresult,result);
        		mul(tempresult, B_public);
        	}
        }
        strcpy(tempresult, result);
        if(p[0] == '0') printf("输入错误,不能除以0!!!\n");
    	else if(tempresult[0] == '0') printf("0\n");
		else{
			div(tempresult, p);
			printf("%s\n", remainder);
		} 
        printf("\n");
    }
}
