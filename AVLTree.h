#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <ostream>
#include <iomanip>
#include <fstream>
#include <iostream>


template <typename Key, typename Info>
class AVLTree {
private:
    struct Node {
        Key key;
        Info info;
        short int balanceFactor;
        Node* right;
        Node* left;
        Node() { this->left = nullptr; this->right = nullptr; };
        Node(Key newkey, Info newinfo) {
            this->key = newkey;
            this->info = newinfo;
            this->balanceFactor = 0;
            this->left = nullptr;
            this->right = nullptr;
        }
    };
    unsigned int sizer;
    Node* root;

public:
    AVLTree() { root = nullptr; sizer = 0; }
    ~AVLTree() { clear(root); }

    size_t size() const;

    void recursionInsert(Node*& subptr, Key const& key, Info const& info);
    void insert(Key const& key, Info const& info);

    Info* find(Key const& key);

    std::string SwitchToString(Node* subtree, std::string to_string) const;
    std::string toString() const;

    void clear(Node*& subptr);
    void clear();
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

    int setFactor(Node* const& subptr);

    void Left_Rotation(Node* ptr);
    void Right_Rotation(Node* ptr);

};

template <typename Key, typename Info>
void AVLTree<Key, Info>::clear(Node*& subptr) {
    if (subptr == nullptr) {
        return;
    }
    clear(subptr->left);
    clear(subptr->right);
    delete subptr;
    sizer = 0;
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::clear() {
    clear(root);
}

template <typename Key, typename Info>
size_t AVLTree<Key, Info>::size() const {
    return sizer;
}

template <typename Key, typename Info>
Info* AVLTree<Key, Info>::find(Key const& key) {
    Node* current = root;
    if (root == nullptr) {
        return nullptr;
    }
    while (current != nullptr && current->key != key) {
        if (key > current->key) {
            current = current->right;
        }
        else if (key < current->key) {
            current = current->left;
        }
    }
    if (current == nullptr) {
        return nullptr;
    }
    return &(current->info);

}

template <typename Key, typename Info>
void AVLTree<Key, Info>::recursionInsert(Node*& subptr, Key const& key, Info const& info) {
    if (subptr == nullptr) {
        subptr = new Node(key, info);
        sizer++;
        setFactor(root);
    }
    else if (subptr->key == key) {
        subptr->info++;
        return;
    }
    else if (key < subptr->key)
        recursionInsert(subptr->left, key, info);
    else if (key > subptr->key)
        recursionInsert(subptr->right, key, info);

}

template <typename Key, typename Info>
void AVLTree<Key, Info>::insert(Key const& key, Info const& info) {
    recursionInsert(root, key, info);
}

template <typename Key, typename Info>
int AVLTree<Key, Info>::setFactor(Node* const& subptr) {

    if (subptr == nullptr) {
        return 0;
    }

    int left_height = setFactor(subptr->left);
    int right_height = setFactor(subptr->right);

    subptr->balanceFactor = left_height - right_height;

    if (subptr->balanceFactor == -2 && subptr->right->balanceFactor == -1) {
        Left_Rotation(subptr);
        return setFactor(subptr);
    }
    if (subptr->balanceFactor == 2 && subptr->left->balanceFactor == 1) {
        Right_Rotation(subptr);
        return setFactor(subptr);
    }
    if (subptr->balanceFactor == -2 && subptr->right->balanceFactor == 1) {
        Right_Rotation(subptr->right);
        Left_Rotation(subptr);
        return setFactor(subptr);
    }
    if (subptr->balanceFactor == 2 && subptr->left->balanceFactor == -1) {
        Left_Rotation(subptr->left);
        Right_Rotation(subptr);
        return setFactor(subptr);
    }

    if (left_height > right_height)
        return(left_height + 1);
    else return(right_height + 1);
}

template <typename Key, typename Info>
void AVLTree<Key, Info>::Left_Rotation(Node* ptr) {
    if (ptr == root) {
        root = ptr->right;
        ptr->right = ptr->right->left;
        root->left = ptr;
        return;
    }

    Node* prev_ptr = root;
    while (prev_ptr->right != ptr && prev_ptr->left != ptr) {
        if (ptr->key < prev_ptr->key)
            prev_ptr = prev_ptr->left;
        else if (ptr->key > prev_ptr->key)
            prev_ptr = prev_ptr->right;
    }

    if (prev_ptr->right == ptr) {
        prev_ptr->right = ptr->right;
    }
    if (prev_ptr->left == ptr) {
        prev_ptr->left = ptr->right;
    }
    Node* tmp = ptr->right->left;
    ptr->right->left = ptr;
    ptr->right = tmp;
    

}

template <typename Key, typename Info>
void AVLTree<Key, Info>::Right_Rotation(Node* ptr) {
    if (ptr == root) {
        root = ptr->left;
        ptr->left = ptr->left->right;
        root->right = ptr;
        return;
    }

    Node* prev_ptr = root;
    while (prev_ptr->right != ptr && prev_ptr->left != ptr) {
        if (ptr->key < prev_ptr->key)
            prev_ptr = prev_ptr->left;
        else if (ptr->key > prev_ptr->key)
            prev_ptr = prev_ptr->right;
    }

    if (prev_ptr->right == ptr)
        prev_ptr->right = ptr->left;
    if (prev_ptr->left == ptr)
        prev_ptr->left = ptr->left;
    Node* tmp = ptr->left->right;
    ptr->left->right = ptr;
    ptr->left = tmp;

}

template<typename Key, typename Info>
std::string AVLTree<Key, Info>::toString() const {
    std::string to_string;
    to_string = SwitchToString(root, to_string);
    return to_string;
}

template<typename Key, typename Info>
std::string AVLTree<Key, Info>::SwitchToString(Node* subtree, std::string to_string) const {
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
std::ostream& operator <<(std::ostream& stream, AVLTree<Key, Info> const& tree)
{
    tree.print<std::ostream>(stream);
    return stream;
}

AVLTree <std::string, int>& counter(const std::string& fileName) {
    AVLTree < std::string, int> occurance;
    std::string st;
    std::ifstream myfile;
    myfile.open(fileName);
    if (!myfile) {
        std::cout << "Their are no files of that name" << std::endl;
    }
    while (!myfile.eof()) {
        myfile >> st;
        if (occurance.find(st) != nullptr) {
            occurance.insert(st, *occurance.find(st) + 1);
        }
        else{
            occurance.insert(st, 1);
    }
    }
    return occurance;
}
