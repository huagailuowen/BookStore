#include"accounts.h"
#include "mytype.h"
#include <any>
#include <vector>
// #include "mytype.h"
Account::Account(Userid id_,Username name_,power_type power_,Password password_)
:id(id_),name(name_),power(power_),password(password_){}
bool Account::empty()
{
    return (id==Mystring<20>("#"));
}
bool Account::getinto(const Password&thepassword,const int&thepower)
{
    if((int)power<(int)thepower)return true;
    if(password!=thepassword)return false;
    return true;
}
power_type Account::privilege()
{
    return power;
}
Password Account::pass()
{
    return password;
}
Userid Account::user()
{
    return id;
}
Username Account::nam()
{
    return name;
}
AccountData::AccountData(const string &s)
{
    this->Accountware.initialise(s+"_Accountware");
}
Account AccountData::quiry(quiry_type typ,std::any the)
{
    auto pid=std::any_cast<Userid>(&the);
    Account res;
    res.id=Userid("#");
    if(typ==quiry_type::userid){
        auto tmp=
        Accountware.find(*pid);
        if(tmp.empty())
            return res;
        else 
            return tmp.front();
    }
    return res;
}
void AccountData::del(Userid id)
{
    Accountware.del(id);
}
void AccountData::update(Userid id,Password pd)
{
    auto tmp=Accountware.find(id);
    if(tmp.empty()){
        throw("???");
        return ;
    }
    Account the=tmp.front();
    Accountware.del(id);
    the.password=pd;
    Accountware.insert(the.id,the);
}
void AccountData::adduser(Account the)
{
    Accountware.insert(the.id,the);
}