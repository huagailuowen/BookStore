

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
