#include"books.h"
#include"memory.h"
#include"mytype.h"
#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
extern int TEST;
bool Book::operator<(const Book &b)const
{
    return realISBN<b.realISBN;
}
bool Book::cp(const Book &b)const
{
    return ISBN<b.ISBN;
}

bool Book::operator>(const Book &b)const
{
    return realISBN>b.realISBN;
}
bool Book::operator==(const Book &b)const
{
    return realISBN==b.realISBN;
}
bool Book::operator<=(const Book &b)const
{
    return realISBN<=b.realISBN;
}
bool Book::operator>=(const Book &b)const
{
    return realISBN>=b.realISBN;
}
bool Book::operator!=(const Book &b)const
{
    return realISBN!=b.realISBN;
}
    
std::ostream& operator<<(std::ostream&out,const Book&the)
{
    out<<the.ISBN<<'\t'<<the.name<<'\t';
    out<<the.author<<'\t'<<the.keyword<<'\t';
    out<<std::fixed<<std::setprecision(2)<<the.price<<'\t'<<the.num;
    return out;
}
Book::Book(Bookname name_,MyISBN ISBN_,int realISBN_,Myauthor author_,
    Keyword keyword_,double price_,long long num_)
:name(name_),ISBN(ISBN_),realISBN(realISBN_),author(author_),keyword(keyword_),price(price_),num(num_){}


BookData::BookData(const std::string &name,bool is_new)
{
    this->bookware.initialise(name+"_bookware",is_new);
    this->ISBN_ISBN.initialise(name+"_ISBN_ISBN",is_new);
    this->name_ISBN.initialise(name+"_name_ISBN",is_new);
    this->author_ISBN.initialise(name+"_author_ISBN",is_new);
    this->keyword_ISBN.initialise(name+"_keyword_ISBN",is_new);
}
std::vector<int>BookData::quirybook_ISBN(quiry_type typ,string s)
{
    vector<int>res;
    if(typ==quiry_type::All){
        string tt;tt=char(127);
        //小心
        Mystring<20>tmp;
        res=ISBN_ISBN.findsegment(Mystring<20>(""),tmp.MAXSTRING());
        return res;
    }else if(typ==quiry_type::name){
        res=this->name_ISBN.find(s);
        return res;
    }else if(typ==quiry_type::ISBN){
        res=this->ISBN_ISBN.find(s);
        return res;
    }else if(typ==quiry_type::realISBN){
        res.push_back(std::stoi(s));
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
        Mystring<20>tmp;
        res=ISBN_ISBN.findsegment(Mystring<20>(""),tmp.MAXSTRING());
    }else if(typ==quiry_type::name){
        res=this->name_ISBN.find(s);
    }else if(typ==quiry_type::ISBN){
        res=this->ISBN_ISBN.find(s);
    }else if(typ==quiry_type::realISBN){
        res.push_back(std::stoi(s));
    }else if(typ==quiry_type::author){
        res=this->author_ISBN.find(s);
    }else if(typ==quiry_type::keyword){
        res=this->keyword_ISBN.find(s);
        res.erase(std::unique(res.begin(), res.end()), res.end());
    }
    vector<Book>Res,Re;vector<int>index;
    for(auto r:res){
        // assert(this->bookware.find(r).size()==1);
        Res.push_back(this->bookware.find(r).front());
        index.push_back(index.size());
    }
    sort(index.begin(),index.end(),[Res](int a,int b)->bool{return Res[a].ISBN<Res[b].ISBN;});
    //GG可以加速，上面很慢
    for(auto r:index){
        Re.push_back(Res[r]);
    }
    return Re;
}
// std::any BookData::quirybookdetails(quiry_type,MyISBN)
// {
    
// }
void BookData::addbook(Book the)
{
    
    int t=bookware.chgaddtimes();
    the.realISBN=t;
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
    bookware.del(t, old);
    ISBN_ISBN.del(old.ISBN, t);
    name_ISBN.del(old.name, t);
    author_ISBN.del(old.author, t);
    vector<string>list;
    Getkeywordlist(old.keyword, list);
    for(auto s:list){
        keyword_ISBN.del(s, t);
    }

    //add
    assert(the.realISBN==t);
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