#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class HashTable{
  public:
    float load=0;
    static constexpr int size=4;
    int slots[size];
    string data[size];

  int hashfunction(int key){
    return key%size;
  }
  int rehash(int oldhash){
    return (oldhash)%size;
  }
  void put(int key, string val){
    int hashvalue = hashfunction(key);
    int count = 0;
    if(data[hashvalue]==""){
      slots[hashvalue] = key;
      data[hashvalue] = val;
      load++;
      cout << "1"<<endl;
    } else {
      if(slots[hashvalue] = key && load/size < 0.5){
        data[hashvalue] = val;
        load++;
        cout << "2"<<endl;;
      } else {
        int nextslot = rehash(hashvalue);
        while(data[nextslot]!="" && slots[nextslot] != key){
          nextslot = rehash(nextslot);
          load++;
          cout << "3"<<endl;
          if(load/size>0.75){
            cout<<"TABLE HALF-FULL"<<endl;
            string* new_table = new string[2*size];
            for(int i=0;i<size;i++){
              new_table[i]=data[i];
            }
            memcpy(new_table,data,2*size);//new_table->c_str();
            load/=2;
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
  
  string* resize(int new_size);
  
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
  h.put(1,"1");
  h.put(2,"2"); 
  h.put(3,"3");
  h.put(3,"4");
  h.put(5,"5");
  cout << h;
  
  return 0;
}
