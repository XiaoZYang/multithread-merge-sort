#ifndef BILIST_H
#define BILIST_H
#include <vector>
#include <future>
#include <thread>

template <typename T>
class BiLinkedList{
    class Node{
        public:
            class Node * prev;
            class Node * next;
            T val;
            Node(T val): prev(nullptr), next(nullptr), val(val) {}
            //~Node(){}
    };
    Node *head;
    Node *tail;
    public:
        BiLinkedList(): head(nullptr), tail(nullptr){}
        void add(T t){
            if(head == nullptr){
                head = new Node(t);
                tail = head;
            }else{
                tail->next = new Node(t);
                tail->next->prev = tail;
                tail = tail->next;
            }
        }

        void remove(Node * n){
            if(n == head){
                auto p = head;
                if(head->next != nullptr) head->next->prev = head->prev;
                head = head->next;
                delete p;
            }
            if(n->prev != nullptr) n->prev->next = n->next;
            if(n->next != nullptr) n->next->prev = n->prev;
            // delete n;
        }

        Node* begin(){
            return head;
        }

        Node* end(){
            return tail->next;
        }

        bool empty(){
            return head == nullptr;
        }
};

#endif
