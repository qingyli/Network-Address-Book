
#include "network.h"
#include <limits>
#include "misc.h"
#include <fstream>
#include <dirent.h>
#include <string> 
#include <vector>

Network::Network(){
    head = NULL;
    tail = NULL;
    count = 0;
}


Network::Network(string fileName){
    // TODO: complete this method!
    // Implement it in one single line!
    // You may need to implement the load method before this!
    loadDB(fileName);
}

Network::~Network(){
   // Copy from lab5 
   Connection* dummy;
   dummy = head;
   dummy = dummy->next;
   while(dummy != NULL)
   {      
      delete dummy->prev;
      dummy = dummy->next;  
   }
   delete tail;
}


void Network::push_front(Connection* newEntry){
    // Adds a new Connection (newEntry) to the front of LL
    // TA completed me in lab5 and since then I've not been changed! 
    newEntry->prev = NULL;
    newEntry->next = head;

    if (head != NULL)
        head->prev = newEntry;
    else
        tail = newEntry;
    
    head = newEntry;
    count++;
}


void Network::push_back(Connection* newEntry){
   // Adds a new Connection (newEntry) to the back of LL
   // Copy from your lab5
   newEntry->prev = tail;
   newEntry->next = NULL;
   if(tail != NULL)
   {
      tail->next = newEntry;
   }
   else
   {
      head = newEntry;
   }
   
   tail = newEntry;
   count++;

}


Connection* Network::search(Connection* searchEntry){
   // Searches the Network for searchEntry
   // if found, returns a pointer to it, else returns NULL
   // Copy from lab5     
   Connection* dummy;
   dummy = head;
   while(dummy != NULL)
   {
      if(*dummy == *searchEntry)
      {
         return dummy;
      }
      else
      { 
         dummy = dummy->next;
      }
   }
   return 0;
}


Connection* Network::search(string fname, string lname){
   // New == for Connection, only based on fname and lname
   // if found, returns a pointer to it, else returns NULL
   // TODO: Complete this method
   // Note: two ways to implement this, 1st making a new Connection with fname and lname and and using search(Connection*), 2nd using fname and lname directly.
   Connection* dummy;
   dummy = head;
   while(dummy != NULL)
   {
      if((dummy->f_name == fname) && (dummy->l_name == lname))
      {
         return dummy;
      }
      else
      {
         dummy = dummy->next;
      }  
   }
   return 0;
}

Connection* Network::search(string friendCode){
   Connection* dummy;
   dummy = head;
   while(dummy != NULL)
   {
      if(friendCode == codeName(dummy->f_name, dummy->l_name))
      {
         return dummy;
      }
      else
      {
         dummy = dummy -> next;
      }
   }
   return 0;
}

void Network::printDB(){
    // Leave me alone! I know how to print! 
    // Note: Notice that we don't need to update this even after adding to Connection attributes
    // This is a feature of OOP, classes are supposed to take care of themselves!
    cout << "Number of connections: " << count << endl;
    cout << "------------------------------" << endl;
    Connection* ptr = head;
    while(ptr != NULL){
        ptr->print_connection();
        cout << "------------------------------" << endl;
        ptr = ptr->next;
    }
}


void Network::saveDB(string filename){
   // Saves the netwrok in file <filename>
   // Note: The format of the output file is very abstract, just raw data
   // Look at studentDB.txt as a template
   // TODO: Update this method with new requirements
   // Note: notice the intentional flaw in this code, as compared to the note mentioned in printDB, now the one who is responsible for implementing Network should be aware of implementation of Connection, not good! You will fix this in PA2. 
   
   ofstream output;
   output.open(filename.c_str());
   
   Connection *dummy;
   dummy = head;
   while(dummy != NULL){
      dummy -> write_connection(output);
      dummy = dummy->next;
   }
   
   output.close();    
    
}


