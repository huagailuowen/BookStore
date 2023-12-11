

#include "mytype.h"
template<const int len>
Mystring<len>::Mystring()
{
    c[0]='\0';
    l=0;
}
template<const int len>
void Mystring<len>::gethash()
{
    myhash=0;
    for(int i=0;i<l;i++)
        myhash=(myhash<<7)+myhash+c[i];
}

template<const int len>
Mystring<len>::Mystring(string s){
    for(int i=0;i<s.size();i++)
        c[i]=s[i];
    l=s.size()+1;
    c[s.size()]='\0';
    gethash();
}
template<const int len>
char& Mystring<len>::operator[](const int &index)
{
    return c[index];
}
template<const int len>
char Mystring<len>::operator[](const int &index)const
{
    return c[index];
}

template<const int len>
int Mystring<len>::size()const
{
    return l;
}
template<const int len>
Mystring<len>::operator string()
{
    string s;
    for(int i=0;i<l;i++)
        s+=c[i];
    return s;
}
template<const int len>
string Mystring<len>::tostr()
{
    string s;
    for(int i=0;i<l;i++)
        s+=c[i];
    return s;
}
template<const int len>
bool Mystring<len>::operator<(Mystring &b)
{
    for(int i=0;i<std::max(l,b.l);i++){
        if(c[i]!=b.c[i])
            return c[i]<b.c[i];
    }
    return 0;
}
template<const int len>
bool Mystring<len>::operator==(Mystring &b)
{
    if(b.l!=l)return 0;
    for(int i=0;i<l;i++){
        if(c[i]!=b.c[i])
            return 0;
    }
    return 1;
}
template<const int len>
bool Mystring<len>::operator>(Mystring &b)
{
    return b<(*this);
}
template<const int len>
bool Mystring<len>::operator>=(Mystring &b)
{
    return !((*this)<b);
}
template<const int len>
bool Mystring<len>::operator<=(Mystring &b)
{
    return !((*this)>b);
}
template<const int len>
bool Mystring<len>::operator!=(Mystring &b)
{
    return !((*this)==b);
}
bool IsISBN(const string &s,MyISBN&the)
{
    if(s.size()>20)return false;
    for(auto c:s){
        if(!(c>=0&&c<=32||c==127))
            return false;
    }
    the=std::move(MyISBN(s));
    return true;   
}
bool Isuserid(const string &s,Userid&the)
{
    if(s.size()>30)return false;
    for(auto c:s){
        if(!(c>='0'&&c<='9'||c=='_'||c>='a'&&c<='z'||c>='A'&&c<='Z'))
            return false;
    }
    the=std::move(Userid(s));
    return true;
}
bool Isauthor(const string &s,Myauthor&the)
{
    if(s.size()>60)return false;
    for(auto c:s){
        if(!(c>=0&&c<=32||c==127||c=='\"'))
            return false;
    }
    the=std::move(Myauthor(s));
    return true;   
}
bool Isbookname(const string &s,Bookname &the)
{
    if(s.size()>60)return false;
    for(auto c:s){
        if(!(c>=0&&c<=32||c==127||c=='\"'))
            return false;
    }
    the=std::move(Bookname(s));
    return true;   
}
bool Isusername(const string &s,Username &the)
{
    if(s.size()>30)return false;
    for(auto c:s){
        if(!(c>=0&&c<=32||c==127))
            return false;
    }
    the=std::move(Username(s));
    return true;    
}
bool Ispassword(string s,Password&the)
{
    if(s.size()>30)return false;
    for(auto c:s){
        if(!(c>='0'&&c<='9'||c=='_'||c>='a'&&c<='z'||c>='A'&&c<='Z'))
            return false;
    }
    the=std::move(Password(s));
    return true;
}
bool Iskeyword(const string &s,Keyword&the)
{
    // if(s.size()==0)return false;
    //????
    if(s.size()>60)return false;
    char las='|';
    for(auto c:s){
        if(!(c>=0&&c<=32||c==127||c=='\"'))
            return false;
        if(c=='|'&&las=='|')
            return false;
        las=c;
    }
    if(las=='|')
        return false;
    the=std::move(Keyword(s));
    return true;
}
void Getkeywordlist(const Keyword&the,std::vector<string>&list)
{
    list.clear();
    string tmp="";
    for(int i=0;i<the.size();i++){
        if(the[i]=='|')list.push_back(std::move(tmp)),tmp="";
        else tmp+=the[i];
    }
}