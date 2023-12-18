#include <fstream>
#include <ios>
#include<iostream>
#include <string>
#include <utility>
#include <vector>
#include<set>
#include<map>

#include "memory.h"
#include "mytype.h"
#include "opt.h"
#include "books.h"
#include "accounts.h"
#include "log.h"

AccountData Accountdata; 
LogData Logdata;
BookData Bookdata;
vector<std::pair<Userid, int>>userstack;
vector<MyISBN>theselected;
std::map<Userid,int>st;
int TEST=0;
void init(std::string name="sjtu",bool is_new=0)
{
    Accountdata=AccountData(name+"Account",is_new);
    Logdata=LogData(name+"Log",is_new);
    
    // exit(0);
    Bookdata=BookData(name+"Bookdata",is_new);
    Accountdata.adduser(Account(Userid("root"),Username("root"),power_type::owner,Password("sjtu")));
    userstack.resize(1);
    userstack[0]=std::make_pair(Userid("#"), (int)power_type::none);
}
int main()
{
    // Mystring<20> a;
    // // Isuserid("390489349", a);
    // std::cout<<(string)a;
    init("sjtu");
    // Logdata.addlog(-1,Log(userstack.back().first,userstack.back().second,""));
    while(Readcommand());
    return 0;
}