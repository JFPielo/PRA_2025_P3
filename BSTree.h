#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T> 
class BSTree {
    private:
        //miembros privados
        int nelem;
        BSNode<T> *root;

    public:
        // miembros públicos
        BSTree() {
            this->nelem = 0;
            this->root = nullptr;
        }
        
        int size() const {
            return this->nelem;
        }

        T search(T e) {
            return search(this->root, e)->elem;
        }

        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr) {
                throw runtime_error("Elemento no encontrado");
            } else if(n->elem < e ){
                return search(n->right, e);
            } else if(n->elem > e ){
                return search(n->left, e);
            } else {
                return n;
            }
        }

        T operator[](T e) const {
            return search(e);
        }

        void insert(T e) {
            this->root = insert(this->root, e);
            this->nelem++;  // y también incrementa el contador
        }

        BSNode<T>* insert(BSNode<T>* n, T e){
            if (n == nullptr) {
                return new BSNode<T>(e);
            } else if(n->elem == e){
                throw runtime_error("Elemento duplicado");
            } else if(n->elem < e){
                n->right = insert(n->right, e);
            } else {
                n->left = insert(n->left, e);
            }
            return n;
        }   

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
            bst.print_inorder(out, bst.root);
            return out;
        }

        void print_inorder(std::ostream &out, BSNode<T>* n) const {
            if (n != nullptr) {                    // if n != null
                print_inorder(out, n->left);       // inorden(n.first_descendant(), P)
                out << n->elem << " ";             // P(n) - procesar el nodo
                print_inorder(out, n->right);      // inorden(remaining_descendants)
            }
        }

        void remove(T e) {
            root = remove(this->root, e);
            this->nelem--;  
        }

        BSNode<T>* remove(BSNode<T>* n, T e){
            if(n == nullptr){
                throw runtime_error("Elemento no encontrado");
            } else if(n->elem < e){
                n->right = remove(n->right, e);
            } else if(n->elem > e){
                n->left = remove(n->left, e);
            } else {
                // Nodo encontrado
                if (n->left != nullptr && n->right != nullptr) {
                    // 2 descendientes
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                } else {
                    // 1 o 0 descendientes
                    n = (n->left != nullptr) ? n->left : n->right;
                }
            }
            return n;
        }

        T max(BSNode<T>* n) const{
            if(n == nullptr){
                throw runtime_error("Árbol vacío");
            } else if (n->right != nullptr){
                return max(n->right);
            } else {
                return n->elem;
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if(n->right == nullptr) {
                return n->left;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }

        ~BSTree() { 
            delete_cascade(root); 
        }

        void delete_cascade(BSNode<T>* n){
            if(n != nullptr){
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }


};

#endif