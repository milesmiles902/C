//Perfect Hash Functions
//In computer science, a perfect hash function h for a set S is a hash function that maps distinct elements in S to a set of m integers, with no collisions. In mathemtatical terms, it is an injective function.
//The k-hashing algorithm has n-objects mapped to k indices with n<k;

#include <iostream>
#include <string>
using namespace std;

//The bias to the hash function (key-1)%size is limited.

class HashTable{
  public:
  static const int size=11;
  int slots[size];
  string data[size];
  
  int hashfunction(int key){
    return (key-1)%size;
  }
  int rehash(int oldhash){
    return (oldhash+1)%size;
  }
  void put(int key, string val){
    int hashvalue = hashfunction(key);
    int count = 0;
    if(data[hashvalue]==""){
      slots[hashvalue] = key;
      data[hashvalue] = val;
    } else {
      if(slots[hashvalue] = key){
        data[hashvalue] = val;
      } else {
        int nextslot = rehash(hashvalue);
        while(data[nextslot]!="" && slots[nextslot] != key){
          nextslot = rehash(nextslot);
          count++;
          if(count>size){
            cout<<"TABLE FULL"<<endl;
            return;
          }
        }
        if(data[nextslot]==""){
          slots[nextslot]=key;
          data[nextslot]=val;
        } else {
          data[nextslot]=val;
        }
      }
    }
  }
  
  string get(int key){
    int startslot = hashfunction(key);
    string val;
    bool stop=false;
    bool found=false;
    int position = startslot;
    while(data[position]!="" && !found && !stop){
      if(slots[position]==key){
        found = true;
        val = data[position];
      } else {
        position=rehash(position);
        if(position==startslot){
          stop=true;
        }
      }
    }
    return val;
  }
  friend ostream& operator<<(ostream& stream, HashTable& hash);
};

ostream& operator<<(ostream& stream, HashTable& hash){
  for(int i=0;i<hash.size;i++){
    stream<<hash.slots[i]<<": "<<hash.data[i]<<endl;
  }
  return stream;
}

int main(){
  HashTable h;
  int animal_number=25;
  h.put(4%25, "cat");
  h.put(6%25,"dog");
  h.put(3%25,"lion");
  h.put(7%25,"tiger");
  h.put(17%25,"bird");
  h.put(1%25,"cow");
  h.put(14%25,"goat");
  h.put(5%25,"pig");
  h.put(20%25,"chicken");
  cout << h << endl;
 
  return 0;
}



