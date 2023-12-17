#include "opt.h"
#include "accounts.h"
#include "books.h"
#include "log.h"
#include "mytype.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include<string>
#include<set>
#include <utility>
using std::string;
extern AccountData Accountdata; 
extern LogData Logdata;
extern BookData Bookdata;
extern vector<std::pair<Userid, int>>userstack;
extern vector<int>theselected;
extern std::set<Userid>st;
bool Readcommand()
{
    string command;     
    std::ostringstream oss;
    int typ=-1;
    if(!getline(std::cin,command))return false;
    // bool tmp=1;
    bool tmp=readcommand(command,oss,typ);
    // std::cerr<<tmp<<'\n';
    if(!tmp){
        //ostream
        std::cout<<"Invalid\n";
        return true;
    }else{
        //todo
        Logdata.addlog(typ,Log(userstack.back().first,userstack.back().second,command));
        string out=oss.str();
        if(out!=""&&typ!=(int)command_type::import){
            std::cout<<out;
        }
        if(typ==(int)command_type::buy){
            Logdata.chgbill(+stod(out));
        }else if(typ==(int)command_type::import){
            Logdata.chgbill(-stod(out));
        } 
    }
    if(typ==(int)command_type::exit||typ==(int)command_type::quit)
        return false;
    return true;
}

