
#include "connection.h"

Connection::Connection(){
   // I'm already done! 
   set_connection();
}


Connection::~Connection(){
   // TODO: Complete me!
   delete birthdate;
   delete email;
   delete phone;
}


Connection::Connection(string fname, string lname, \
       string bdate, string email, string phone){
   // TODO: Complete this method!
   // phone and email strings are in full version
   this->f_name = fname;
   this->l_name = lname;
   this->birthdate = new Date(bdate);

   size_t len = email.length();
   size_t idx = email.find(')');
   string str1 = email.substr(1,(idx-1));   
   string str2 = email.substr((idx+2),(len-idx));
   this->email = new Email(str1,str2);
   
   len = phone.length();
   idx = phone.find(')');
   str1 = phone.substr(1,(idx-1));
   str2 = phone.substr((idx+2),(len-idx));
   this->phone = new Phone(str1,str2);
   
}


Connection::Connection(string filename){
   // TODO: Complete this method!
   set_connection(filename);
}


void Connection::set_connection(){
   // prompts for the information of the user
   // first/last name can have spaces!
   // date format must be "M/D/YYYY"
   // We are sure user enters info in correct format.
   // TODO: complete this method!
   string temp;
   string tempe;
   string tempp;
   string typee;
   string typep;

   cout << "First Name: ";
   // code here
   getline(cin,f_name);
	cout << "Last Name: ";
   // code here
   getline(cin,l_name);
   cout << "Birthdate (M/D/YYYY): ";
   // code here
   getline(cin,temp);
    
   cout << "Type of email address: ";
   // code here
   getline(cin,typee);
   
   cout << "Email address: ";
   // code here
   getline(cin,tempe);

   cout << "Type of phone number: ";
   // code here
   getline(cin,typep);
   cout << "Phone number: ";
   // code here
   getline(cin,tempp);
   
   this -> birthdate = new Date(temp);
   this -> email = new Email(typee, tempe);
   this -> phone = new Phone(typep, tempp);
   
}


void Connection::set_connection(string filename){
   // TODO: Complete this method!
   // Look at connection_template files as examples.     
   // Phone number in files can have '-' or not.
   ifstream input;
   char trash;
   string temp;
   size_t idx;
   size_t len;
   input.open(filename.c_str());
   getline(input,temp);
   idx = temp.find(',');
   len = temp.length();
   l_name = temp.substr(0,idx);
   f_name = temp.substr((idx+2),(len-idx));
   
   getline(input,temp);
   this -> birthdate = new Date(temp); 
   getline(input,temp);
   len = temp.length();
   idx = temp.find(')');
   string str1 = temp.substr(1,(idx-1));   
   string str2 = temp.substr((idx+2),(len-idx));
   this->email = new Email(str1,str2);
   
   getline(input,temp);
   len = temp.length();
   idx = temp.find(')');
   str1 = temp.substr(1,(idx-1));
   str2 = temp.substr((idx+2),(len-idx));
   this->phone = new Phone(str1,str2);
   
}

void Connection::makeFriends(Connection* newFriend){
   myfriends.push_back(newFriend);
}

void Connection::write_connection(ofstream& output)
{  

   output << l_name << ", " << f_name << endl;
   output << birthdate->get_date() << endl;
   output << email->get_contact() << endl;
   output << phone->get_contact() << endl;
   for(int i=0; i < myfriends.size(); i++)
   {
      output << codeName(myfriends[i]->f_name, myfriends[i]->l_name) << endl;
   }
   output << "--------------------" << endl;



}




bool Connection::operator==(const Connection& rhs){
   // TODO: Complete this method!
   // Note: Difference to Lab is that from now on the combination of fname-lname is unique for any connection
   if ( (this->f_name == rhs.f_name) && 
    (this->l_name == rhs.l_name))
      return true;
   else
      return false;
}


bool Connection::operator!=(const Connection& rhs){ 
   // TODO: Complete this method!
   return !(*this == rhs);
}


void Connection::print_connection(){
   // Already implemented for you! Do not change!
   cout << l_name <<", " << f_name << endl;
	birthdate->print_date("Month D, YYYY");
   email->print();
   phone->print();
   for(int i=0; i < myfriends.size(); i++)
   {
      cout << codeName(myfriends[i]->f_name, myfriends[i]->l_name) << endl;
   }
}

