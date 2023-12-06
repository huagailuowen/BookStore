#include<bits/stdc++.h>
#include <cassert>
#include <cstddef>
#include <ctime>
#include <ios>
#include <vector>
#ifndef MY_MEMORY_CLASS
#define MY_MEMORY_CLASS

#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

const int MAXblocknum=2000;
const int blocklength=2000;
template<class Tkey,class Tvalue>
class MyMemoryClass {
private:
    fstream file;
    string file_name;
public:
    class Head{
        public:
        //别用这个，sizeof 写不了
        //std::vector<int>index;
        int blocknum=0;
        int index[MAXblocknum];
        Tkey indexkey[MAXblocknum];
        Tvalue indexval[MAXblocknum];
        
    };
    class Block{
        //别用这个，sizeof 写不了
        //std::vector<int>index;
        public:
        size_t itemnum=0;
        Tkey indexkey;
        Tvalue indexval;
        bool F=0;
        Tkey key[blocklength];
        Tvalue val[blocklength];
        Tkey minikey()
        {
            return indexkey;
        }
        Tvalue minival()
        {
            return indexval;
        }
        
        std::size_t size()
        {
            return itemnum; 
        }
        void add(Tkey _key,Tvalue _val)
        {
            key[itemnum]=_key;
            val[itemnum++]=_val;
            int p=itemnum-1;
            while(p&&(key[p]<key[p-1]||(key[p]==key[p-1]&&val[p]<val[p-1]))){
                std::swap(key[p],key[p-1]);
                std::swap(val[p],val[p-1]);
                p--;
            }
            if(!F){
                indexkey=_key;
                indexval=_val;
                F=1;
            }
        }
        void upd()
        {
            if(F)return;
            indexkey=key[0];
            indexval=val[0];
            F=1;
            return ;
            // for(int i=1;i<itemnum;i++){
            //     if(indexkey>key[i])
            //         indexkey=key[i];
            // }
        }
    };
    
    MyMemoryClass() = default;

    MyMemoryClass(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "",bool is_new=1) {
        if (FN != "") file_name = FN;
        if(!is_new)return;
        file.open(file_name, std::ios::out);
        Head H;
        // H.indexkey
        file.write(reinterpret_cast<char *>(&H), sizeof(Head));
        file.close();
    }
    void insert(Tkey key,Tvalue val)
    {
        file.open(file_name, std::ios::out|std::ios::in);
        Head H;
        file.read(reinterpret_cast<char *>(&H), sizeof(Head));
        if(H.blocknum==0){
            // file.seekp(sizeof(Head));
            Block block;
            block.add(key,val);
            H.index[H.blocknum]=sizeof(Head);
            H.indexkey[H.blocknum]=block.minikey();
            H.indexval[H.blocknum++]=block.minival();
            file.seekp(0,std::ios::beg);
            file.write(reinterpret_cast<char *>(&H), sizeof(Head));
            file.seekp(sizeof(Head),std::ios::beg);
            file.write(reinterpret_cast<char *>(&block), sizeof(Block));
            file.close();
            return;
        }
        int las=0;
        for(int i=0;i<H.blocknum;i++){
            if(i&&(key<H.indexkey[i]||(key==H.indexkey[i]&&val<H.indexval[i]))){
                break;
            }         
            las=i;  
        }
        //最后一只
        Block block;
        file.seekg(H.index[las],std::ios::beg);
        file.read(reinterpret_cast<char *>(&block), sizeof(Block));
        if(block.size()!=blocklength){
            block.add(key,val);
            H.indexkey[las]=block.minikey();
            H.indexval[las]=block.minival();
            
            file.seekp(0,std::ios::beg);
            file.write(reinterpret_cast<char *>(&H), sizeof(Head));
            
            file.seekp(H.index[las],std::ios::beg);
            file.write(reinterpret_cast<char *>(&block), sizeof(Block));
            file.close();
            return;
        }
        Block newblock;
        file.seekg(0,std::ios::end);
        H.index[H.blocknum++]=file.tellg();
        for(int i=H.blocknum-1;i>las+1;i--){
            std::swap(H.index[i],H.index[i-1]);
            std::swap(H.indexkey[i],H.indexkey[i-1]);
            std::swap(H.indexval[i],H.indexval[i-1]);
            
        }
        for(int i=(blocklength>>1);i<blocklength;i++){
            newblock.add(block.key[i], block.val[i]);
        }
        block.itemnum=(blocklength>>1);
        if(block.key[block.itemnum]<key||(block.key[block.itemnum]==key&&block.val[block.itemnum]<val))
        {
            newblock.add(key,val);
        }
        else{
            block.add(key,val);
        }
        block.upd();
        newblock.upd();
        H.indexkey[las]=block.minikey();
        H.indexval[las]=block.minival();
        
        H.indexkey[las+1]=newblock.minikey();
        H.indexval[las+1]=newblock.minival();
        
        file.seekp(0,std::ios::beg);
        file.write(reinterpret_cast<char *>(&H), sizeof(Head));
            
        file.seekp(H.index[las],std::ios::beg);
        file.write(reinterpret_cast<char *>(&block), sizeof(Block));
        file.seekp(H.index[las+1],std::ios::beg);
        file.write(reinterpret_cast<char *>(&newblock), sizeof(Block));
        

        file.close();
    }

