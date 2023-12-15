#ifndef LOG
#define LOG
#include <memory>
#include <string>
#include "memory.h"
#include "mytype.h"
class Log{
    Userid id;
    int power;
    Mystring<200> command;
    public:
    Log ()=default;
    Log(Userid i,int p,string s)
    {
        id=i;
        power=p;
        command=s;
    }
    friend class LogData;
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
    std::pair<double,double> financesum(int count);
    void reportfinance(std::ostringstream &oss);
    void reportemployee(std::ostringstream &oss);
    void reportlog(std::ostringstream &oss);
    
    void addlog(int,Log);
    void chgbill(double val);
    
};


#endif