#include<iostream>
#include <utility>
#include <vector>
#include<set>
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
std::set<Userid>st;
void init(std::string name="sjtu")
{
    Accountdata=AccountData(name);
    Logdata=LogData(name);
    Bookdata=BookData(name);
    Accountdata.adduser(Account(Userid("root"),Username("root"),power_type::owner,Password("sjtu")));
    userstack.resize(1);
    userstack[0]=std::make_pair(Userid(""), (int)power_type::none);
}
int main()
{
    // Mystring<20> a;
    // // Isuserid("390489349", a);
    // std::cout<<(string)a;
    init();
    while(Readcommand());
    return 0;
}