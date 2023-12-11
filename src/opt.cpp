#include "opt.h"
#include "accounts.h"
#include "log.h"
#include "mytype.h"
#include <iostream>
#include <sstream>
#include<string>
#include <utility>
using std::string;
extern AccountData Accountdata; 
extern LogData Logdata;
extern BookData Bookdata;
extern vector<std::pair<Userid, int>>userstack;
extern vector<MyISBN>theselected;
bool Readcommand()
{
    string command;
    std::ostringstream oss;
    int typ=-1;
    if(!getline(std::cin,command))return false;
    bool tmp=readcommand(command,oss,typ);
    if(!tmp){
        //ostream
        std::cout<<"Invalid\n";
    }else{
        //todo
        Logdata.addlog(typ,Log(userstack.back().first,command));
        string &&out=oss.str();
        if(out!=""&&typ!=(int)command_type::import){
            std::cout<<out;
        }
        if(typ==(int)command_type::buy){
            Logdata.chgbill(Logdata.Commandnum(), +stod(out));
        }else if(typ==(int)command_type::import){
            Logdata.chgbill(Logdata.Commandnum(), -stod(out));
        } 
    }
    
    return tmp;
}

bool readcommand(const string &command,std::ostringstream& oss,int &typ)
{
    string tmp;
    vector<string>list;
    for(auto s:command){
        if(s==' '){
            if(tmp!="")
                list.push_back(tmp);
            continue;
        }
        tmp+=s;
    }
    if(list.empty()){
        //ostream
        return true;
    }
    string opt=list[0];
    if(opt=="quit"){
        typ=(int)command_type::quit;
        //exit normally
        return false;
    }else if(opt=="exit"){
        typ=(int)command_type::exit;
        //exit normally
        return false;
    }else if(opt=="su"){
        typ=(int)command_type::su;
        return su(std::move(list), oss);
    }else if(opt=="logout"){
        typ=(int)command_type::logout;
        return logout(std::move(list), oss);
    }else if(opt=="register"){
        typ=(int)command_type::regi;
        return regi(std::move(list), oss);
    }else if(opt=="useradd"){
        typ=(int)command_type::useradd;
        return useradd(std::move(list), oss);
    }else if(opt=="delete"){
        typ=(int)command_type::del;
        return del(std::move(list), oss);
    }else if(opt=="show"&&(list.size()<=1||list[1]!="finance")){
        typ=(int)command_type::show;
        return show(std::move(list), oss);
    }else if(opt=="buy"){
        typ=(int)command_type::buy;
        return buy(std::move(list), oss);
    }else if(opt=="select"){
        typ=(int)command_type::select;
        return select(std::move(list), oss);
    }else if(opt=="modify"){
        typ=(int)command_type::modify;
        return modify(std::move(list), oss);
    }else if(opt=="import"){
        typ=(int)command_type::import;
        return import(std::move(list), oss);
    }else if(opt=="show"&&(list.size()>1&&list[1]=="finance")){
        typ=(int)command_type::showfinance;
        return showfinance(std::move(list), oss);
    }else if(opt=="log"){
        typ=(int)command_type::log;
        return log(std::move(list), oss);
    }else if(opt=="report"&&(list.size()>1&&list[1]=="finance")){
        typ=(int)command_type::reportfinance;
        return reportfinance(std::move(list), oss);
    }else if(opt=="report"&&(list.size()>1&&list[1]=="employee")){
        typ=(int)command_type::reportemployee;
        return reportemployee(std::move(list), oss);
    }
    return true;
}


//todo
bool su(vector<string>list,std::ostringstream &oss)
{
    if(list.size()>=3)return false;
    Userid Id;Password Pd("\"");
    if(list.size()<=1)return false;
    if(!Isuserid(list[1], Id))return false;
    if(list.size()==3){
        if(!Ispassword(list[2], Pd))
            return false;
    }
    Account theaccount=Accountdata.quiry(quiry_type::userid,Id);
    if(theaccount.empty())return false;
    if(!theaccount.getinto(Pd,userstack.back().second)){
        return false;
    }
    userstack.push_back(std::make_pair(theaccount.user() , (int)theaccount.privilege()));
    theselected.push_back(MyISBN(""));
    return true;
}
bool logout(vector<string>list,std::ostringstream &oss)
{
    if(userstack.size()==1)return false;
    userstack.pop_back();
    theselected.pop_back();
    return true;
}

bool regi(vector<string>list,std::ostringstream &oss)
{
    if(list.size()!=4)return false;
    Userid Id;Password Pd;Username Nam;
    if(!Isuserid(list[1], Id))return false;
    if(!Ispassword(list[2], Pd))return false;
    if(!Isusername(list[3], Nam))return false;
    Account tmp=Accountdata.quiry(quiry_type::userid, Id);
    if(!tmp.empty())return false;
    tmp=Account(Id,Nam,power_type::customer,Pd);
    Accountdata.adduser(tmp);
    return true;
}
bool passwd(vector<string>list,std::ostringstream &oss)
{
    Userid Id;Password Pd(""),newPd;
    if(list.size()<3||list.size()>4)return false;
    if(!Isuserid(list[1], Id))return false;
    if(!Ispassword(list.back(), newPd))return false;
    if(list.size()==4){
        if(!Ispassword(list[2], Pd))return false;
    }
    Account tmp=Accountdata.quiry(quiry_type::userid, Id);
    if(tmp.empty())return false;
    if((int)tmp.privilege()!=7&&tmp.pass()!=Pd)return false;
    tmp=Account(tmp.user(),tmp.nam(),tmp.privilege(),newPd);
    Accountdata.update(Id, newPd);
    return true;
}
bool useradd(vector<string>list,std::ostringstream &oss);
bool del(vector<string>list,std::ostringstream &oss);
bool show(vector<string>list,std::ostringstream &oss);
bool buy(vector<string>list,std::ostringstream &oss);
bool select(vector<string>list,std::ostringstream &oss);
bool modify(vector<string>list,std::ostringstream &oss);
bool import(vector<string>list,std::ostringstream &oss);
//记得输出总金额
bool showfinance(vector<string>list,std::ostringstream &oss);
bool log(vector<string>list,std::ostringstream &oss);
bool reportfinance(vector<string>list,std::ostringstream &oss);
bool reportemployee(vector<string>list,std::ostringstream &oss);
