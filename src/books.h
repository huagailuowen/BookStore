#ifndef BOOKS
#define BOOKS
#include <ostream>
#include<string>
#include<vector>
#include<any>
#include"mytype.h"

#include"memory.h"

using std::string;
using std::vector;
class BookData;
class Book{
    Bookname name;
    MyISBN ISBN;
    int realISBN;
    Myauthor author;
    Keyword keyword;
    double price;
    int num;
    friend std::ostream& operator<<(std::ostream&,const Book&);
    friend bool buy(vector<string>list,std::ostringstream &oss);
    friend bool select(vector<string>list,std::ostringstream &oss);
    friend bool modify(vector<string>list,std::ostringstream &oss);
    friend bool import(vector<string>list,std::ostringstream &oss);
    public:
    Book(){num=price=0;}
    Book(Bookname name_,MyISBN ISBN_,int realISBN_,Myauthor author_,
    Keyword keyword_,double price_,int num_);
    friend class BookData;
    bool operator<(const Book &b)const;
    bool operator>(const Book &b)const;
    bool operator==(const Book &b)const;
    bool operator<=(const Book &b)const;
    bool operator>=(const Book &b)const;
    bool operator!=(const Book &b)const;
    bool cp(const Book &b)const;

};
std::ostream& operator<<(std::ostream&,const Book&);

class BookData{
    public:
    string name;
    // MyMemoryClass<MyISBN,Keyword>keywordware;
    MyMemoryClass<int,Book>bookware;//faster???
    MyMemoryClass<Keyword,int>keyword_ISBN;
    MyMemoryClass<Myauthor,int>author_ISBN;
    MyMemoryClass<Bookname,int>name_ISBN;
    MyMemoryClass<MyISBN,int>ISBN_ISBN;
    
    public:
    
    BookData()=default;
    BookData(const string &,bool is_new);
    std::vector<int>quirybook_ISBN(quiry_type,string);
    std::vector<Book>quirybook(quiry_type,string);
    // std::any quirybookdetails(quiry_type,MyISBN);
    void addbook(Book the);
    void modifybook(Book,Book);
    friend class Book;
    //判重

};
#endif