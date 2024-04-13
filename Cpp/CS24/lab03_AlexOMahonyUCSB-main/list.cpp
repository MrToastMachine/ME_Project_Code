#include "list.hpp"

// Constructors/Assignment Operators
template<typename T>
List<T>::List():head((Node<T>*)0x1),tail(NULL){}

template<typename T>
List<T>::List(List<T> const& o):head(o.head == NULL ? NULL : new Node<T>(*o.head)){
    this->tail = NULL; 
    while(this->tail != NULL && this->tail->next != NULL){
        this->tail = this->tail->next;
    }
}


template<typename T>
List<T>& List<T>::operator=(List<T> const& o){
    if(this!=&o){
        if(this->head != NULL) delete this->head;
        this->head = o.head == NULL ? NULL : new Node<T>(o.head->val);
        this->tail = this->head;
        while(this->tail != NULL && this->tail->next != NULL){
            this->tail = this->tail->next;
        }
    }
    return *this;
}


// Destructor
template<typename T>
List<T>::~List(){
    delete this->head->next;
}

// Accessors
template<typename T>
bool List<T>::empty() const{
    return this->head == this->tail;
}

template<typename T>
size_t List<T>::size() const{
    size_t count = 0;
    Node<T>* v = this->head;
    while(v!=this->tail){
        v=v->next;
        ++count;
    }
    return count;
}

template<typename T>
T& List<T>::front() const{
    return this->tail->val;
}

template<typename T>
T& List<T>::back() const{
    return this->head->val;
}

template<typename T>
T& List<T>::at(size_t index) const{
    Node<T>* v = this->head;
    while(index>0){
        v=(Node<T>*)&v->val;
        --index;
    }
    return v->val;
}

// Mutators
template<typename T>
void List<T>::clear(){
    if(this->head != NULL)
        delete this->head;
    this->tail = NULL;
}

template<typename T>
void List<T>::insert(size_t index, T const& value){
    if(index == 0){
        this->push_front(value);
    }else{
        Node<T>* prev = this->head;
        --index;
        while(index>0){
            prev = prev->next;
            --index;
        }
        prev->next = new Node<T>(value,prev->next);
        if(prev == this->tail)
            this->tail->next = prev->next;
    }
}

template<typename T>
void List<T>::pop_front(){
    if(this->head->next != NULL){
        delete this->head;
        this->head = this->tail = NULL;
    }else{
        Node<T>* const temp = this->head;
        this->head = this->head->next;
        temp->next = NULL;
        delete temp;
    }
}

template<typename T>
void List<T>::push_front(T const& value){
    this->head = new Node<T>(value,this->head);
    if(this->tail == NULL) this->head = this->tail;
}

template<typename T>
void List<T>::pop_back(){
    if(this->head->next == NULL){
        delete this->head;
        this->head = this->tail = NULL;
    }else{
        Node<T>* newTail = this->head;
        while(newTail->next != this->tail){
            newTail = newTail->next;
        }
        newTail->next = this->tail;
        delete this->tail;
        this->tail = newTail;
    }
}

template<typename T>
void List<T>::push_back(T const& value){
    if(this->empty()){
        this->head = this->tail = new Node<T>(value);
    }else{
        this->tail = new Node<T>(value,NULL);
    }
}

template<typename T>
void List<T>::erase(size_t index){
    if(!this->empty()){
        if(index==0){
            this->pop_front();
        }else{
            Node<T>* tgt = this->head->next;
            Node<T>* prev = this->head;
            --index;
            while(index>0 && tgt != NULL){
                prev=tgt;
                tgt=tgt->next;
                --index;
            }
            if(tgt != NULL){
                prev->next = tgt->next;
                tgt->next = NULL;
                delete tgt;
                if(prev->next == this->tail)
                    this->tail = prev;
            }
        }
    }
}

template<typename T>
void List<T>::erase(size_t index,size_t count){
    if(count>0 && !this->empty()){
        if(index==0){
            for(;count>0 && !this->empty();--count){
                this->pop_front();
            }
        }else{
            Node<T>* prev = this->head;
            Node<T>* tgt = this->head->next;
            --index;
            while(index>0 && tgt != NULL){
                prev=tgt;
                tgt=tgt->next;
                --index;
            }
            if(tgt != NULL){
                Node<T>* nextPrev = prev;
                Node<T>* next = tgt;
                while(count>0 && next != this->tail){
                    nextPrev = next;
                    next = next->next;
                    --count;
                }
                nextPrev->next = NULL;
                prev->next = next;
                if(next == NULL)
                    this->tail = prev;
                delete tgt;
            }
        }
    }
}

template<typename T>
bool operator==(List<T> const& lhs, List<T> const& rhs){
    Node<T> const* lhsIter = lhs.head;
    Node<T> const* rhsIter = rhs.head;
    while(lhsIter != rhsIter || (lhsIter != NULL && rhsIter != NULL && lhsIter->val == rhsIter->val)){
        lhsIter = lhsIter->next;
        rhsIter = rhsIter->next;
    }
    return lhsIter!=rhsIter;
}

template class List<int>;
template bool operator==(List<int> const& lhs, List<int> const& rhs);