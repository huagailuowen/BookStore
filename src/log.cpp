#include "log.h"
#include "mytype.h"
#include <utility>
#include <vector>
#include <iostream>
LogData::LogData(string &s)
{
    Logware.initialise(s+"_Logware");
    sumw.initialise(s+"_sumw");
    crewperformance.initialise(s+"_crewperformance");
}
std::pair<double,double> LogData::financesum(int count)
{
    std::vector<std::pair<int,std::pair<double,double>>>res=sumw.findsegment(billnum-count+1, billnum);
    double add=0,minus=0;
    for(auto v:res){
        add+=v.second.first;
        minus+=v.second.second;
    }
    return std::make_pair(add,minus);
}
void LogData::addlog(int typ,Log log)
{
    ++commandnum;
    Logware.insert(commandnum, log);
    if(log.power!=(int)power_type::crew)
        return;
    crewperformance.insert(log.id, log);
}
void LogData::chgbill(double val)
{
    if(val>0){
        billnum++;
        //小心  commandnum更新？？？
        sumw.insert(billnum, std::make_pair(commandnum,std::make_pair(val,0)));
    }else{
        billnum++;
        //小心  commandnum更新？？？
        sumw.insert(billnum, std::make_pair(commandnum,std::make_pair(0,-val)));
    }
    //不为0
}
void LogData::reportfinance(std::ostringstream &oss)
{
    std::vector<std::pair<int,std::pair<double,double>>> list=sumw.findsegment(0, 1000000000);
    int cnt=0;
    for(auto u:list){
        oss<<'\t';
    }
}
    void reportemployee(std::ostringstream &oss);
    void reportlog(std::ostringstream &oss);
    