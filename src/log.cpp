#include "log.h"
#include "mytype.h"
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
bool Log::operator<(const Log &b) const { return id < b.id; }
bool Log::operator>(const Log &b) const { return id > b.id; }
bool Log::operator==(const Log &b) const { return id == b.id; }
bool Log::operator<=(const Log &b) const { return id <= b.id; }
bool Log::operator>=(const Log &b) const { return id >= b.id; }
bool Log::operator!=(const Log &b) const { return id != b.id; }
LogData::LogData(const string &s, bool is_new) {
  Logware.initialise(s + "_Logware", is_new);
  sumw.initialise(s + "_sumw", is_new);
  crewperformance.initialise(s + "_crewperformance", is_new);
  crew.initialise(s + "_crew", is_new);
  basic.initialise(s + "_basic", is_new);

  // basic.insert(0,std::make_pair(0,std::make_pair(0,0)));
  //     std::cerr<<'{'<<basic.find(0).size()<<'}';

  if (basic.find(0).empty()) {
    basic.insert(0, std::make_pair(0, std::make_pair(0, 0)));
  }
}
std::pair<double, double> LogData::financesum(int count) {
  auto base = basic.find(0).front();
  std::vector<std::pair<int, std::pair<double, double>>> res =
      sumw.findsegment(base.second.first - count + 1, base.second.first);
  double add = 0, minus = 0;
  for (auto v : res) {
    add += v.second.first;
    minus += v.second.second;
  }
  basic.del(0);
  basic.insert(0, base);
  return std::make_pair(add, minus);
}
void LogData::addcrew(Userid id) { crew.insert(1, id); }
void LogData::delcrew(Userid id) { crew.del(1, id); }

void LogData::addlog(int typ, Log log) {
  auto base = basic.find(0).front();
  ++base.first;
  Logware.insert(base.first, log);
  basic.del(0);
  basic.insert(0, base);
  if (log.power != (int)power_type::crew)
    return;
  crewperformance.insert(log.id, log);
}
void LogData::chgbill(double val) {
  auto base = basic.find(0).front();
  if (val > 0) {
    base.second.first++;
    // 小心  base.first更新？？？
    sumw.insert(base.second.first,
                std::make_pair(base.first, std::make_pair(val, 0)));
  } else {
    // 0只可能是 buy
    base.second.first++;
    // 小心  base.first更新？？？
    sumw.insert(base.second.first,
                std::make_pair(base.first, std::make_pair(0, -val)));
  }
  basic.del(0);
  basic.insert(0, base);
  // 不为0
}
void LogData::reportfinance(std::ostringstream &oss) {
  std::vector<std::pair<int, std::pair<double, double>>> list =
      sumw.findsegment(0, 1000000000);
  int cnt = 0;
  for (auto u : list) {
    oss << "line:" << ++cnt << '\t' << " | "
        << "command:" << u.first << '\t' << " | ";
    oss << std::fixed << std::setprecision(2)
        << (u.second.first > 0 ? u.second.first : -u.second.second) << '\n';
  }
}
void LogData::reportemployee(std::ostringstream &oss) {
  std::vector<Userid> crewlist = crew.findsegment(0, 1);
  for (auto u : crewlist) {
    oss << "crew:" << u << ":\n";
    auto performancelist = crewperformance.find(u);
    for (auto v : performancelist) {
      oss << v.command << '\n';
    }
  }
}
void LogData::reportlog(std::ostringstream &oss) {
  auto list = Logware.findsegment(0, 1000000000);
  for (auto v : list) {
    oss << "User:" << v.id << '\t' << "command:" << v.command << '\n';
  }
}
