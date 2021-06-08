#include <queue>
#include <map>
#include <iostream>
#include <string>

namespace ariel{
    template <typename T>
    class BinaryTree{
    private:
        struct Node{
            Node *left;
            Node *right;
            T value;           
            explicit Node(T val = 0, Node *l = nullptr, Node *r = nullptr) : value(val), left(l), right(r){};
            friend std::ostream &operator<<(std::ostream &out, const Node &n){return out;}
        };
        Node *root;
        void copy_tree(Node **newer, Node *other){
            if (other == nullptr){return;}
            *newer = new Node(other->value);
            copy_tree(&((*newer)->left), other->left);
            copy_tree(&((*newer)->right), other->right);
        }
        void delete_tree(Node** n){
            if(*n == nullptr){return;}
            delete_tree(&((*n)->left));
            delete_tree(&((*n)->right));
            delete *n;
        }
    public:
        BinaryTree<T>(){this->root = nullptr;}
        BinaryTree<T>(BinaryTree<T> &other){
            if (other.root == nullptr){this->root = nullptr;}
            else{copy_tree(&this->root, other.root);}
        }
        BinaryTree(BinaryTree<T> &&other) noexcept{
            this->root = other.root;
            other.root = nullptr;
        }
        BinaryTree &operator=(BinaryTree<T> &&bt) noexcept{
            if (this->root){delete this->root;}
            this->root = bt.root;
            bt.root = nullptr;
            return *this;
        }
        BinaryTree<T> &operator=(const BinaryTree<T> &other){
            if (this != &other){copy_tree(&this->root, other.root);}
            return *this;
        }
        class iterator{
        private:
            std::queue<Node *> q;
            Node *current;
            void preorder(Node *n){
                if (n == nullptr){return;}
                this->q.push(n);
                preorder(n->left);
                preorder(n->right);
            }
            void postorder(Node *n){
                if (n == nullptr){return;}
                postorder(n->left);
                postorder(n->right);
                this->q.push(n);
            }
            void inorder(Node *n){
                if (n == nullptr){return;}
                inorder(n->left);
                this->q.push(n);
                inorder(n->right);
            }

        public:
            explicit iterator(const std::string &type, Node *pTree = nullptr) : current(pTree){
                if (current != nullptr){
                    if (type == "pre"){preorder(this->current);}
                    else if (type == "in"){inorder(this->current);}
                    else if (type == "post"){postorder(this->current);}
                    this->current = this->q.front();
                }
            }
            iterator &operator++() {
                this->q.pop();
                if (this->q.empty()){this->current = nullptr;}
                else{this->current = this->q.front();}
                return *this;
            }
            iterator operator++(int) {
                iterator temp = *this;
                this->q.pop();
                if (this->q.empty()){this->current = nullptr;}
                else{this->current = this->q.front();}
                return temp;
            }
            bool operator==(const iterator &other) const{return this->current == other.current;}
            bool operator!=(const iterator &other) const{return this->current != other.current;}
            T &operator*() const{return this->current->value;}
            T *operator->() const{return &(this->current->value);}
            Node *get_current(){return this->current;}
            friend std::ostream &operator<<(std::ostream &out, const iterator &num){
                out << *num;
                return out;
            }
        };
        BinaryTree<T>::iterator begin(){return begin_inorder();}
        BinaryTree<T>::iterator end(){return end_inorder();}
        BinaryTree<T>::iterator begin_preorder(){return iterator("pre", root);}
        BinaryTree<T>::iterator end_preorder(){return iterator("pre");}
        BinaryTree<T>::iterator begin_inorder(){return iterator("in", root);}
        BinaryTree<T>::iterator end_inorder(){return iterator("in");}
        BinaryTree<T>::iterator begin_postorder(){return iterator("post", root);}
        BinaryTree<T>::iterator end_postorder(){return iterator("post");}
        BinaryTree<T> &add_root(T root){
            if (this->root == nullptr){this->root = new Node(root);}
            else{this->root->value = root;}
            return *this;
        }
        BinaryTree<T> &add_left(T father, T l){
            if (this->root == nullptr){
                std::string exp = "The root is null";
                throw std::invalid_argument(exp);
            }
            iterator it = this->begin();
            for (; it != this->end(); ++it){
                if (*it == father){
                    if (it.get_current()->left == nullptr){it.get_current()->left = new Node(l);}
                    else{it.get_current()->left->value = l;}
                    return *this;
                }
            }
            std::string exp = "The first argument isn't in the tree";
            throw std::invalid_argument(exp);
        }
        BinaryTree<T> &add_right(T father, T r){
            if (this->root == nullptr){
                std::string exp = "The root is null";
                throw std::invalid_argument(exp);
            }
            iterator it = this->begin();
            for (; it != this->end(); ++it){
                if (*it == father){
                    if (it.get_current()->right == nullptr){it.get_current()->right = new Node(r);}
                    else{it.get_current()->right->value = r;}
                    return *this;
                }
            }
            std::string exp = "The first argument isn't in the tree";
            throw std::invalid_argument(exp);
        }
        friend std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &num){return out;}
        ~BinaryTree<T>(){
            if(this->root != nullptr){return;}
            delete_tree(&this->root);
        }
    };
}