#include <iostream>
using namespace std;

//creates a node class
class Node {
    //defines data, and next as a pointer.
    private:
        int data; //data in the beginning node
        Node *next; //pointer to the next node

    public:
        Node(int initdata) {
                data = initdata; //the initialized data is set as the head
                next = NULL; //the next node is set as NULL, as there is no next node yet.
        }

        int getData() { //function that return data of a given node.
                return data;
        }

        Node *getNext() { // pointer that gets the next node
                return next;
        }

        void setData(int newData) { // sets data in node
                data = newData;
        }

        void setNext(Node *newnext) {
                next = newnext;
        }
};

 // creates unorderedlist that points to the head of the linked list
class UnorderedList {
    public:
            Node *head;

            UnorderedList() { // makes the head node equal to null
                    head = NULL;
            }

        bool isEmpty() { // the head node is empty if it is null
            return head == NULL;
        }

        void add(int item) { //cerates a "temp" pointer that adds the new node to the head of the list
            Node *temp = new Node(item);
            temp->setNext(head);
            head = temp;
        }

        int size() { //cereates a "current" pointer that iterates through the list until it reaches null
            Node *current = head;
            int count = 0;
            while (current != NULL) {
                count++;
                current = current->getNext();
            }

            return count;
        }

        // creates "current" pointer that iterates through the list
        // untli it finds the item being searched for, and returns a boolean value

        bool search(int item) {
            Node *current = head;
            while (current != NULL) {
                if (current->getData() == item) {
                    return true;
                } else {
                    current = current->getNext();
                }
            }
            return false;
        }

        // uses current and previous pointer to iterate through the lists
        // finds the items that is searched for, and removes it

        void remove(int item) {
            Node *current = head;
            Node *previous = NULL;
            bool found = false;
            while (!found) {
                if (current->getData() == item) {
                    found = true;
                } else {
                    previous = current;
                    current = current->getNext();
                }
            }
            if (previous == NULL) {
                head = current->getNext();
            } else {
                previous->setNext(current->getNext());
            }
        }

        friend ostream& operator<<(ostream& os, const UnorderedList& ol);
};

ostream& operator<<(ostream& os, const UnorderedList& ol) {
    Node *current = ol.head;
    while (current != NULL) {
        os<<current->getData()<<endl;
        current = current->getNext();
    }
    return os;
}


int main() {
    UnorderedList mylist;
    mylist.add(31);
    mylist.add(77);
    mylist.add(17);
    mylist.add(93);
    mylist.add(26);
    mylist.add(54);
    mylist.add(54);

    cout<<"MY LIST: "<<endl<<mylist;
    return 0;
}