void Network::loadDB(string filename){
   // Loads the netwrok from file <filename>
   // The format of the input file is similar to saveDB
   // Look at network studentDB.txt as a template
   // Phone number can be with dashes or without them
   // TODO: Now you will notice you need to go back and make a new constructor to the Connection class,  
   // Connection::Connection(fname, lname, bdate, email, phone)
   // TODO: Update this method with new requirements 
   
   Connection *dummy; 
   dummy = head;
   while(dummy != NULL)
   {
      dummy = head->next;
      delete head;
      head = dummy;
      count--;
   }
   head = NULL;
   tail = NULL;
   
   ifstream input;
   input.open(filename.c_str());
   string p_hone, e_mail, temp, fname, lname, bdate;
   size_t len, idx;
   
   int i;
   
   while(getline(input,temp))
   {  
      i = 0;
      idx = temp.find(',');
      len = temp.length();
      lname = temp.substr(0,idx);
      fname = temp.substr((idx+2),(len-idx));
      getline(input,bdate);
      getline(input,e_mail);
      getline(input,p_hone);
      dummy = new Connection(fname,lname,bdate,e_mail,p_hone);
      
      push_back(dummy);
      
      getline(input,temp);
     
      while(temp.find("-") ==  std::string::npos)
      {
         dummy -> fcodes.push_back(temp);
         getline(input,temp);
         i++;
      }
      dummy = dummy->next;
   }
  
   dummy = head;
   Connection* buff;
   while(dummy != NULL)
   {
      for(int j = 0; j < dummy -> fcodes.size(); j++)
      {
         buff = search(dummy -> fcodes[j]);
         if(buff)
         {
            dummy -> myfriends.push_back(buff);
         }
      }
      dummy = dummy -> next;
   
   }
   input.close();
}


bool Network::remove(string fname, string lname){
   // We modified the definition of == for Connection in Connection definition itself, 
   // So we should not be worried about changes we made in Connection to modify this method!
   // Copy from lab5
   Connection* buff = head;
   Connection* dummy = search(fname,lname);
   
   if(dummy == NULL)
   {
      return false;
   }
   else
   {
      while(buff != NULL)
         {
            for(int i = 0; i < buff->myfriends.size(); i++) 
            {
               if(buff->myfriends[i] == dummy)
               {
                  counter.push_back(i);
               }
            }
            
            for(int j = 0; j < counter.size(); j++)
            {
               buff->myfriends.erase(buff->myfriends.begin()+counter[j]);
            }
            buff = buff->next;
            counter.clear();
         }
   }
   
   if((dummy->prev == NULL) && (dummy->next == NULL))
   {
      dummy = NULL;
      count--;
   }
   else if(dummy->prev == NULL)
   {
      dummy = search(fname,lname);
      dummy -> next -> prev = NULL;
      count--;
      delete dummy;
   }
   else if(dummy->next == NULL)
   {
      dummy->prev->next = NULL;
      count--;
      delete dummy;
   }      
   else
   {
      dummy->prev->next = dummy->next;
      dummy->next->prev = dummy->prev;
      count--;
      delete dummy;
   }
   
   
   
   return true;    
}


void Network::sendEmail(string addr, string subject, string content, string attachment=""){
   // Sending a command looks like:
   // echo "content" | mailx -s "subject" -a "attachment" addr;
   // TODO: Search how you can run a unix command in C++
   // TODO: You need to add double quotation character (") to both sides of strings for this command. Adding other characters (like ? in code below) should be easy, but double quotation says: I'm a character but not a typical character! 
   // string new_str = '?' + old_str + '?'
   // TODO: Complete this method
   subject = "\"" + subject + "\"";
   content = "\"" + content + "\"";
   attachment = "\"" + attachment + "\"";
   string command;
   command = "echo " + content + " | mailx -s " + subject + " -a" + attachment + " " + addr;
   cout << command << endl;
   system(command.c_str());   
}


