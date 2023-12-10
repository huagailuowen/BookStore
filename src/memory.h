#ifndef MY_MEMORY_CLASS
#define MY_MEMORY_CLASS
#include <cassert>
#include <cstddef>
#include <ctime>
#include <ios>
#include <vector>
#include <fstream>

using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;
const int MAXblocknum=500;
const int blocklength=300;
template<class Tkey,class Tvalue>
class MyMemoryClass {
private:
    fstream file;
    string file_name;
public:
    class Head{
        public:
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
        Tkey minikey();
        Tvalue minival();
        std::size_t size();
        void add(Tkey _key,Tvalue _val);
        void upd();
    };
    
    MyMemoryClass() = default;

    MyMemoryClass(const string& file_name) : file_name(file_name) {}

    void initialise(string FN = "",bool is_new=1);
    void insert(Tkey key,Tvalue val);

    std::vector<Tvalue> find(Tkey key);
    void del(Tkey key,Tvalue val);
};
#endif
