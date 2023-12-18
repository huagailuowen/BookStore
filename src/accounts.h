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
    Password password;
    public:
    friend class MyMemoryClass<class Tkey, class Tvalue>;
    friend class AccountData;
    Account()=default;
    Account(Userid id_,Username name_,power_type power_,Password password_);
    bool empty();
    bool getinto(const Password&,const int&);
    power_type privilege();
    Password pass();
    Userid user();
    Username nam();
    bool operator<(const Account &b)const;
    bool operator>(const Account &b)const;
    bool operator==(const Account &b)const;
    bool operator<=(const Account &b)const;
    bool operator>=(const Account &b)const;
    bool operator!=(const Account &b)const;
};
class AccountData{
    public:
    friend void init(std::string);
    MyMemoryClass<Userid,Account> Accountware;
    public:
    AccountData()=default;
    AccountData(const string &,bool is_new);
    Account quiry(quiry_type,std::any);
    //找不到返回userid="#
    void del(Userid);
    void update(Userid,Password);
    void adduser(Account);
};


#endif