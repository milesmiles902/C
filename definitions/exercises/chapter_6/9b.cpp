#include <iostream>
#include <string>
#include <random>
#include <chrono>
using namespace std;

//The sorting algorithm bencharked was hashing. There would not be a difference in execution speeds because no other algorithms exist to search.

class HashTable{
  public:
  static const int size=1000;
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
  int i,size=500,array[500];
  for(i=0;i<500;i++){
    array[i]=(rand()%10);
  }
  HashTable h;
  
  chrono::time_point<std::chrono::system_clock> start, end;
  start = chrono::system_clock::now();
  for(i=0;i<size;i++){
    h.put(i,to_string(array[i]));
  }
  end = chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end-start;
  cout << "The time to insert 500 items into a hash table is: " << elapsed_seconds.count() << " seconds." << endl;
  return 0;
}
