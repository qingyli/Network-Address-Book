#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(){

   string email ("180-1948-8576");
   size_t len = email.length();
   cout << len << endl;
   //size_t idx = email.find(')');
   //string str1(++email.begin(),idx);
   //string str1 = email.substr(1,(idx-1));   
   //string str2 = email.substr((idx+2),(len-idx));
   //cout << idx << endl;
   //cout << str1 << endl;
   //cout << str2 << endl;
   //string num = str2;
   if(email.find("-") !=  std::string::npos)
   {
      long int area_code = atoi(email.substr(0, 3).c_str());
      long int num1 = atoi(num.substr(4,3).c_str());
      long int num2 = atoi(num.substr(9,4).c_str());
      long int phone_num = area_code*10000000 + num1*10000 + num2;  
      cout << "found" << area_code << endl;
   } 

   return 0;



}
