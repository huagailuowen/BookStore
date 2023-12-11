#ifndef MYTYPE
#define MYTYPE
#include <string>
#include <vector>
#include "memory.h"
using std::string;
class AccountData;
class BookData;
enum class quiry_type { All/*共有*/,ISBN , name , author , keyword ,userid,username };
enum class power_type { none=0,customer=1,crew=3, owner=7 };

enum class command_type {
quit,
exit,
su,
logout,
regi,
passwd,
useradd,
del,
show,
buy,
select,
modify,
import,
showfinance,
log,
reportfinance,
reportemployee
};

template <const int len> struct Mystring {
    private:
  unsigned long long myhash = 0;
  char c[len + 1];
  int l = 0;
  public:
  Mystring();
  Mystring(string s);
  operator string();
  string tostr();
  void gethash();
  int size()const;
  char& operator[](const int &index);
  char operator[](const int &index)const;
  
  bool operator<(Mystring &b);
  bool operator==(Mystring &b);
  bool operator>(Mystring &b);
  bool operator>=(Mystring &b);
  bool operator<=(Mystring &b);
  bool operator!=(Mystring &b);
  friend class AccountData;
  friend class BookData;
  template<class Tkey,class Tvalue>
  friend class MyMemoryClass;
};
using MyISBN = Mystring<20>;
using Userid = Mystring<20>;
using Myauthor = Mystring<60>;
using Bookname = Mystring<60>;
using Username = Mystring<30>;
using Password = Mystring<30>;
using Keyword = Mystring<60>;
bool IsISBN(const string &s,MyISBN&);
bool Isuserid(const string &s,Userid&);
bool Isauthor(const string &s,Myauthor&);
bool Isbookname(const string &s,Bookname &);
bool Isusername(const string &s,Username &);

bool Ispassword(const string &s,Password&);
bool Iskeyword(const string &s,Keyword&);
void Getkeywordlist(const Keyword&,std::vector<string>&);

// struct MyISBN{

//     MyISBN();
//     MyISBN(string s);
//     string tostr();
//     bool operator<(MyISBN &b);
//     bool operator==(MyISBN &b);
//     bool operator>(MyISBN &b);
//     bool operator>=(MyISBN &b);
//     bool operator<=(MyISBN &b);
//     bool operator!=(MyISBN &b);
// };
#endif
