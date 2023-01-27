#include<iostream>
template <typename Key, typename Info>

class Sequence
{

public:

    struct Thing
    {
        Key key;
        Info info;

    };
    
    Sequence();
    Sequence(const Sequence &src);
    ~Sequence();

    Sequence<Key, Info>& operator=(const Sequence<Key,Info> &src);//Assignment operator
    Sequence<Key, Info>& addition(const Sequence<Key,Info> &src);// Add two linked lists together

    Thing& getThingKey(const Key& key);
    Thing getThing(int index) const;
    void print();
    void append(const Key &key, const Info &info);// add elements from the back of the linked list
    void push_front(const Key &key, const Info &info);// add elements from the front of the linked list
    void insert(const Key &key, const Info &info, unsigned int index);
    void removeAll();// removing all elements from the linked list
    bool removeAt(const Key &where, const Info &what, unsigned int occurance = 0); // remove the element at a specific location according to the KEY and INFO
    bool pop_back();// remove the last element in the linked list
    bool pop_front();// remove the first element in the linked list
    bool searchFor(const Key &key, const Info &info);// search if the element exists in the linked list
    bool isEmpty();// check if the list if empty
    unsigned int size() const;// the size of the list

private:
    struct Node
    {
        Thing thing;
        Node *next;

    };

    Node *head = nullptr;
};

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence()
{
    head = nullptr;
}

template <typename Key, typename Info>
Sequence<Key, Info>::Sequence(const Sequence &src)
{
    if (head!= nullptr)
    {
        return;
    }
    
    Node* current = src.head;
    while (current!= nullptr)
    {
        this->append(current->thing.key,current->thing.info);
        current = current->next;
    }

}

