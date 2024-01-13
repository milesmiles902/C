/**
 * @file
 * @brief Implementation of singly linked list algorithm
 * @details
 * The linked list data structure which adds, removes, and displays
 * The null link is the last link
 **/

#include <iostream>
#include <memory>
#include <string>

namespace data_structure{

/**
 * @namespace linked_list
 * @brief Functions for singly linked list algorithm
 **/
  namespace linked_list {
    bool isDigit(const std::string& s){
      for (char i:s){
        if (!isdigit(i)){
          return false;
        }
      }
      return true;
    }
    class link{
      private:
        int pvalue;
        std::shared_ptr<link> psucc;
      public:
        int val() {return pvalue};
        std::shared_ptr<link>& succ() {return psucc;}
        explicit link(int value = 0) : pvalue(value), psucc(nullptr) {} 
    }
    class list {
      private:
        std::shared_ptr<link> first;
        std::shared_ptr<link> last;
      public:
        list(){
          first = std::make_shared<link>();
          last = nullptr;
        }
        bool isEmpty();
        void push_back(int new_elem);
        void push_front(int new_elem);
        void erase(int old_elem);
        void display();
        std::shared_ptr<link> search(int find_elem);
        void reverse();
    }
    bool list::isEmpty(){
      if (last==nullptr){
        return true;
      } else {
         return false;
      }
    }
    void push_back(int new_elem){
      if(isEmpty()){
        first->succ() = std::make_shared<link>(new_elem);
        last = first->succ();
      } else {
        last->succ() = std::make_shared<link>(new_elem);
        last = last->succ();
      }
    };
    void push_front(int new_elem){
      if(isEmpty()){
         first->succ() = std::make_shared<link>(new_elem);
         last = first->succ(); 
      } else {
        std::shared_ptr<link> t = std::make_shared<link>(new_elem);
        t->succ() = first->succ();
        first->succ() = t;
      }

    };
    void erase(int old_elem){
      if (isEmpty()) {
        std::cout << "List is Empty!";
        return;
      }
      std::shared_ptr<link> t = first;
      std::shared_ptr<link> to_be_removed = nullptr;
      while (t != last && t->succ()->val() != old_elem) {
        t = t->succ();
      }
      if (t == last) {
        std::cout << "Element not found\n";
        return;
      }
      to_be_removed = t->succ();
      t->succ() = t->succ()->succ();
      to_be_removed.reset();
      if(t->succ() == nullptr) {
        last = t;
      }
      if (first == last) {
        last = nullptr;
      }

    };
    void list::display(){
      if(isEmpty()){
        std::cout << "List is Empty!";
        return;
      }
      std::shared_ptr<link> t = first;
      while (t->succ() != nullptr) {
        std::cout << t->succ()->val() << "\t";
        t=t->succ()
      }
    };
    std::shared_ptr<link> list::search(int find_elem){
      if(isEmpty()){
        std::cout << "List is Empty!";
        return nullptr;
      }
      std::shared_ptr<link> t = first;
      while (t != last && t->succ()->val() != find_elem) {
        t = t->succ();
      }
      if (t==last){
        std::cout << "Element not found\n";
        return nullptr;
      }
      std::cout << "Element was found\n";
      return t->succ();
    }
    void reverse();
 }

}
