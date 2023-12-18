#ifndef LOG
#define LOG
#include <memory>
#include <string>
#include "memory.h"
#include "mytype.h"
class Log{
    Userid id;
    int power;
    Mystring<400> command;
    public:
    Log ()=default;
    Log(Userid i,int p,string s)
    {
        id=i;
        power=p;
        command=s;
    }
    friend class LogData;
    bool operator<(const Log &b)const;
    bool operator>(const Log &b)const;
    bool operator==(const Log &b)const;
    bool operator<=(const Log &b)const;
    bool operator>=(const Log &b)const;
    bool operator!=(const Log &b)const;
};
class LogData{
    // int commandnum=0,billnum=0,crewnum=0;
    
    MyMemoryClass<int,std::pair<int,std::pair<int,int>>> basic;
    MyMemoryClass<int,Log> Logware;
    MyMemoryClass<int,std::pair<int,std::pair<double,double>>> sumw;
    MyMemoryClass<Userid,Log> crewperformance;
    MyMemoryClass<bool,Userid> crew;
    
    public:
    int Commandnum(){
        auto base=basic.find(0).front();
        return base.first;
    }
    int Billnum(){
        auto base=basic.find(0).front();
        return base.second.first;
    }
    // int crewnum(){
    //     auto base=basic.find(0).front();
    //     return base.second.second;
    // }
    //useless
    LogData()=default;
    LogData(const string &,bool is_new);
    std::pair<double,double> financesum(int count);
    void reportfinance(std::ostringstream &oss);
    void reportemployee(std::ostringstream &oss);
    void reportlog(std::ostringstream &oss);
    void addcrew(Userid);
    void delcrew(Userid);
    
    void addlog(int,Log);
    void chgbill(double val);
    
};


#endif