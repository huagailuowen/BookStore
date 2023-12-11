#ifndef ACCOUNTS
#define ACCOUNTS
#include <string>
#include <any>

#include "memory.h"
#include "mytype.h"
class Account{
    Userid id;
    Username name;
    power_type power;
    Password passport;
    public:
    friend class MyMemoryClass<class Tkey, class Tvalue>;
    Account()=default;
    Account(Userid id,Username name,power_type power,Password passport);
    bool empty();
    bool getinto(const Password&,const int&);
    power_type privilege();
    Password pass();
    Userid user();
    Username nam();
    
};
class AccountData{
    MyMemoryClass<Userid,Account> Accountware;
    public:
    AccountData()=default;
    AccountData(const string &);
    Account quiry(quiry_type,std::any);
    //找不到返回userid="$"
    void del(Userid);
    void update(Userid,Password);
    void adduser(Account);
};


#endif