template <typename Key, typename Info>
Sequence<Key, Info>::~Sequence()
{
    Node *current = head;
    while (current != nullptr)
    {
        Node *tmp = current->next;
        delete current;
        current = tmp;
    }
    head = nullptr;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::push_front(const Key &key, const Info &info)
{
    Node *new_node = new Node;
    new_node->next = head;
    new_node->thing.info = info;
    new_node->thing.key = key;
    head = new_node;

}

template <typename Key, typename Info>
bool Sequence<Key, Info>::searchFor(const Key &key, const Info &info)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->thing.key == key && current->thing.info == info)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_front()
{
    if (head == nullptr)
    {
        return false;
    }
    if (head->next == nullptr)
    {
        delete head;
        return true;
    }

    Node *current = head;
    if (current != nullptr)
    {
        head = current->next;
        delete current;
        return true;
    }
    return false;
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::isEmpty()
{
    if (head == nullptr)
    {
        return true;
    }
    return false;
}
template <typename Key, typename Info>
bool Sequence<Key, Info>::pop_back()
{
    Node *current = head;
    if (head != nullptr)
    {
        while (current->next->next != nullptr)
        {
            current = current->next;
        }
        delete current->next;
        current->next = nullptr;
        return true;
    }
    else if (head->next == nullptr)
    {
        delete head;
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::print()
{
    Node *current = head;
    while (current != nullptr)
    {
        std::cout << "(" << current->thing.key << ", " << current->thing.info << ")";
        current = current->next;
    }
}

template <typename Key, typename Info>
unsigned int Sequence<Key, Info>::size() const
{
    int count = 0;
    Node *current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::insert(const Key &key, const Info &info, unsigned int index)
{
    if (head != nullptr)
    {
        if (index < 1 ||index > size()+1)
    {
        throw std::invalid_argument("Invalid index");
    }
    
    if (index == 1)
    {
        push_front(key, info);
        return;
    }
    
    if (index == size()+1)
    {
        append(key, info);
        return;
    }
        Node *current = head;
        Node *new_node = new Node;
        new_node->thing.key = key;
        new_node->thing.info = info;
        for (unsigned int i = 0; i < (index-2); i++)
        {
            current = current->next;
        }
        Node *tmp = current->next;
        current->next = new_node;
        new_node->next = tmp;
    }
}

template <typename Key, typename Info>
bool Sequence<Key, Info>::removeAt(const Key &where, const Info &what, unsigned int occurance)
{
    if (isEmpty() == 1)
    {
        return false;
    }
    Node *current = head;
    Node *tmp;
    unsigned int occur = 0;
    if (searchFor(where, what) == true)
    {
        if (head->thing.key == where && head->thing.info == what)
        {
            Node*Htemp = head;
            head = head->next;
            delete Htemp;
            return true;
        }
        
        while (current->next != nullptr)
        {
            if (current->next->thing.key == where && current->next->thing.info == what)
            {
                occur++;
                if (occur == occurance)
                {
                    if(current->next->next == nullptr){
                        Node* Ttmp = current->next;
                        delete Ttmp;
                        current->next = nullptr;
                        return true;
                    }else{
                    tmp = current->next;
                    current->next = current->next->next;
                    delete tmp;
                    return true;
                    }
                }
            }
            current = current->next;
        }
    }else
    {
        return false;
    }
    return false;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::removeAll()
{
    Node *current = head;
    Node *next = nullptr;
    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

template <typename Key, typename Info>
void Sequence<Key, Info>::append(const Key &key, const Info &info)
{
    if(head == nullptr){
        push_front(key,info);
        return;
    }
    Node *new_node = new Node;
    new_node->thing.key = key;
    new_node->thing.info = info;
    Node *current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    new_node->next = nullptr;
    current->next = new_node;

}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key,Info>::addition(const Sequence<Key,Info> &src){
    if (this->head == nullptr)
    {
        this->operator=(src);
    }
    Node* current = src.head;
    while (current!= nullptr)
    {
        this->append(current->thing.key, current->thing.info);
        current = current->next;
    }

    return *this;
    
}

template <typename Key, typename Info>
Sequence<Key, Info>& Sequence<Key,Info>::operator=(const Sequence<Key,Info> &src)
{
    this->removeAll();
    Node* current = src.head;
    while (current!= nullptr)
    {
        this->append(current->thing.key,current->thing.info);
        current = current->next;
    }
    return *this;
}

template <typename Key, typename Info>
typename Sequence<Key,Info>::Thing& Sequence<Key,Info>::getThingKey(const Key& key){
    Node* current = head;
    while (current != nullptr)
    {
        if (current->thing.key == key)
        {
            return (current->thing);
        }
        current = current->next;
    }
    append(key,*(new Info));
    return getThingKey(key);
}

template <typename Key, typename Info>
typename Sequence<Key,Info>::Thing Sequence<Key,Info>::getThing(int index) const{
    if (index<1 || index > size())
    {
        throw std::invalid_argument("Invalid index");
    }
    Node* current = head;
    int idx=1;
    while (current != nullptr)
    {
        if (idx == index)
        {
            return (current->thing); 
        }
        current= current->next;
        idx++;
    }
   return (current->thing);
}

template <typename Key, typename Info>
Sequence<Key, Info> join(const Sequence<Key, Info>& left,  const Sequence<Key, Info>& right, Info (*aggregate)(const Info& left, const Info& right))
{
    if (left.size() < 1)
    {
        return right;
    }if (right.size() < 1)
    {
        return left;
    }
    Sequence<Key,Info> new_sequence;
    for (unsigned int i = 1; i <= left.size(); i++)
    {
        Key left_key = left.getThing(i).key;
        new_sequence.getThingKey(left_key).info = aggregate(new_sequence.getThingKey(left_key).info, left.getThing(i).info);
    }

    for (unsigned int j = 1; j <= right.size(); j++)
    {
        Key right_key = right.getThing(j).key;
        new_sequence.getThingKey(right_key).info = aggregate(new_sequence.getThingKey(right_key).info, right.getThing(j).info);
    }
    
    return new_sequence;
}
