#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>


template <typename Key, typename Info>
class BinarySearchTree {
private:
    struct Node {
        Key key;
        Info info;
        Node* left;
        Node* right;
        Node() { this->left = nullptr; this->right = nullptr; };
        Node(Key newkey, Info newinfo) {
            this->key = newkey;
            this->info = newinfo;
            this->left = nullptr;
            this->right = nullptr;
        }
    };
    unsigned int sizer = 0;
    Node* root;
public:
    BinarySearchTree(){ root = nullptr; };
    ~BinarySearchTree() { clear(root); }


    size_t size() const;

    void insert(Key const& key, Info const& info);

    void remove(Key const& key);

    Info* find(Key const& key);

    std::string toString() const;

    void clear(Node*& subptr);

    template<typename StreamType>
    void print(StreamType& stream) const {
        if (root != nullptr) recprint(stream, root, 0);
    }

    template<typename StreamType>
    void recprint(StreamType& stream, Node* node, int space) const {
        stream << "[" << node->key << ", " << node->info << "]\n";
        space++;

        if (node->left != nullptr) {
            for (int i = 0; i < space; i++) {
                stream << "    ";
            }
            stream << "L: ";
            recprint(stream, node->left, space);

        }
        if (node->right != nullptr) {
            for (int i = 0; i < space; i++) {
                stream << "    ";
            }
            stream << "R: ";
            recprint(stream, node->right, space);
        }

    }

    int height(Node* ptr);

    std::string SwitchToString(Node* subtree, std::string to_string) const;


};

template <typename Key, typename Info>
void BinarySearchTree<Key, Info>::clear(Node*& subptr) {
    if (subptr == nullptr) {
        return;
    }
    clear(subptr->left);
    clear(subptr->right);
    delete subptr;
}

template <typename Key, typename Info>
int BinarySearchTree<Key, Info>::height(Node* ptr) {
    if (ptr == NULL)
        return 0;
    else
    {

        int left_height = height(ptr->left);
        int right_height = height(ptr->right);


        if (left_height > right_height)
            return(left_height + 1);
        else return(right_height + 1);
    }
}

template <typename Key, typename Info>
void BinarySearchTree<Key, Info>::insert(Key const& key, Info const& info) {
    Node* new_node = new Node(key,info);
    if (root == nullptr) {
        root = new_node;
        sizer++;
            return;
    }
    Node* current = root;
    Node* rootOfCurr = nullptr;
    while (current != nullptr) {
        rootOfCurr = current;
        if (current->key == key) {
            current->info++;
            return;
        }
        if (key > current->key) {
            current = current->right;
        }
        else if (key < current->key) {
            current = current->left;
        }
    }
    if (key > rootOfCurr->key) {
        rootOfCurr->right = new_node;
        sizer++;
    }
    else if (key < rootOfCurr->key) {
        rootOfCurr->left = new_node;
        sizer++;
    }
}

template <typename Key, typename Info>
void BinarySearchTree<Key, Info>::remove(Key const& key) {
    Node* current = root;
    Node* rootOfCurr = nullptr;
    
    while (current != nullptr && current->key != key) {
        rootOfCurr = current;
        if (key > current->key) {
            current = current->right;
        }
        else {
            current = current->left;
        }
    }
    if (current == nullptr) {
        return;
    }
    else {
        /// no children
        if (current->right == nullptr && current->left == nullptr) {
            if(rootOfCurr->right == current){
                 rootOfCurr->right = nullptr;
             }
             if(rootOfCurr->left == current){
                 rootOfCurr->left = nullptr;
             }
            delete current;
            return;
            sizer--;
        }
        ///one child
        if (current->right == nullptr || current->left == nullptr) {

            Node* tmp = new Node;
            if (current->right == nullptr) {
                tmp = current->left;
            }
            if (current->left == nullptr) {
                tmp = current->right;
            }
            if (rootOfCurr->right == current) {
                rootOfCurr->right = tmp;
            }
            if (rootOfCurr->left == current) {
                rootOfCurr->left = tmp;
            }
            delete current;
            sizer--;
        }
        ///two children
        else {
            Node* tmpPrev = nullptr;
            Node* tmp = current->right;

            while (tmp->left != nullptr) {
                tmpPrev = tmp;
                tmp = tmp->left;
            }
            
            current->key = tmp->key;
            current = tmp;
            sizer--;

        }
    }
}

template <typename Key, typename Info>
Info* BinarySearchTree<Key, Info>::find(Key const& key) {
    Node* current = root;
    if (root == nullptr) {
        return nullptr;
    }
    while (current != nullptr && current->key != key) {
        if (key > current->key) {
            current = current->right;
        }
        else if(key<current->key) {
            current = current->left;
        }
    }
    if (current == nullptr) {
        return nullptr;
    }
       return &(current->info);
    
}

template <typename Key, typename Info>
size_t BinarySearchTree<Key, Info>::size() const {
    return sizer;
}

template<typename Key, typename Info>
std::string BinarySearchTree<Key, Info>::toString() const {
    std::string to_string;
    to_string = SwitchToString(root, to_string);
    return to_string;
}
template<typename Key, typename Info>
std::string BinarySearchTree<Key, Info>::SwitchToString(Node* subtree, std::string to_string) const {
    if (subtree == nullptr) return to_string;
    else {
        to_string += "([";
        to_string += std::to_string(subtree->key);
        to_string += ",";
        to_string += std::to_string(subtree->info);
        to_string += "],";
    }
    if (subtree->left != nullptr) {
        to_string = SwitchToString(subtree->left, to_string);
       
    } to_string += ",";
    if (subtree->right != nullptr) {
        to_string = SwitchToString(subtree->right, to_string);
        
    }to_string += ")";
    return to_string;
}

template<typename Key, typename Info>
std::ostream& operator <<(std::ostream& stream, BinarySearchTree<Key, Info> const& tree)
{
    tree.print<std::ostream>(stream);
    return stream;
}

