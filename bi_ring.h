
#include<iostream>
 template<typename Key,typename Info>
 class bi_ring{ // doubly linked implementation
     private:
        struct Node{
            Key key;
            Info info;
            Node* next;
            Node* prev;
        };
        Node* head;
     
     public:
     class iterator{
        private:
          //  bi_ring<Key,Info>* ring_node;
            Node* nodeIT;
            iterator(Node* new_current): nodeIT(new_current){}
            friend class bi_ring<Key,Info>;
            friend class const_iterator;
         public:

         iterator() : nodeIT(nullptr){};
         iterator(const iterator& src) : nodeIT(nullptr) {*this = src;};
         ~iterator() {this->nodeIT = nullptr;};
         const iterator & operator=(const iterator & itr);
         iterator& operator++();
         iterator& operator--();
         iterator operator++(int);
         iterator operator--(int);
         bool operator==(const iterator& itr) const;
         bool operator!=(const iterator& itr) const;
         Info& operator*();
         Info& getInfo()const;
         Key& getKey()const;
     };
     class const_iterator
       {
       private:
             Node * nodeIT;
       public:
              const_iterator() : nodeIT(nullptr) {};
              const_iterator(Node * node_nodeIT) : nodeIT(node_nodeIT) {};
              const_iterator(const const_iterator & itr) : nodeIT(itr.nodeIT) {};
              const_iterator(const iterator & itr) : nodeIT(itr.nodeIT) {};
              ~const_iterator() {this->nodeIT = nullptr;};
              
              const const_iterator& operator=(const const_iterator & itr);
              const_iterator& operator++ ();
              const_iterator& operator-- ();
              const_iterator operator++ (int);
              const_iterator operator-- (int);
              bool operator==(const const_iterator& itr) const;
              bool operator!= (const const_iterator& itr) const;
              const Info& operator* () const; 
              Info& getInfo()const;
              Key& getKey()const;         
       };  

     bi_ring():head(nullptr){};
     bi_ring(const bi_ring& src):head(nullptr) {*this = src;};
     ~bi_ring(){clear();};

     bi_ring<Key,Info>& operator=(const bi_ring<Key,Info>& src);
     unsigned int size() const;

    //  bi_ring(bi_ring&& src);
    //  bi_ring& operator=(const bi_ring&& src);

    bool IsEmpty();
    bool clear();
    void append(const Key& key, const Info& info);
    void print();

    const_iterator cbegin()const;
    const_iterator cend()const;


    iterator begin();
    iterator end();

    iterator push_front(const Key& key,const Info& info); //returns the place of the newly added Node
    iterator pop_front();//returns the second Node after the Node we remove
    iterator find(const Info& info); 
    iterator insert(iterator position,const Key& key,const Info& info);
    iterator insert_after(iterator position,const Key& key,const Info& info);
    iterator erase(iterator position);
 };

template<typename Key, typename Info>
void bi_ring<Key,Info>::print(){
    Node * current = head;
     if (IsEmpty()) {     // empty Sequenceuence
        std::cout << "The Sequenceuence is empty.";
        return;
     }

     do {            // display Nodes
        std::cout << "("<< current->key<< ","<<current->info << ")"<<"\t";
        current = current->next;
     } 
     while (current != head);      // again first Node (finished circle)
}

template<typename Key, typename Info>
bool bi_ring<Key,Info>::IsEmpty(){
    return(head == nullptr);
}

template<typename Key, typename Info>
bool bi_ring<Key,Info>::clear(){

    if(IsEmpty()){
        return true;
    }
    Node* current;
    head->prev->next = nullptr;
    do{
    current = head;
    head = head->next;
    delete current;
    }while(head != nullptr);
    return true;
}

template <typename Key, typename Info>
void bi_ring<Key, Info>::append(const Key& key, const Info& info){
    Node *new_node = new Node;
    new_node->key = key;
    new_node->info = info;

    if(IsEmpty()){
        head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
    }
    else{
        new_node->next = head;
        new_node->prev = head->prev;
        head->prev->next = new_node;
        head->prev = new_node;
    }

}

template<typename Key, typename Info>
unsigned int bi_ring<Key,Info>::size() const{
    if(head==nullptr){
        return 0;
    }
    unsigned int count = 0;
    Node* current = head;
    do{
        count++;
        current = current->next;
    }while(current!=head);
    return count;
}

