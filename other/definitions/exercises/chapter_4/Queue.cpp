#include <iostream>
#include <vector>

using namespace std;

template<class T>
class Queue{
  public:
    Queue(const std::initializer_list<T>& i) :vec{i} {};
    void pop() {
      vec.erase(vec.begin());
    };
    void push(int value) {
      vec.push_back(value);
    };
    int size(){
      return vec.size();
    };
    bool empty() {
      return vec.empty();
    };
    int rear() {
      return vec.back();
    };
  private:
    std::vector<T> vec;
};

