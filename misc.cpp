
#include "misc.h"

void printMe(string type){
    if (type == "banner"){
        char banner[] = \
"   ######## ########   #######        ##    ###    ##    ##         ########   #######   #######  ##    ## \n \
     ##    ##     ## ##     ##       ##   ## ##   ###   ##         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ## ##     ##       ##  ##   ##  ####  ##         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ########  ##     ##       ## ##     ## ## ## ## ####### ########  ##     ## ##     ## ##### \n \
     ##    ##   ##   ##     ## ##    ## ######### ##  ####         ##     ## ##     ## ##     ## ##  ## \n \
     ##    ##    ##  ##     ## ##    ## ##     ## ##   ###         ##     ## ##     ## ##     ## ##   ## \n \
     ##    ##     ##  #######   ######  ##     ## ##    ##         ########   #######   #######  ##    ##\n";
        cout << endl << banner << endl << endl;
    }
}


string codeName(string str1, string str2)
{
   string temp = str1 + str2;
   string code;
   size_t found;
   size_t len;
   
   len = temp.length();
   found = temp.find(" ");
   
   if(temp.find(" ") !=  std::string::npos)
   {  
      code = temp.substr(0,found) + temp.substr((found+1),(len-found-1));
   }
   else
   {
      code = temp;
   }
   for(int i=0; i < code.length(); i++)
   {
      code[i] = tolower(code[i]);
   }
   
   return code;
}