bool readcommand(const string &command,std::ostringstream& oss,int &typ)
{
    string tmp;
    vector<string>list;
    for(auto s:command){
        if(s==' '){
            if(tmp!="")
                list.push_back(tmp);
            tmp="";
            continue;
        }
        tmp+=s;
    }
    if(tmp!="")list.push_back(tmp);
    tmp="";
    if(list.empty()){
        //ostream
        return true;
    }
    // for(auto i:list)std::cerr<<i<<' ';

    std::cerr<<'\n';
    // exit(0);
    string opt=list[0];
    if(opt=="quit"){
        if(list.size()!=1)return false;
        typ=(int)command_type::quit;
        //exit normally
        return true;
    }else if(opt=="exit"){
        if(list.size()!=1)return false;
        typ=(int)command_type::exit;
        //exit normally
        return true;
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
    return false;
}


//todo
bool su(vector<string>list,std::ostringstream &oss)
{
    if(list.size()>3)return false;
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
    theselected.push_back(-1);
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
bool useradd(vector<string>list,std::ostringstream &oss)
{
    if(list.size()!=5)return false;
    if(userstack.back().second<3)return false;
    Userid Id;Password Pd;Username Nam;power_type pri;
    if(!Isuserid(list[1], Id))return false;
    if(!Ispassword(list[2], Pd))return false;
    if(!Isprivilege(list[3], pri))return false;
    if(!Isusername(list[4], Nam))return false;

    
    if(userstack.back().second<=(int)pri)return false;
    Account tmp=Accountdata.quiry(quiry_type::userid, Id);
    if(!tmp.empty())return false;

    tmp=Account(Id,Nam,pri,Pd);
    Accountdata.adduser(tmp);
    if(pri==power_type::crew){
        Logdata.addcrew(Id);
    }
    return true;
}
bool del(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<7)return false;
    if(list.size()!=2)return false;
    Userid Id;
    if(!Isuserid(list[1], Id))return false;

    Account tmp=Accountdata.quiry(quiry_type::userid, Id);
    if(tmp.empty())return false;
    if(st.find(Id)!=st.end())return false;
    Accountdata.del(Id);
    if(tmp.privilege()==power_type::crew){
        Logdata.delcrew(Id);
    }
    return true;
}
bool show(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<1)return false;
    if(list.size()>2)return false;
    if(list.size()==1){
        vector<Book>res=Bookdata.quirybook(quiry_type::All,"");
        for(auto v:res){
            oss<<v<<'\n';
        }
        return true;
    }else{
        if(list[1].size()>=6&&list[1].substr(0,6)=="-ISBN="){
            list[1]=list[1].substr(6,list[1].size());
            if(list[1].size()==0)return false;
            
            vector<Book>res=Bookdata.quirybook(quiry_type::ISBN, list[1]);
            for(auto v:res){
                oss<<v<<'\n';
            }
            return true;
        }else if(list[1].size()>=8&&list[1].substr(0,6)=="-name="){
            if(list[1][6]!='\"'||list[1].back()!='\"')return false;
            list[1]=list[1].substr(7,list[1].size()-1);
            if(list[1].size()==0)return false;
            Bookname chk;
            if(!Isbookname(list[1], chk))return false;
            vector<Book>res=Bookdata.quirybook(quiry_type::name, list[1]);
            // auto u=res.begin();
            // oss<<*u;
            // while((++u)!=res.end()){
            //     oss<<'\n'<<*u;
            // }
            for(auto v:res){
                oss<<v<<'\n';
            }
            return true;
        }else if(list[1].size()>=10&&list[1].substr(0,8)=="-author="){
            if(list[1][8]!='\"'||list[1].back()!='\"')return false;
            list[1]=list[1].substr(9,list[1].size()-1);
            if(list[1].size()==0)return false;
            Myauthor chk;
            if(!Isauthor(list[1], chk))return false;
            vector<Book>res=Bookdata.quirybook(quiry_type::author, list[1]);
            for(auto v:res){
                oss<<v<<'\n';
            }
            return true;
        } else if(list[1].size()>=11&&list[1].substr(0,9)=="-keyword="){
            if(list[1][9]!='\"'||list[1].back()!='\"')return false;
            list[1]=list[1].substr(10,list[1].size()-1);
            if(list[1].size()==0)return false;
            Keyword chk;
            if(!Iskeyword(list[1], chk,true))return false;
            vector<Book>res=Bookdata.quirybook(quiry_type::keyword, list[1]);
            for(auto v:res){
                oss<<v<<'\n';
            }
            return true;
        } 
    }
    return false; 
}
bool buy(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<1)return false;
    if(list.size()!=3)return false;
    MyISBN ISBN;
    int quantity;
    if(!IsISBN(list[1],ISBN))return false;
    if(!Isquantity(list[2],quantity))return false;
    if(quantity==0)return false;
    vector<Book>res=Bookdata.quirybook(quiry_type::ISBN,list[1]);
    if(res.empty())return false;
    // std::cerr<<"]]]";
    if(res.front().num<quantity)return false;
    Book newbook=res.front();
    newbook.num-=quantity;
    Bookdata.modifybook(res.front(), newbook);
    oss.setf(std::ios::fixed);                    
    oss<<std::setprecision(2)<<newbook.price*quantity<<'\n';
    oss.unsetf(std::ios::fixed);  
    return true;
}
bool select(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<3)return false;
    if(list.size()!=2)return false;
    MyISBN ISBN;
    if(!IsISBN(list[1], ISBN))return false;
    vector<Book>res=Bookdata.quirybook(quiry_type::ISBN,list[1]);
    if(res.empty()){
        Book tmp;
        tmp.ISBN=ISBN;
        Bookdata.addbook(tmp);
        res.push_back(tmp);
    }
    theselected.back()=Bookdata.quirybook_ISBN(quiry_type::ISBN,ISBN).front();
    return true;
}

