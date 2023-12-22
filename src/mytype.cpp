

#include "mytype.h"
#include <algorithm>
#include <cmath>
#include <string>

bool IsISBN(const string &s, MyISBN &the) {
  if (s.size() > 20)
    return false;
  for (auto c : s) {
    if ((c >= 0 && c <= 32 || c == 127))
      return false;
  }
  the = std::move(MyISBN(s));
  return true;
}
bool Isuserid(const string &s, Userid &the) {
  if (s.size() > 30)
    return false;
  for (auto c : s) {
    if (!(c >= '0' && c <= '9' || c == '_' || c >= 'a' && c <= 'z' ||
          c >= 'A' && c <= 'Z'))
      return false;
  }
  the = std::move(Userid(s));
  return true;
}
bool Isauthor(const string &s, Myauthor &the) {
  if (s.size() > 60)
    return false;
  for (auto c : s) {
    if ((c >= 0 && c <= 32 || c == 127 || c == '\"'))
      return false;
  }
  the = std::move(Myauthor(s));
  return true;
}
bool Isbookname(const string &s, Bookname &the) {
  if (s.size() > 60)
    return false;
  for (auto c : s) {
    if ((c >= 0 && c <= 32 || c == 127 || c == '\"'))
      return false;
  }
  the = std::move(Bookname(s));
  return true;
}
bool Isusername(const string &s, Username &the) {
  if (s.size() > 30)
    return false;
  for (auto c : s) {
    if ((c >= 0 && c <= 32 || c == 127))
      return false;
  }
  the = std::move(Username(s));
  return true;
}
bool Ispassword(const string &s, Password &the) {
  if (s.size() > 30)
    return false;
  for (auto c : s) {
    if (!(c >= '0' && c <= '9' || c == '_' || c >= 'a' && c <= 'z' ||
          c >= 'A' && c <= 'Z'))
      return false;
  }
  the = std::move(Password(s));
  return true;
}
bool Iskeyword(const string &s, Keyword &the, bool one) {
  // if(s.size()==0)return false;
  //????
  std::set<string> st;
  if (s.size() > 60)
    return false;
  char las = '|';
  string tmp = "";
  for (auto c : s) {
    if ((c >= 0 && c <= 32 || c == 127 || c == '\"'))
      return false;
    if (c == '|' && las == '|')
      return false;
    las = c;
    if (c == '|') {
      if (st.find(tmp) != st.end())
        return false;
      st.insert(tmp);
      tmp = "";
    } else
      tmp += c;
    if (c == '|' && one)
      return false;
  }
  if (las == '|')
    return false;
  if (st.find(tmp) != st.end())
    return false;
  the = std::move(Keyword(s));
  return true;
}
void Getkeywordlist(const Keyword &the, std::vector<string> &list) {
  list.clear();
  string tmp = "";
  for (int i = 0; i < the.size(); i++) {
    if (the[i] == '|')
      list.push_back(std::move(tmp)), tmp = "";
    else
      tmp += the[i];
  }
  if (tmp != "")
    list.push_back(std::move(tmp)), tmp = "";
  std::sort(list.begin(), list.end());
}
bool Isprivilege(const string &s, power_type &a) {
  if (s.size() != 1)
    return false;
  switch (s[0]) {
  case '1':
    a = power_type::customer;
    return true;
  case '3':
    a = power_type::crew;
    return true;
  case '7':
    a = power_type::owner;
    return true;
  }
  return false;
}
bool Isquantity(const string &s, long long &the) {
  if (s.size() > 10 || s.empty())
    return false;
  long long res = 0;
  for (auto c : s) {
    if (c < '0' || c > '9')
      return false;
    res = res * 10 + c - '0';
  }
  if (res > 2147483647)
    return false;
  the = res;
  return true;
}

bool Isprice(const string &s, double &the) {
  if (s.size() > 13 || s.empty())
    return false;
  double res = 0;
  int pos = -1;
  if (s.front() == '.' || s.back() == '.')
    return false;
  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (c == '.') {
      if (pos >= 0)
        return false;
      pos = i;
      continue;
    }
    if (c < '0' || c > '9')
      return false;
  }
  // 两位？？
  if (s.size() > pos + 3)
    s.substr(0, pos + 3);
  the = std::stod(s);
  if (s.size() > pos + 3 && s[pos + 3] > '4')
    the += 0.01;
  return true;
}