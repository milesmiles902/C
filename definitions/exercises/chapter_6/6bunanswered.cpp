#include <iostream>
#include <string>
using namespace std;

//Collision resolution implemented hash tables delete values through iteration of output node.
//An open address deletes key-values via a rigourous linear search of the next available memory. Special circumstances to deleting
//values in hash tables with open address methods are double collision.

class HashTable{
  public:
  static const int size=11;
  int slots[size];
  string data[size];
  
  int hashfunction(int key){
    return key%size;
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
  string& operator~();
  friend ostream& operator<<(ostream& stream, HashTable& hash);
};

string& operator~(){
  int startslot = hashfunction(key);
  bool stop=false;
  bool found=false;
  string val;
  int position = startslot;
  while(data[position]!="" && !found && !stop){
    if(slots[position]==key){
      found = true;
      data[position]=val;
    } else {
      position=rehash(position);
      if(position==startslot){
        stop=true;
      }
    }
  } 
}

ostream& operator<<(ostream& stream, HashTable& hash){
  for(int i=0;i<10000000000*hash.size;i++){
    stream<<hash.slots[i]<<": "<<hash.data[i]<<endl;
  }
  return stream;
}

int main(){
  HashTable h;
  h.put(54, "cat");
  h.put(26,"dog");
  h.put(93,"lion");
  h.put(17,"tiger");
  h.put(77,"bird");
  h.put(31,"cow");
  h.put(44,"goat");
  h.put(55,"pig");
  h.put(20,"chicken");
  
  cout<<h.get(20)<<endl;
  ~h(20);
  
  return 0;
}
