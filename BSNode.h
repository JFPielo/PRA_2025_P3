#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

template <typename T> 
class BSNode {
    public:
        T elem;
        BSNode* left;
        BSNode* right;

        BSNode(T elem, BSNode* left = nullptr, BSNode* right = nullptr) {
            this->elem = elem;
            this->left = left;
            this->right = right;
        }

        friend std::ostream& operator<<(std::ostream &out, const BSNode<T> &bsn){
            out << "Node(" << bsn.elem << ")";
            return out;
        }
    
};

#endif