#ifndef OPT
#define OPT
#include "books.h"
#include "accounts.h"
#include <iostream>
#include <string>
bool su(vector<string>list,std::ostringstream &oss);
bool logout(vector<string>list,std::ostringstream &oss);
bool regi(vector<string>list,std::ostringstream &oss);
bool passwd(vector<string>list,std::ostringstream &oss);
bool useradd(vector<string>list,std::ostringstream &oss);
bool del(vector<string>list,std::ostringstream &oss);
bool show(vector<string>list,std::ostringstream &oss);
bool buy(vector<string>list,std::ostringstream &oss);
bool select(vector<string>list,std::ostringstream &oss);
bool modify(vector<string>list,std::ostringstream &oss);
bool import(vector<string>list,std::ostringstream &oss);
bool showfinance(vector<string>list,std::ostringstream &oss);
bool log(vector<string>list,std::ostringstream &oss);
bool reportfinance(vector<string>list,std::ostringstream &oss);
bool reportemployee(vector<string>list,std::ostringstream &oss);
bool readcommand(string &command,std::ostringstream& oss,int &typ);
bool Readcommand();


// void 
#endif