#ifndef ACCOUNTS
#define ACCOUNTS
#include <string>
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
};
class AccountData{
    MyMemoryClass<Userid,Account> Accountware;
    public:
    AccountData()=default;
    AccountData(const string &);
    Account quiry();
    void del(Userid);
    void update(Userid,Password);
    void adduser(Account);
};


#endif