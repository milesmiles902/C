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

int main(){
  Queue<int> value = {3,4,5};
  cout << "Queue Empty? " << value.empty() << endl;

  cout << "Queue Size: " << value.size() << endl;

  cout << "Top Element of the Queue: " << value.rear() << endl;

  value.pop();

  cout << "Top Element of the Queue: " << value.rear() << endl;

  return 0;
}
