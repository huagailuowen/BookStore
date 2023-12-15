#include"books.h"
#include"memory.h"
#include"mytype.h"
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
std::ostream& operator<<(std::ostream&out,const Book&the)
{
    out<<the.ISBN<<'\t'<<the.name<<'\t';
    out<<the.author<<'\t'<<the.keyword<<'\t';
    out<<std::setprecision(2)<<the.price<<'\t'<<the.num;
    return out;
}
Book::Book(Bookname name_,MyISBN ISBN_,Myauthor author_,
    Keyword keyword_,double price_,int num_)
:name(name_),ISBN(ISBN_),author(author_),keyword(keyword_),price(price_),num(num_){}


BookData::BookData(std::string &name)
{
    this->bookware.initialise(name+"_bookware");
    this->ISBN_ISBN.initialise(name+"_ISBN_ISBN");
    this->name_ISBN.initialise(name+"_name_ISBN");
    this->author_ISBN.initialise(name+"_author_ISBN");
    this->keyword_ISBN.initialise(name+"_keyword_ISBN");
}
std::vector<int>BookData::quirybook_ISBN(quiry_type typ,string s)
{
    vector<int>res;
    if(typ==quiry_type::All){
        res=ISBN_ISBN.findsegment(Mystring<20>(""),std::to_string(char(127)));
        return res;
    }else if(typ==quiry_type::name){
        res=this->name_ISBN.find(s);
        return res;
    }else if(typ==quiry_type::ISBN){
        res=this->ISBN_ISBN.find(s);
        return res;
    }else if(typ==quiry_type::author){
        res=this->author_ISBN.find(s);
        return res;
    }else if(typ==quiry_type::keyword){
        res=this->keyword_ISBN.find(s);
        res.erase(std::unique(res.begin(), res.end()), res.end());
        return res;
    }
    return res;
}
std::vector<Book>BookData::quirybook(quiry_type typ,string s)
{
    vector<int>res;
    if(typ==quiry_type::All){
        res=ISBN_ISBN.findsegment(Mystring<20>(""),std::to_string(char(127)));
    }else if(typ==quiry_type::name){
        res=this->name_ISBN.find(s);
    }else if(typ==quiry_type::ISBN){
        res=this->ISBN_ISBN.find(s);
    }else if(typ==quiry_type::author){
        res=this->author_ISBN.find(s);
    }else if(typ==quiry_type::keyword){
        res=this->keyword_ISBN.find(s);
        res.erase(std::unique(res.begin(), res.end()), res.end());
    }
    vector<Book>Res;
    for(auto r:res){
        Res.push_back(this->bookware.find(r).front());
    }
    //GG可以加速，上面很慢
    return Res;
}
// std::any BookData::quirybookdetails(quiry_type,MyISBN)
// {
    
// }
void BookData::addbook(Book the)
{
    
    int t=bookware.chgaddtimes();

    bookware.insert(t, the);
    ISBN_ISBN.insert(the.ISBN, t);
    name_ISBN.insert(the.name, t);
    author_ISBN.insert(the.author, t);

    vector<string>list;
    Getkeywordlist(the.keyword, list);
    for(auto s:list){
        keyword_ISBN.insert(s, t);
    }
}
void BookData::modifybook(Book old,Book the)
{
    int t=ISBN_ISBN.find(old.ISBN).front();
    bookware.del(t, the);
    ISBN_ISBN.del(old.ISBN, t);
    name_ISBN.del(old.name, t);
    author_ISBN.del(old.author, t);

    vector<string>list;
    Getkeywordlist(old.keyword, list);
    for(auto s:list){
        keyword_ISBN.del(s, t);
    }

    //add
    bookware.insert(t, the);
    ISBN_ISBN.insert(the.ISBN, t);
    name_ISBN.insert(the.name, t);
    author_ISBN.insert(the.author, t);

    // vector<string>list;
    Getkeywordlist(the.keyword, list);
    for(auto s:list){
        keyword_ISBN.insert(s, t);
    }
}