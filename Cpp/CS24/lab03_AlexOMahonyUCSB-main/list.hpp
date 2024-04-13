#ifndef LIST_HPP_
#define LIST_HPP_

#include <cstddef>
#include <utility>
#include <iostream>
#include <vector>

template<typename T>
struct Node;

template<typename T>
class List{
    private:
        Node<T>* head;
        Node<T>* tail;
    public:
        // Constructors/Assigners
        List();
        List(List const& o);
        List(List&& o);
        List& operator=(List const& o);
        List& operator=(List&& o);
        
        // Destructor
        ~List();

        // Accessors
        bool empty() const;
        size_t size() const;
        T& front() const;
        T& back() const;
        T& at(size_t index) const;

        // Mutators
        void clear();
        void insert(size_t index, T const& value);
        void pop_front();
        void push_front(T const& value);
        void pop_back();
        void push_back(T const& value);
        void erase(size_t index);
        void erase(size_t first, size_t count);

        // Equality Operator
        template<typename C>
        friend bool operator==(List<C> const& lhs, List<C> const& rhs);

        // Debugging Tools
        void render(std::ostream& out) const;
        static size_t alloc_cnt(){return Node<T>::alloc_cnt;}
};

template<typename T>
void List<T>::render(std::ostream& out) const{
    out<<'[';
    if(this->head != NULL){
        out<<this->head->val;
        Node<T>* p = this->head->next;
        while(p != NULL){
            out<<','<<p->val;
            p = p->next;
        }
    }
    out<<']'<<'\n';
}

template<typename T>
std::ostream& operator<<(std::ostream& o, List<T> const& v){
    v.render(o);
    return o;
}


template<typename T>
struct Node{
    T val;
    Node* next;
    static size_t alloc_cnt;

    Node(T const& val, Node* const next = NULL);
    Node(Node const& o);
    Node(Node&& o);
    ~Node();
    Node& operator=(Node const& o);
    Node& operator=(Node&& o);
};

template<typename T>
Node<T>::Node(T const& value, Node<T>* const next_node):val(value),next(next_node){++alloc_cnt;}

template<typename T>
Node<T>::Node(Node<T> const& o):val(o.val),next(o.next == NULL ? NULL : new Node(*o.next)){++alloc_cnt;}

template<typename T>
Node<T>::Node(Node<T>&& o):val(std::move(o.val)),next(o.next){
    o.next = NULL;
    ++alloc_cnt;
}

template<typename T>
Node<T>::~Node(){
    if(this->next != NULL)
        delete next;
    --alloc_cnt;
}

template<typename T>
Node<T>& Node<T>::operator=(Node<T> const& o){
    if(this->next != NULL) delete this->next;
    this->val = o.val;
    this->next = o.next == NULL ? NULL : new Node(*o.next);
    return *this;
}

template<typename T>
Node<T>& Node<T>::operator=(Node<T>&& o){
    if(this->next != NULL) delete this->next;
    this->val = std::move(o.val);
    this->next = o.next;
    o.next = NULL;
    return *this;
}

#endif //LIST_HPP_