template<typename Key, typename Info>
bi_ring<Key,Info>& bi_ring<Key,Info>::operator=(const bi_ring<Key,Info>& src){
    clear();
    Node* current = src.head;
    do
    {
        append(current->key,current->info);
        current= current->next;
    }while(current != src.head);
    return *this;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::begin(){
    return iterator(head);
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::const_iterator bi_ring<Key,Info>::cbegin()const{
    return iterator(head);
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::end(){
    return iterator(head->prev);
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::const_iterator bi_ring<Key,Info>::cend()const{
    return iterator(head->prev);
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::insert_after(iterator position,const Key& key,const Info& info){
    if(position.nodeIT == nullptr && head != nullptr){
        return position;
    }

    
    Node* current = position.nodeIT;
    Node* new_node = new Node;
    new_node->key = key;
    new_node->info = info;

    if(IsEmpty()){
        head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        position = iterator(new_node);
        return position;
    }

    new_node->next = current->next;
    new_node->prev = current;
    current->next->prev = new_node;
    current->next = new_node;

    return (++position);
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::insert(iterator position,const Key& key,const Info& info){
    if(position.nodeIT == nullptr && head != nullptr){
        return position;
    }
    Node* current = position.nodeIT;
    Node* new_node = new Node;
    new_node->key = key;
    new_node->info = info;

    if(IsEmpty()){
        head = new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        position = iterator(new_node);
        return position;
    }
    
    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
    
    return (--position);
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::erase(iterator position){
 
    if (position.nodeIT == nullptr) { 
        return position;
    }
        
     Node* current = position.nodeIT;
        
     
     if (current == head && current->next != head){ 
        head = head->next;
     }
     position--;              
     current->prev->next = current->next;
     current->next->prev = current->prev;
     delete current;
     return position;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::iterator::operator++(int){
    iterator temp = *this;
    nodeIT = nodeIT->next;
    return temp;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::iterator::operator--(int){
    iterator temp = *this;
    nodeIT = nodeIT->prev;
    return temp;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator& bi_ring<Key,Info>::iterator::operator++(){
    nodeIT = nodeIT->next;
    return *this;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator& bi_ring<Key,Info>::iterator::operator--(){
    nodeIT = nodeIT->prev;
    return *this;
}

template<typename Key, typename Info>
bool bi_ring<Key,Info>::iterator::operator!=(const iterator& itr)const{
    return nodeIT != itr.nodeIT;
}

template<typename Key, typename Info>
bool bi_ring<Key,Info>::iterator::operator==(const iterator& itr)const{
    return nodeIT == itr.nodeIT;
}

template<typename Key, typename Info>
Info& bi_ring<Key,Info>::iterator::operator*(){
    return nodeIT->info;
}

template<typename Key, typename Info>
Info& bi_ring<Key,Info>::iterator::getInfo() const{
    return nodeIT->info;
}

template<typename Key, typename Info>
Key& bi_ring<Key,Info>::iterator::getKey() const{
    return nodeIT->key;
}

template<typename Key, typename Info>
const typename bi_ring<Key,Info>::iterator& bi_ring<Key,Info>::iterator::operator=(const iterator& itr){
    nodeIT = itr.nodeIT;
    return *this;
}

template<typename Key, typename Info>
Info& bi_ring<Key,Info>::const_iterator::getInfo() const{
    return nodeIT->info;
}

template<typename Key, typename Info>
Key& bi_ring<Key,Info>::const_iterator::getKey() const{
    return nodeIT->key;
}

template<typename Key, typename Info>
const typename bi_ring<Key,Info>::const_iterator& bi_ring<Key,Info>::const_iterator::operator=(const const_iterator& itr){
    nodeIT = itr.nodeIT;
    return *this;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::const_iterator& bi_ring<Key,Info>::const_iterator::operator++(){
    nodeIT = nodeIT->next;
    return *this;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::const_iterator& bi_ring<Key,Info>::const_iterator::operator--(){
    nodeIT = nodeIT->prev;
    return *this;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::const_iterator bi_ring<Key,Info>::const_iterator::operator++(int){
    const_iterator temp = *this;
    nodeIT = nodeIT->next;
    return temp;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::const_iterator bi_ring<Key,Info>::const_iterator::operator--(int){
    const_iterator temp = *this;
    nodeIT = nodeIT->prev;
    return temp;
}

template<typename Key, typename Info>
bool bi_ring<Key,Info>::const_iterator::operator==(const const_iterator& itr)const{
    return nodeIT == itr.nodeIT;
}

template<typename Key, typename Info>
bool bi_ring<Key,Info>::const_iterator::operator!=(const const_iterator& itr)const{
    return nodeIT != itr.nodeIT;
}

template<typename Key, typename Info>
const Info& bi_ring<Key,Info>::const_iterator::operator*() const{
    return nodeIT->info;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::find(const Info& info){
    if(head != nullptr){
        iterator position = begin();
        do{
            if(*position == info){
                return position;
                
            }
            position++;
        }while(position!= begin());
    }
    return nullptr;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::pop_front(){
    iterator itr = begin();
    erase(itr);
    itr = iterator(head);
    return itr;
}

template<typename Key, typename Info>
typename bi_ring<Key,Info>::iterator bi_ring<Key,Info>::push_front(const Key& key,const Info& info){
    Node* new_node = new Node;
    new_node->key = key;
    new_node->info = info;
    if(IsEmpty()){
        head =  new_node;
        new_node->next = new_node;
        new_node->prev = new_node;
        return iterator(new_node);
    }
    new_node->next = head;
    new_node->prev = head->prev;
    head->prev->next = new_node;
    head->prev = new_node;
    head = new_node;
    return iterator(new_node);
} 

template<typename Key, typename Info>

 std::ostream& operator<<(std::ostream& os, const bi_ring<Key,Info>& src){
     os << "[";
     for(auto it = src.cbegin(); it!= src.cend(); ++it)
        os << *it << ",";
        return os << "]";
}

template<typename Key,typename Info>// we copy fcnt Node from first ring then we copy scnt Node from the ring
bi_ring<Key,Info>shuffle(const bi_ring<Key,Info>& first, unsigned int fcnt, const bi_ring<Key,Info>& second, unsigned int scnt, unsigned int reps){
    bi_ring<Key,Info> new_ring;
    typename bi_ring<Key,Info>::const_iterator first_itr = first.cbegin();
    typename bi_ring<Key,Info>::const_iterator second_itr = second.cbegin();
    if(first.size() == 0 && second.size() == 0){
        return new_ring;
    }
    for(unsigned int i = 0; i < reps; i++){
        for(unsigned int k = 0; k < fcnt; k++){
            new_ring.append(first_itr.getKey(), first_itr.getInfo());
            first_itr++;
        }
        for(unsigned int t = 0; t < scnt; t++){
            new_ring.append(second_itr.getKey(), second_itr.getInfo());
            second_itr++;
        }
        
    }
    return new_ring;
}
  