bool modify(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<3)return false;
    if(theselected.back()==-1)return false;
    if(list.size()==1){
        return false;
    }
    
    Book the=Bookdata.quirybook(quiry_type::realISBN, std::to_string(theselected.back())).front();
    Book old=the;
    bool flag[9]={0,0,0,0,0,0,0,0,0};
    for(int i=1;i<list.size();i++){

        if(list[i].size()>=6&&list[i].substr(0,6)=="-ISBN="){
            if(flag[(int)quiry_type::ISBN])return false;
            flag[(int)quiry_type::ISBN]=true;
            list[i]=list[i].substr(6,list.size());

            if(list[i].size()==0)return false;
            MyISBN chk;
            if(!IsISBN(list[i], chk))return false;
            if(old.ISBN==chk)return false;
            the.ISBN=MyISBN(list[i]);
            continue;

        }else if(list[i].size()>=8&&list[i].substr(0,6)=="-name="){
            if(flag[(int)quiry_type::name])return false;
            flag[(int)quiry_type::name]=true;
            if(list[i][6]!='\"'||list[i].back()!='\"')return false;
            list[i]=list[i].substr(7,list.size()-1);
            if(list[i].size()==0)return false;
            Bookname chk;
            if(!Isbookname(list[i], chk))return false;
            the.name=Bookname(list[i]);
            continue;

        }else if(list[i].size()>=10&&list[i].substr(0,8)=="-author="){
            if(flag[(int)quiry_type::author])return false;
            flag[(int)quiry_type::author]=true;
            if(list[i][8]!='\"'||list[i].back()!='\"')return false;
            list[i]=list[i].substr(9,list.size()-1);
            if(list[i].size()==0)return false;
            Myauthor chk;
            if(!Isauthor(list[i], chk))return false;
            the.author=Myauthor(list[i]);
            continue;

        } else if(list[i].size()>=11&&list[i].substr(0,9)=="-keyword="){
            if(flag[(int)quiry_type::keyword])return false;
            flag[(int)quiry_type::keyword]=true;
            if(list[i][9]!='\"'||list[i].back()!='\"')return false;
            list[i]=list[i].substr(10,list.size()-1);
            if(list[i].size()==0)return false;
            Keyword chk;
            if(!Iskeyword(list[i], chk))return false;
            the.keyword=Keyword(list[i]);
            continue;
            
        } else if(list[i].size()>=7&&list[i].substr(0,7)=="-price="){
            if(flag[(int)quiry_type::price])return false;
            flag[(int)quiry_type::price]=true;
            list[i]=list[i].substr(7,list.size());
            if(list[i].size()==0)return false;
            double chk;
            if(!Isprice(list[i], chk))return false;
            the.price=chk;
            continue;

        } 
        return false;
    }
    Bookdata.modifybook(old, the);
    return true;
    
}
bool import(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<3)return false;
    if(theselected.back()==-1)return false;
    int quantity;double totalcost=0;
    if(list.size()!=3)return false;
    if(!Isquantity(list[1],quantity))return false;
    if(!Isprice(list[2],totalcost))return false;
    if(quantity<0)return false;
    if(totalcost<0)return false;
    
    vector<Book>res=Bookdata.quirybook(quiry_type::realISBN,std::to_string(theselected.back()));
    Book newbook=res.front();
    newbook.num+=quantity;
    Bookdata.modifybook(res.front(), newbook);
    oss.setf(std::ios::fixed);                    
    oss<<std::setprecision(2)<<totalcost<<'\n';
    oss.unsetf(std::ios::fixed);  
    return true;
}
//记得输出总金额
bool showfinance(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<7)return false;
    if(list.size()>3)return false;
    int count=Logdata.Billnum();
    if(list.size()==3){
        if(!Isquantity(list[2], count))return false;
    }
    if(count>Logdata.Billnum())return false;
    auto res=Logdata.financesum(count);
    if(count==0)oss<<'\n';
    else{
        oss.setf(std::ios::fixed);                    
        oss<<"+ "<<std::setprecision(2)<<res.first<<" - "<<std::setprecision(2)<<res.second<<'\n';
        oss.unsetf(std::ios::fixed);   
    }
    return true;
}
bool log(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<7)return false;
    if(list.size()>1)return false;   
    Logdata.reportlog(oss);
    return true;
}
bool reportfinance(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<7)return false;
    if(list.size()>2)return false;   
    Logdata.reportfinance(oss);
    return true;
}
bool reportemployee(vector<string>list,std::ostringstream &oss)
{
    if(userstack.back().second<7)return false;
    if(list.size()>2)return false;   
    Logdata.reportemployee(oss);
    return true;
}