    std::vector<Tvalue> find(Tkey key)
    {
        // std::cerr<<key.tostr()<<'\n';
        std::vector<Tvalue> Ans;
        file.open(file_name, std::ios::out|std::ios::in);
        Head H;
        file.read(reinterpret_cast<char *>(&H), sizeof(Head));
        // std::cerr<<H.blocknum<<'\n';
        if(H.blocknum==0){
            return Ans;
        }
            // std::cerr<<H.blocknum<<'\n';
        int las=0,beg=H.blocknum;
        for(int i=0;i<H.blocknum;i++){
            if(i&&(key<H.indexkey[i])){
                break;
            }         
            las=i;  
        }
        for(int i=H.blocknum-1;i>=0;i--){
            if((i==0)||key>H.indexkey[i]){
                beg=i;
                break;
            }         
        }
        assert(beg<=las);
        // std::cerr<<las-beg<<'\n';
        Block block;
        for(int i=beg;i<=las;i++){
            file.seekg(H.index[i],std::ios::beg);
            file.read(reinterpret_cast<char *>(&block), sizeof(Block));
            for(int j=0;j<block.itemnum;j++){
                if(key==block.key[j]){
                    Ans.push_back(block.val[j]);
                }
            }
        }
        //最后一只
        file.close();
        return Ans;
    }
    void del(Tkey key,Tvalue val)
    {
        std::vector<Tvalue> Ans;
        file.open(file_name, std::ios::out|std::ios::in);
        Head H;
        file.read(reinterpret_cast<char *>(&H), sizeof(Head));
        // std::cerr<<H.blocknum<<'\n';
        if(H.blocknum==0){
            return;
        }
            // std::cerr<<H.blocknum<<'\n';
        int las=0,beg=H.blocknum;
        for(int i=0;i<H.blocknum;i++){
            if(i&&(key<H.indexkey[i]||(key==H.indexkey[i]&&val<H.indexval[i]))){
                break;
            }         
            las=i;  
        }
        for(int i=H.blocknum-1;i>=0;i--){
            if((i==0)||(key>H.indexkey[i]||(key==H.indexkey[i]&&val>H.indexval[i]))){
                beg=i;
                break;
            }         
        }
        assert(beg<=las);
        // std::cerr<<las-beg<<'\n';
        Block block;
        int p;
        for(int i=beg;i<=las;i++){
            file.seekg(H.index[i],std::ios::beg);
            file.read(reinterpret_cast<char *>(&block), sizeof(Block));
            int flag=0;
            p=0;
            for(int j=0;j<block.itemnum;j++){
                if(key==block.key[j]&&val==block.val[j]){
            // std::cerr<<"234342";
                    flag=1;
                }
                else{
                    block.key[p]=block.key[j];
                    block.val[p]=block.val[j];
                    p++;
                }
            }
            block.itemnum=p;
            block.upd();
            // cerr<<sizeof(Block);
            if(!flag)continue;
            file.seekp(H.index[i],std::ios::beg);
            file.write(reinterpret_cast<char *>(&block), sizeof(Block));
            
        }
        //最后一只
        file.close();
        return ;
    }
    void test() {
        // if (FN != "") file_name = FN;
        clock_t time_req;
        time_req=clock();
        file.open(file_name, std::ios::app);
        // for(int T=1;T<=1000;T++){
        // int t=10;
        // for(int i=1;i<=10000;i++){

        //     file.write(reinterpret_cast<char *>(&t), sizeof(int));
        // }
        // }
        // std::cerr<<"||||||||||||||"<<'\n';
        for(int T=1;T<=20000;T++){
        int t=10;
            // file.write(reinterpret_cast<char *>(&pp), sizeof(P));
        
        
        }
        time_req=clock()-time_req;
        std::cout<<(double)time_req/CLOCKS_PER_SEC<<'\n';
        file.close();
    }
    

    
    
