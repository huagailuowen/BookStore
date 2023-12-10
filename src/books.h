#ifndef BOOKS
#define BOOKS
#include<string>
#include<vector>
#include<any>
#include"mytype.h"

#include"memory.h"

using std::string;
using std::vector;
class Book{
    Bookname name;
    MyISBN ISBN;
    Myauthor author;
    Keyword keyword;
    int price;
};
class BookData{
    string name;
    // MyMemoryClass<MyISBN,Keyword>keywordware;
    MyMemoryClass<MyISBN,Book>bookware;//faster???
    MyMemoryClass<Keyword,MyISBN>keyword_ISBN;
    MyMemoryClass<Myauthor,MyISBN>author_ISBN;
    MyMemoryClass<Bookname,MyISBN>name_ISBN;
    public:
    
    BookData()=default;
    BookData(string &);
    std::vector<MyISBN>quirybook(quiry_type,vector<string>);
    std::any quirybookdetails(quiry_type,MyISBN);

};
#endif