
#include "contact.h"
// TODO: Add needed libraries! 
using namespace std;

Email::Email(string type, string email_addr){
    // TODO: Complete me!
    this -> type = type;
    this -> email_addr = email_addr;
    
    
}


void Email::set_contact(){
    // TODO: Do not change the prompts!
	
    cout << "Enter the type of email address: ";
    // some code here
    getline(cin,type);

    cout << "Enter email address: ";
    // some code here
    getline(cin,email_addr);
}


string Email::get_contact(string style){
    // Note: We have default argument in declaration and not in definition!
    if (style=="full")
	    return "(" + type + ") " + email_addr;
    else 
        return email_addr;
}


void Email::print(){
   // Note: get_contact is called with default argument
   cout << get_contact() << endl;
}


Phone::Phone(string type, string num){
   // TODO: It is possible that num includes "-" or not, manage it!
   // TODO: Complete this method!
   // Note: We don't want to use C++11! stol is not valid!
   // The code has been covered in the discussion session

   // Note: Understand your own TA's bug!
   /*This code has a bug, can you understand why?
   long int area_code = atoi(num.substr(0, 3).c_str());
   long int number = atoi(num.substr(3).c_str()); 
   this->phone_num = area_code*10000000 + number; 
   */
   this -> type = type;
   //https://stackoverflow.com/questions/2340281/check-if-a-string-contains-a-string-in-c
   if(num.find("-") !=  std::string::npos)
   {  
      this -> phone_num = num;
   }
   else
   {
      this -> phone_num = num.substr(0, 3) + "-" + num.substr(3,3) + "-" + num.substr(6,4);
   }
   
   
    
}


void Phone::set_contact(){
   // TODO: Complete this method
   // Use the same prompts as given!
   string num;
	cout <<"Enter the type of phone number: ";
	getline(cin,type);
	cout << "Enter the phone number: ";
	getline(cin,num);
   if(num.find("-") !=  std::string::npos)
   {  
      this -> phone_num = num;
   }
   else
   {
      this -> phone_num = num.substr(0, 3) + "-" + num.substr(3,3) + "-" + num.substr(6,4);
   }
}


string Phone::get_contact(string style){
   // TODO: Complete this method, get hint from Email 
   // The code has been covered in discussion session 

   /* Note: Understand your own TA's bug!
    * This code has a bug, can you understand it!
   int x1 = (phone_num/10000000);
	int x2 = ((phone_num)/10000)%1000;
	int x3 = phone_num%10000;
   */
   if (style=="full")
	   return "(" + type + ") " + phone_num;
   else 
      return phone_num;
}


void Phone::print(){
   // Note: get_contact is called with default argument
	cout << get_contact() << endl;
}


