#ifndef MYTYPE
#define MYTYPE
#include <string>
#include "memory.h"
using std::string;
class AccountData;
class BookData;
enum class quiry_type { All,ISBN , name , author , keyword  };
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
