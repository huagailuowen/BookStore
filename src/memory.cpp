
// #include "memory.h"
// #include <cassert>
// #include <cstddef>
// #include <ctime>
// #include <ios>
// #include <vector>


// #include <fstream>

// using std::fstream;
// using std::ifstream;
// using std::ofstream;
// using std::string;

// template <class Tkey, class Tvalue>
// Tkey MyMemoryClass<Tkey, Tvalue>::Block::minikey() {
//   return indexkey;
// }
// template <class Tkey, class Tvalue>
// Tvalue MyMemoryClass<Tkey, Tvalue>::Block::minival() {
//   return indexval;
// }
// template <class Tkey, class Tvalue>
// size_t MyMemoryClass<Tkey, Tvalue>::Block::size() {
//   return itemnum;
// }
// template <class Tkey, class Tvalue>
// void MyMemoryClass<Tkey, Tvalue>::Block::add(Tkey _key, Tvalue _val) {
//   key[itemnum] = _key;
//   val[itemnum++] = _val;
//   int p = itemnum - 1;
//   while (p && (key[p] < key[p - 1] ||
//                (key[p] == key[p - 1] && val[p] < val[p - 1]))) {
//     std::swap(key[p], key[p - 1]);
//     std::swap(val[p], val[p - 1]);
//     p--;
//   }
//   if (!F) {
//     indexkey = _key;
//     indexval = _val;
//     F = 1;
//   }
// }
// template <class Tkey, class Tvalue>
// void MyMemoryClass<Tkey, Tvalue>::Block::upd() {
//   if (F)
//     return;
//   indexkey = key[0];
//   indexval = val[0];
//   F = 1;
//   return;
// }
// template <class Tkey, class Tvalue>
// int MyMemoryClass<Tkey, Tvalue>::getaddtimes()
// {
//   file.open(file_name, std::ios::out | std::ios::in);
//   Head H;
//   file.read(reinterpret_cast<char *>(&H), sizeof(Head));
//   file.close();
//   return H.addtimes;
// }
// template <class Tkey, class Tvalue>
// void MyMemoryClass<Tkey, Tvalue>::initialise(string FN, bool is_new) {

//   if (FN != "")
//     file_name = FN;
//   // if(!is_new)return;
//   // if()
//   file.open(file_name, std::ios::app);
//   if (file.tellp() != 0) {
//     file.close();
//     return;
//   }
//   // std::cerr<<"|||"<<file.tellp()<<'\n';
//   Head H;
//   // H.indexkey
//   file.write(reinterpret_cast<char *>(&H), sizeof(Head));
//   file.close();
// }
// template <class Tkey, class Tvalue>
// void MyMemoryClass<Tkey, Tvalue>::insert(Tkey key, Tvalue val) {
//   file.open(file_name, std::ios::out | std::ios::in);
//   Head H;
//   file.read(reinterpret_cast<char *>(&H), sizeof(Head));
//   if (H.blocknum == 0) {
//     // file.seekp(sizeof(Head));
//     Block block;
//     block.add(key, val);
//     H.index[H.blocknum] = sizeof(Head);
//     H.indexkey[H.blocknum] = block.minikey();
//     H.indexval[H.blocknum++] = block.minival();
//     file.seekp(0, std::ios::beg);
//     file.write(reinterpret_cast<char *>(&H), sizeof(Head));
//     file.seekp(sizeof(Head), std::ios::beg);
//     file.write(reinterpret_cast<char *>(&block), sizeof(Block));
//     file.close();
//     return;
//   }
//   int las = 0;
//   for (int i = 0; i < H.blocknum; i++) {
//     if (i && (key < H.indexkey[i] ||
//               (key == H.indexkey[i] && val < H.indexval[i]))) {
//       break;
//     }
//     las = i;
//   }
//   // 最后一只
//   Block block;
//   file.seekg(H.index[las], std::ios::beg);
//   file.read(reinterpret_cast<char *>(&block), sizeof(Block));
//   if (block.size() != blocklength) {
//     block.add(key, val);
//     H.indexkey[las] = block.minikey();
//     H.indexval[las] = block.minival();

//     file.seekp(0, std::ios::beg);
//     file.write(reinterpret_cast<char *>(&H), sizeof(Head));