    // int write(Tvalue &t) {
    //     /* your code here */
    //     int flag;
    //     file.open(file_name, std::ios::app);
    //     int index=file.tellp();
    //     file.write(reinterpret_cast<char *>(&t), sizeof(T));
    //     // file.seekp(sizeof(int)*(info_len));
    //     // fstream tmp;
    //     // tmp.open(file_name, std::ios::app);
    //     // // file.read(reinterpret_cast<char *>(&flag), sizeof(int));
    //     // while(file.tellp()!=tmp.tellp()){
    //     //     file.seekp(sizeof(T));
    //     // }
    //     // tmp.close();
    //     file.close();
    //     return index;
    // }

    

    
    // void read(T &t, const int index) {
    //     /* your code here */
    //     file.open(file_name, std::ios::in);
    //     file.seekg(index);
    //     file.read(reinterpret_cast<char *>(&t), sizeof(T));
    //     file.close();
    // }
};
struct Mystring{
    char c[65];int l=0;
    Mystring()
    {c[0]='\0';l=0;}
    Mystring(string s){
        for(int i=0;i<s.size();i++)
            c[i]=s[i];
        l=s.size()+1;
        c[s.size()]='\0';
    }
    string tostr()
    {
        string s;
        for(int i=0;i<l;i++)
            s+=c[i];
        return s;
    }
    bool operator<(Mystring &b)
    {
        for(int i=0;i<std::max(l,b.l);i++){
            if(c[i]!=b.c[i])
                return c[i]<b.c[i];
        }
        return 0;
    }
    bool operator==(Mystring &b)
    {
        if(b.l!=l)return 0;
        for(int i=0;i<l;i++){
            if(c[i]!=b.c[i])
                return 0;
        }
        return 1;
    }
    bool operator>(Mystring &b)
    {
        return b<(*this);
    }
    bool operator>=(Mystring &b)
    {
        return !((*this)<b);
    }
    bool operator<=(Mystring &b)
    {
        return !((*this)>b);
    }
    bool operator!=(Mystring &b)
    {
        return !((*this)==b);
    }

};

#endif //MY_MEMORY_CLASS
using namespace std;
int main()
{
    // Mystring a("323233");
    // Mystring b(a);
    // a.c[1]='8';
    // cout<<a.tostr()<<' '<<b.tostr()<<'\n';
        
    MyMemoryClass<Mystring, int>A;
    A.initialise("hhh.in");
    int T;cin>>T;
    while(T--){
        string s;string a;int b;
        cin>>s;
        if(s=="insert"){
            cin>>a>>b;
            A.insert(a, b);
        }
        if(s=="delete"){
            cin>>a>>b;
            A.del(a, b);
        }
        if(s=="find"){
            cin>>a;//cout<<"|||";
            vector<int>v=A.find(a);
            if(v.empty())cout<<"null";
            else{
                for(auto u:v)
                    cout<<u<<' ';
            }
            cout<<'\n';
        }
        
    }
    
    // for(int i=1;i<=1000;i++){
    //     A.insert(rand()%100, i);

    // }
    // vector<int >v=A.find(6);
    // // cout<<v.size();
    // for(auto u:v){
    //     cout<<u<<'\n';
    // }
    // A.del(6,137);
    // A.del(6,137);
    // A.del( 6,207);
    // A.del( 6,740);
    // A.del( 6,887);
    // // cerr<<"4444";
    // v=A.find(6); v 
    // // cout<<v.size();
    // for(auto u:v){
    //     cout<<u<<'\n';
    // }
    return 0;
}
/*
8
insert FlowersForAlgernon 1966
insert CppPrimer 2012
insert Dune 2021
insert CppPrimer 2001
find CppPrimer
find Java
delete CppPrimer 2012
find CppPrimer
*/