#ifndef LOG
#define LOG
#include <string>
#include "memory.h"
#include "mytype.h"
class Log{
    Userid id;
    Mystring<200> command;
    public:
    Log ()=default;
    Log(Userid i,string s)
    {
        id=i;
        command=s;
    }
};
class LogData{
    int commandnum=0,billnum=0;
    MyMemoryClass<int,Log> Logware;
    MyMemoryClass<int,std::pair<int,std::pair<double,double>>> sumw;
    MyMemoryClass<Userid,Log> crewperformance;
    public:
    int Commandnum(){return commandnum;}
    int Billnum(){return billnum;}
    LogData()=default;
    LogData(string &);
    std::pair<double,double> financesum(int count=-1);
    void reportfinance();
    void reportemployee();
    void addlog(int,Log);
    void chgbill(int comnum,double val);
    
};


#endif