//     file.seekp(H.index[las], std::ios::beg);
//     file.write(reinterpret_cast<char *>(&block), sizeof(Block));
//     file.close();
//     return;
//   }
//   Block newblock;
//   file.seekg(0, std::ios::end);
//   H.index[H.blocknum++] = file.tellg();
//   for (int i = H.blocknum - 1; i > las + 1; i--) {
//     std::swap(H.index[i], H.index[i - 1]);
//     std::swap(H.indexkey[i], H.indexkey[i - 1]);
//     std::swap(H.indexval[i], H.indexval[i - 1]);
//   }
//   for (int i = (blocklength >> 1); i < blocklength; i++) {
//     newblock.add(block.key[i], block.val[i]);
//   }
//   block.itemnum = (blocklength >> 1);
//   if (block.key[block.itemnum] < key ||
//       (block.key[block.itemnum] == key && block.val[block.itemnum] < val)) {
//     newblock.add(key, val);
//   } else {
//     block.add(key, val);
//   }
//   block.upd();
//   newblock.upd();
//   H.indexkey[las] = block.minikey();
//   H.indexval[las] = block.minival();

//   H.indexkey[las + 1] = newblock.minikey();
//   H.indexval[las + 1] = newblock.minival();

//   file.seekp(0, std::ios::beg);
//   file.write(reinterpret_cast<char *>(&H), sizeof(Head));

//   file.seekp(H.index[las], std::ios::beg);
//   file.write(reinterpret_cast<char *>(&block), sizeof(Block));
//   file.seekp(H.index[las + 1], std::ios::beg);
//   file.write(reinterpret_cast<char *>(&newblock), sizeof(Block));

//   file.close();
// }
// template <class Tkey, class Tvalue>
// std::vector<Tvalue> MyMemoryClass<Tkey, Tvalue>::find(Tkey key) {
//   // std::cerr<<key.tostr()<<'\n';
//   std::vector<Tvalue> Ans;
//   file.open(file_name, std::ios::out | std::ios::in);
//   Head H;
//   file.read(reinterpret_cast<char *>(&H), sizeof(Head));
//   // std::cerr<<H.blocknum<<'\n';
//   if (H.blocknum == 0) {
//     return Ans;
//   }
//   // std::cerr<<H.blocknum<<'\n';
//   int las = 0, beg = H.blocknum;
//   for (int i = 0; i < H.blocknum; i++) {
//     if (i && (key < H.indexkey[i])) {
//       break;
//     }
//     las = i;
//   }
//   for (int i = H.blocknum - 1; i >= 0; i--) {
//     if ((i == 0) || key > H.indexkey[i]) {
//       beg = i;
//       break;
//     }
//   }
//   assert(beg <= las);
//   // std::cerr<<las-beg<<'\n';
//   Block block;
//   for (int i = beg; i <= las; i++) {
//     file.seekg(H.index[i], std::ios::beg);
//     file.read(reinterpret_cast<char *>(&block), sizeof(Block));
//     for (int j = 0; j < block.itemnum; j++) {
//       if (key == block.key[j]) {
//         Ans.push_back(block.val[j]);
//       }
//     }
//   }
//   // 最后一只
//   file.close();
//   return Ans;
// }
// template <class Tkey, class Tvalue>
// void MyMemoryClass<Tkey, Tvalue>::del(Tkey key, Tvalue val) {
//   std::vector<Tvalue> Ans;
//   file.open(file_name, std::ios::out | std::ios::in);
//   Head H;
//   file.read(reinterpret_cast<char *>(&H), sizeof(Head));
//   // std::cerr<<H.blocknum<<'\n';
//   if (H.blocknum == 0) {
//     return;
//   }
//   // std::cerr<<H.blocknum<<'\n';
//   int las = 0, beg = H.blocknum;
//   for (int i = 0; i < H.blocknum; i++) {
//     if (i && (key < H.indexkey[i] ||
//               (key == H.indexkey[i] && val < H.indexval[i]))) {
//       break;
//     }
//     las = i;
//   }
//   for (int i = H.blocknum - 1; i >= 0; i--) {
//     if ((i == 0) || (key > H.indexkey[i] ||
//                      (key == H.indexkey[i] && val > H.indexval[i]))) {
//       beg = i;
//       break;
//     }
//   }
//   assert(beg <= las);
//   // std::cerr<<las-beg<<'\n';
//   Block block;
//   int p;
//   for (int i = beg; i <= las; i++) {
//     file.seekg(H.index[i], std::ios::beg);
//     file.read(reinterpret_cast<char *>(&block), sizeof(Block));
//     int flag = 0;
//     p = 0;
//     for (int j = 0; j < block.itemnum; j++) {
//       if (key == block.key[j] && val == block.val[j]) {
//         // std::cerr<<"234342";
//         flag = 1;
//       } else {
//         block.key[p] = block.key[j];
//         block.val[p] = block.val[j];
//         p++;
//       }
//     }
//     block.itemnum = p;
//     block.upd();
//     // cerr<<sizeof(Block);
//     if (!flag)
//       continue;
//     file.seekp(H.index[i], std::ios::beg);
//     file.write(reinterpret_cast<char *>(&block), sizeof(Block));
//   }
//   // 最后一只
//   file.close();
//   return;
// }
