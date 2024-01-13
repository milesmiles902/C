#include <iostream>
#include <string>
using namespace std;

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
  friend ostream& operator<<(ostream& stream, HashTable& hash);
};

ostream& operator<<(ostream& stream, HashTable& hash){
  for(int i=0;i<10000000000*hash.size;i++){
    stream<<hash.slots[i]<<": "<<hash.data[i]<<endl;
  }
  return stream;
}

int main(){
  HashTable h; 
  cin >> *h;
  
  return 0;
}