void Network::showMenu(){
    // TODO: Complete this method!
    // All the prompts are given to you, 
    // You should add code before, between and after prompts!
   int opt;
   while(1){
      cout << "\033[2J\033[1;1H";
      printMe("banner"); // from misc library

      cout << "Select from below: \n";
      cout << "1. Save network database \n";
      cout << "2. Load network database \n";
      cout << "3. Add a new connection \n";
      cout << "4. Remove a connection \n";
      cout << "5. Search \n";
      cout << "6. Send an email \n";
      cout << "7. Send an iMessage \n";
      cout << "8. Print database \n";
      cout << "9. Connect \n";
      cout << "\nSelect an option ... ";
        
      if (cin >> opt) {
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      } else {
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         cout << "Wrong option! " << endl;
         return;
      }
        
      // You may need these variables! Add more if you want!
      string fname, lname, fileName, bdate;
      cout << "\033[2J\033[1;1H";

      if (opt==1){
         // TODO: Complete me!
         cout << "Saving network database \n";
         cout << "Enter the name of the save file: ";
         cin >> fileName;
         cout << "Network saved in " << fileName << endl;
         saveDB(fileName);
      }
      else if (opt==2){
         // TODO: Complete me!
         cout << "Loading network database \n";
         // TODO: print all the files in this same directory that have ".db" format
         // Take a look into sample_files.cpp 
         DIR *dir;
         int i = 0;
         int index = 0;
         string a[100];
         string filename;
         struct dirent *ent;
         char targetFolderAddr[] = "./";
         if ((dir = opendir ("./")) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
               if(strstr(ent->d_name,".db"))
               {
                  a[i] = ent->d_name;
                  i++;
                  cout << ent->d_name << endl;
               }
            }
            closedir (dir);
            }
            else {
               perror ("No directory!");
               break;
            }
            cout << "Enter the name of the load file: "; 
            cin >> filename;
            // If file with name FILENAME does not exist: 
            for(int x=0; x<i; x++)
            {
               if(filename == a[x])
               {
                  index = 1;
               }
            }
            if(index == 1)
            {
               loadDB(filename);
               cout << "Network loaded from " << fileName << " with " << count << " connections \n";            
            }
            else
            {
               cout << "File does not exist!" << endl;
            }
            // If file is loaded successfully, also print the count of connections in it: 
         }
      else if (opt == 3){
            // TODO: Complete me!
            // TODO: use push_front, and not push_back 
            // Add a new Connection ONLY if it does not exists!
            cout << "Adding a new connection \n";
            Connection *dummy = new Connection();
            
            if(search(dummy->f_name, dummy-> l_name))
            {
               cout << "Already exist" << endl;
            }
            else
            {
               push_front(dummy);
            }
             
         }
      else if (opt == 4){
         // TODO: Complete me!
         string fname, lname;
         cout << "Removing a connection \n";
         cout << "First name: ";
         getline(cin,fname);
         cout << "Last name: ";
         getline(cin,lname);
         if(remove(fname,lname))
         {
            cout << "Remove Successful" << endl;
         }
         else
         {
            cout << "Connection not found!" << endl;
         }
           
         // if found, cout << "Remove Successful! \n";
         // if not found: cout << "Connection not found! \n";
      }
      else if (opt==5){
         // TODO: Complete me!
         string fname, lname;
         cout << "Searching: \n";
         cout << "First Name: ";
         cin >> fname;
         cout << "Last Name: ";
         cin >> lname;
         Connection *dummy = search(fname,lname);
         if(dummy)
         {
            dummy -> print_connection();
         }
         else
         {
            cout << "Not found!" << endl;
         }
         
         // if found: print connection
         // if not, cout << "Not found! \n";
      }
      else if (opt==6){
         // Note: Completed!
         cout << "Sending email to: \n";
         cout << "First Name: ";
         std::getline (std::cin, fname);
         cout << "Last Name: ";
         std::getline (std::cin, lname);
         Connection* ptr = search(fname, lname);
         if (ptr){
            string subject, content, attachment;
            cout << "Sending email to: \n";
            ptr->print_connection();
            cout << "Subject: ";
            std::getline (std::cin, subject);
            cout << "Content: ";
            std::getline (std::cin, content);
            cout << "Attachment: ";
            std::getline (std::cin, attachment);
            string addr = ptr->email->get_contact("1");
            sendEmail(addr, subject, content, attachment);
         }
         else 
            cout << "Contact not found! \n";
      }
      else if (opt==7){
         cout << "Option currently not available\n";
      }
      else if (opt==8){
         // TODO: Complete me!
         cout << "Network Database: \n";
         printDB();
      }
      else if (opt==9){
         string fname, lname;
         cout << "Make friend: \n";
         cout << "Connection 1 \n";
         cout << "First Name: ";
         getline(cin,fname);
         cout << "Last Name: ";
         getline(cin,lname);
         Connection *dummy1 = search(fname,lname);
         if(dummy1)
         {
            cout << "Connection 2 \n";
            cout << "First Name: ";
            getline(cin,fname);
            cout << "Last Name: ";
            getline(cin,lname);
            Connection *dummy2 = search(fname,lname);
            if(dummy2)
            {
               dummy1 -> makeFriends(dummy2);
               dummy2 -> makeFriends(dummy1);
               
               cout << "Connected successfully" << endl;
               //dummy1 -> print_connection();
               //dummy2 -> print_connection();
            }
            else
            {
               cout << "No such person" << endl;
            }
         
         }
         else
         {
            cout << "No such person" << endl;
         }
      
      }
      else
         cout << "Nothing matched!\n";
        
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      cout << "\n\nPress Enter key to go back to main menu ... ";
      string temp;
      std::getline (std::cin, temp);
      cout << "\033[2J\033[1;1H";
   }
}


