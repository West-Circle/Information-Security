#include<iostream>
#include<vector>
#include<string>
#include<iterator>
using namespace std;

string Find_Repeat_String(string str)
{
	string temp,str1;
	int maxlen = 0;
	for(int i = 0 ; i < str.length() ; i++){
        for(int j = str.length() - i ; j != 0 ; j--){
            temp = str.substr(i,j); // get the sub string from last index to i
            int pos1 = str.find(temp);
            int pos2 = str.rfind(temp); // see whether got repeat or not and get the position
            int length = temp.length();
            if(pos1 != pos2 && length > maxlen){ //if the two position not same and length is maximum
                str1 = temp;
                maxlen = length;
            }
            //else continue;
        }
    }
    return str1;
}
int main(){
	string str = "ktbueluegvitnthuexmonveggmrcgxptlyhhjaogchoemqchpdnetxupbqntietiabpsmaoncnwvoutiugtagmmqsxtvxaoniiogtagmbpsmtuvvihpstpdvcrxhokvhxotawswquunewcgxptlcrxtevtubvewcnwwsxfsnptswtagakvoyyak";
	string temp = str; //string that let to find
    string temp1; //find string
    vector<string> vs;
    //find repeat string and length
    temp1 = Find_Repeat_String(temp);
	while(temp1.length() > 2){ //the minimum length is 3
        cout << temp1 << " ";
        vs.push_back(temp1);
        vector<int> v;
        string temp2 = str; // full string
        int pos1 = temp2.find(temp1);
        while(pos1 != string::npos){
            v.push_back(pos1 + temp1.length());//push the position to vector
            temp2.erase(0, pos1+temp1.length()); //erase the string which before the position
            pos1 = temp2.find(temp1);//find next one
        }
        vector<int>::iterator ite;
        for(ite = v.begin() ; ite < v.end() ; ite++){
            cout << *ite << " ";
        }
        //delete the repeated string
        int pos2 = temp.find(temp1);
        while(pos2 != string::npos){
            temp.erase(pos2, temp1.length());
            pos2 = temp.find(temp1);
        }
        cout << endl;
        temp1 = Find_Repeat_String(temp);
    }
    int minlen = 9999;
    for(int i = 0 ; i < vs.size() ; i++){
        string s = vs[i];
        if(s.length() < minlen){
            minlen = s.length();
        }
    }
    //found the gcd of key length is 3
    cout << "GCD��" << minlen <<endl;
    cout << ".............................................................." << endl;

    //get the frequency
    //minlen is 3 then get the char that separate with 3 char 
    //ex : abcde... , then we will get ad,be,c... 
    for(int i = 0 ; i < minlen ; i++){
        string s = "";
        for(int j = i ; j < str.length() ; j = j + minlen){
            s = s + str[j];
        }
        cout << "��" << i+1 << "�� : " << s << endl;
        int count[26] = {};
        for(int j = 0 ; j < s.length() ; j++){
            int index = s[j] - 'a';
            count[index]++;
        }
        int maxcount = 0;
        for(int j = 0 ; j < 26 ; j++){
            if(count[j] > count[maxcount]) {
                maxcount = j; //get the maximum count index
            }
            if(count[j] != 0){
                cout << char(j + 'a') << " : " << count[j] << endl;
            }
        }
        cout << "Maximum occurrence of a character : " << char(maxcount + 'a') << endl;
		cout << "Number of Occurrence : " << count[maxcount] << "times" << endl; 
     	cout << ".............................................................." << endl;
	}
	
	//find the possible key to decrypt vignere cipher
	string combination[16] = {"cex","cox","csx","ctx","gex","gox","gsx","gtx",
								"pex","pox","psx","ptx","vex","vox","vsx","vtx"}; 
	string possible_key[48] = "";
	int k = 0, countkey = 0;
	char c[5] = "pes";
	while(k != 3){
		string temp[16] = combination;
		for(int i = 0 ; i < 16 ; i++){
			for(int j = 0 ; j < 3 ; j++){ 	
				temp[i][j] = (temp[i][j] - c[k] + 26 ) % 26 + 'a';		
			}
			possible_key[countkey] = temp[i]; 
			countkey++;
		}
		k++;
	}
	for(int i = 0 ; i < 48 ; i++){
		string s = str;
		for(int j = 0 ; j < s.length() ; j++){
			s[j] = ( (s[j] - 'a') - (possible_key[i][j % 3] - 'a') + 26 ) % 26 + 'a'; 
		}
		cout << i+1 << "." << "可能是密文得密钥：" << possible_key[i] << endl; 
		cout << s << endl ;
	}
}



