#ifndef AVLTREE
#define AVLTREE
#include "AVLnode.h"
#include <iostream>


template <class T , class M>
class AVLtree
{
    AVLnode<T,M> *root;
    AVLnode<T, M>* rotateLeftLeft(AVLnode<T, M> *vertex);
    AVLnode<T, M>* rotateRightRight(AVLnode<T, M> *vertex);
    AVLnode<T, M>* rotateLeftRight(AVLnode<T, M> *vertex);
    AVLnode<T, M>* rotateRightLeft(AVLnode<T, M> *vertex);
    int setHeight(AVLnode<T, M> *vertex);
    void rebalance(AVLnode<T, M> *vertex);
    void setBalance(AVLnode<T, M> *vertex);
    void fix_rank_after_remove(AVLnode<T,M> *ver_to_remove);

    public:
    AVLtree();
    ~AVLtree();
    AVLnode<T,M>* getRoot();
    bool addVertex(T* info, M key);
    void removeVertex(AVLnode<T,M> *new_vertex);
    AVLnode<T,M>* find(M to_find);
    void printBalance();
    void printTree();
    void inOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item));
    void postOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item));
    AVLnode<T,M>* findTheIRanke(int i);
};
/**************************************/
/*     C'tors and D'tors section      */
/**************************************/
template <class T, class M>
AVLtree<T,M>::AVLtree() : root(nullptr) {}

template <class T, class M> 
void deleteNode(AVLnode<T,M> *toDelete)
{
    if (toDelete != nullptr)
    {
        delete(toDelete);
    }
}

template <class T, class M>
AVLtree<T,M>::~AVLtree()
{
    postOrder(root, deleteNode);
}

/**************************************/
/*      Explore function section      */
/**************************************/
template <class T, class M>
void AVLtree<T,M>::inOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item)){
    if (target == nullptr)
    {
        return ;
    }
    inOrder(target->left_son,doSomething);
    doSomething(target);
    inOrder(target->right_son, doSomething);  
}

template <class T, class M>
AVLnode<T,M>* AVLtree<T,M>::getRoot(){
    return root;
}

template <class T, class M>
void AVLtree<T,M>::postOrder(AVLnode<T,M> *target, void (*doSomething)(AVLnode<T,M> *item)){
    if (target == nullptr)
    {
        return ;
    }
    postOrder(target->left_son, doSomething);
    postOrder(target->right_son ,doSomething);
    doSomething(target);
}

template<class T, class M>
AVLnode<T,M>* AVLtree<T,M>::findTheIRanke(int i)
{
    if(root == NULL) return NULL;
    i = (root->rank -i +1);
    AVLnode<T,M>* temp = root;
    while ((i > 0) && (temp != nullptr))
    {
        if (temp->left_son != nullptr)
        {
            if (temp->left_son->rank == (i-1))
            {
                return temp;
            }
            if (temp->left_son->rank > (i-1))
            {
                temp = temp->left_son;
                continue;
            }
            else
            {
                i -= (temp->left_son->rank +1);
                temp = temp->right_son;
                continue;
            }
        }
        else 
        {
            if (i == 1) // if there is no left son to temp, means temp is smallest vertex in the tree.
                        //thus, if we wish to return the 1st (adjusted to function logic) lecture, we will return temp.
            {
                return temp;
            }
            else
            {
                temp = temp->right_son;
                i--;
            }
        }
    }
    return NULL;
}

template<class T, class M>
void fixRank(AVLnode<T,M> *vertex)
{
    if (vertex->right_son != NULL)
    {
        if (vertex->left_son != NULL)
        {
            vertex->rank=vertex->left_son->rank+vertex->right_son->rank+1;
        }
        else
        {
            vertex->rank = (vertex->right_son->rank + 1);
        }
        
    }
    else if (vertex->left_son != NULL)
    {
        vertex->rank = (vertex->left_son->rank + 1);
    }
    else
    {
        vertex->rank = 1;
    }
}

/****************************************/
/*     Method implementation section    */
/****************************************/


template <class T, class M>
bool AVLtree<T,M>::addVertex(T* info ,M key)  {
    AVLnode<T, M>* new_vertex = new AVLnode<T, M>(info, key);
    if(root==NULL){
        root= new_vertex;
    }
    AVLnode<T,M> *current_vertex = root;
    AVLnode<T,M> *parent; // so we have a grasp on parent vertex
    while(true)
    {
        if(current_vertex->key == new_vertex->key){
            // current_vertex->rank+=1;
            return true; // this vertex already exists.
        } 
        current_vertex->rank+=1;//every step increases distinguished vertex's rank by 1
        parent=current_vertex;
        bool procede_left;
        if(current_vertex->key > new_vertex->key) procede_left = true;// if current node bigger then new node, we need to go left.
        else procede_left = false;// else we need to go right
        current_vertex = procede_left ? current_vertex->left_son : current_vertex->right_son;
        //when adding a new vertex it must become a leaf at first
        if(current_vertex==NULL)
        { // we made it all the way down to find new leaf spot
            if ((parent->left_son == nullptr ) && (parent->right_son == nullptr)) parent->height++;
            if(procede_left){
                parent->left_son = new_vertex;
            }
            else{
                parent->right_son = new_vertex;
            }
            new_vertex->parent=parent;
            setBalance(parent);
            new_vertex->height=0;
            //parent->height++;
            while(parent->parent != NULL && parent->height == parent->parent->height){
                //if the height of the parent of the vertex is bigger by 1 from the vertex's height then the
                //the tree above is already balanced.
                parent=parent->parent;
                rebalance(parent);
                parent->height=setHeight(parent);
            }
            while(parent != NULL)
            {
                setBalance(parent);
                parent=parent->parent;
            }
            break;
        }
    }
    return true;
}

template <class T, class M>
AVLnode<T,M>* AVLtree<T, M>::rotateLeftLeft(AVLnode<T,M> *vertex){
    AVLnode<T,M> *p=vertex->parent;
    AVLnode<T,M> *b=vertex->left_son;
    if(b->right_son!=NULL) b->right_son->parent=vertex;
    vertex->left_son = b->right_son;
    b->right_son=vertex;
    vertex->parent=b;
    b->parent=p;
    if(p!=NULL){
        if(p->left_son==vertex){
            p->left_son=b;
        }
        else{
            p->right_son=b;
        }
    }
    else{
        root=b;
    }
    vertex->height = setHeight(vertex);
    b->height=setHeight(b);
    setBalance(vertex);
    setBalance(b);
    fixRank(vertex);
    fixRank(b);
    return b;
}

template <class T, class M>
AVLnode<T,M>* AVLtree<T,M>::rotateRightRight(AVLnode<T,M> *vertex){
    AVLnode<T,M> *p=vertex->parent;
    AVLnode<T,M> *c=vertex->right_son;
    if(c->left_son!=NULL) c->left_son->parent=vertex;
    vertex->right_son = c->left_son;
    c->left_son=vertex;
    vertex->parent=c;
    c->parent=p;
    if(p!=NULL){
        if(p->right_son==vertex){
            p->right_son=c;
        }
        else{
            p->left_son=c;
        }
    }
    else
    {
        root = c;
    }
    vertex->height = setHeight(vertex);
    c->height=setHeight(c);
    setBalance(vertex);
    setBalance(c);
    fixRank(vertex);
    fixRank(c);
    return c;
    
}

template<class T, class M>
AVLnode<T,M>* AVLtree<T,M>::rotateLeftRight(AVLnode<T,M> *vertex){
    vertex->left_son=rotateRightRight(vertex->left_son);
    rotateLeftLeft(vertex);
    return vertex;
}

template<class T, class M>
AVLnode<T,M>* AVLtree<T,M>::rotateRightLeft(AVLnode<T,M> *vertex){
    vertex->right_son=rotateLeftLeft(vertex->right_son);
    rotateRightRight(vertex);
    return vertex;
}

template<class T, class M>
int AVLtree<T,M>::setHeight(AVLnode<T,M> *vertex){
    if(vertex==NULL){
        return -1;
    }
    if ( vertex->left_son == nullptr && vertex->right_son == nullptr)
    {
        return 0;
    }
    else if(vertex->left_son == nullptr)
    {
        return (vertex->right_son->height +1);
    }
    else if (vertex->right_son == nullptr)
    {
        return (vertex->left_son->height +1);
    }
    if ((vertex->left_son->height) > (vertex->right_son->height))
    {
        return vertex->left_son->height;
    }
    else
    {
        return vertex->right_son->height ;
    }
}

template <class T, class M>
void AVLtree<T,M>::setBalance(AVLnode<T,M> *vertex) {
    if ( vertex->left_son == nullptr && vertex->right_son == nullptr)
    {
        vertex->balance=0;
        return;
    }
    else if(vertex->left_son == nullptr)
    {
        vertex->balance = -1 - vertex->right_son->height;
        return;
    }
    else if (vertex->right_son == nullptr)
    {
        vertex->balance = vertex->left_son->height + 1;
        return;
    }
    else vertex->balance = vertex->left_son->height - vertex->right_son->height;
}

template <class T, class M>
void AVLtree<T,M>::rebalance(AVLnode<T,M> *vertex){
//    int prev_balace= vertex->balance;
    setBalance(vertex);
    if(vertex->balance==-2){
        vertex->right_son->balance<=0 ? rotateRightRight(vertex) : rotateRightLeft(vertex);
    }
    if(vertex->balance==2){
        vertex->left_son->balance>=0 ? rotateLeftLeft(vertex) : rotateLeftRight(vertex);
    }
}

template <class T, class M>
void printBalance(AVLnode<T,M> *vertex){
 if (vertex != NULL) {
        printBalance(vertex->left);
        std::cout << vertex->balance << " ";
        printBalance(vertex->right);
    }
}

template <class T, class M>
void AVLtree<T,M>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}

template <class T, class M>
void AVLtree<T,M>::fix_rank_after_remove(AVLnode<T,M> *ver_to_remove)
{
    AVLnode<T,M> *temp = ver_to_remove;
    while (temp->parent != nullptr)
    {
        (temp->parent->rank)--;
        temp = temp->parent;
    }
}

template <class T, class M>
void AVLtree<T,M>::removeVertex(AVLnode<T,M> *ver_to_remove)
{
    if (ver_to_remove == NULL) return;
    if(ver_to_remove->parent==nullptr && ver_to_remove->right_son==nullptr && ver_to_remove->left_son==nullptr){
        if (ver_to_remove == root)
        {
            root = nullptr;
        }
        delete(ver_to_remove);
        return; 
    }
    AVLnode<T,M> *to_fix;
    if ((ver_to_remove->right_son == nullptr) &&(ver_to_remove->left_son == nullptr))
    {
        fix_rank_after_remove(ver_to_remove);
        if (ver_to_remove->parent != nullptr)
        {
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = nullptr;
            }
            else 
            {
                ver_to_remove->parent->left_son = nullptr;
            }
        }
        to_fix = ver_to_remove->parent;
        if (ver_to_remove == root)
        {
            root = NULL;
        }
    }
    else if ((ver_to_remove->right_son == nullptr)  && !(ver_to_remove->left_son == nullptr))
    {
        fix_rank_after_remove(ver_to_remove);
        if (ver_to_remove->parent != nullptr)
        {
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = ver_to_remove->left_son;
            }
            else 
            {
                ver_to_remove->parent->left_son = ver_to_remove->left_son;
            }
        }
        ver_to_remove->left_son->parent = ver_to_remove->parent;
        to_fix = ver_to_remove->left_son;
        if (ver_to_remove == root)
        {
            root = ver_to_remove->left_son;
        }
    }
    else if (!(ver_to_remove->right_son == nullptr)  && (ver_to_remove->left_son == nullptr))
    {
        fix_rank_after_remove(ver_to_remove);
        if (ver_to_remove->parent != nullptr)
        {
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = ver_to_remove->right_son;
            }
            else 
            {
                ver_to_remove->parent->left_son = ver_to_remove->right_son;
            }
        }
        ver_to_remove->right_son->parent = ver_to_remove->parent;
        to_fix = ver_to_remove->right_son;
        if (ver_to_remove == root)
        {
            root = ver_to_remove->right_son;
        }
    }
    else
    {
        AVLnode<T,M> * temp1 = ver_to_remove->right_son;
        AVLnode<T,M> * temp2 = temp1->left_son;
        AVLnode<T,M> * temp3 = temp1->right_son;
        while (temp2 != nullptr)
        {
            temp3 = temp2->right_son;
            temp1 = temp2;
            temp2 = temp2->left_son;
        }
        fix_rank_after_remove(temp1);
        temp1->rank = ver_to_remove->rank;
        if(temp1->parent->right_son == temp1)
        {
            temp1->parent->right_son = temp3;
            if (temp3 != nullptr)
            {
                temp3->parent = temp1->parent;
            }
        }
        else    
        {
            temp1->parent->left_son = temp3;
            if (temp3 != nullptr)
            {
                temp3->parent = temp1->parent;
            }
        }
        temp1->right_son = ver_to_remove->right_son;
        if (temp1->right_son != nullptr)
        {
            temp1->right_son->parent = temp1;
        }
        temp1->left_son = ver_to_remove->left_son;
        if (temp1->left_son != nullptr)
        {
            temp1->left_son->parent = temp1;
        }
        if (temp1->parent == ver_to_remove)
        {
            to_fix = temp1;
        }
        else
        {
            to_fix = temp1->parent;
        }
        if (root == ver_to_remove)
        {
            root = temp1;
            temp1->parent = nullptr;
            // if (temp1->right_son != nullptr)
            // {
            //     to_fix = temp1->right_son;
            // }
            // else
            // {
            //     to_fix = temp1;
            // }
        }
        else
        {
            temp1->parent = ver_to_remove->parent;
            if(ver_to_remove->parent->right_son == ver_to_remove)
            {
                ver_to_remove->parent->right_son = temp1;
            }
            else 
            {
                ver_to_remove->parent->left_son = temp1;
            }
        }
    }
    delete(ver_to_remove);
    AVLnode<T,M> *to_fix_balance = to_fix;
    while(to_fix_balance != NULL)
    {
        to_fix_balance->height = setHeight(to_fix_balance);
        setBalance(to_fix_balance);
        to_fix_balance=to_fix_balance->parent;
    }
    while (to_fix != nullptr)
    {
        rebalance(to_fix);
        to_fix = to_fix->parent;
    }
}

template <class T, class M>
void printVertex(AVLnode<T,M> *vertex) {
    std::cout <<"key: ";
    std::cout << *(vertex->info);
    std::cout <<"hieght: ";
    std::cout <<vertex->height<< std::endl;
    std::cout <<"rank: ";
    std::cout <<vertex->rank<< std::endl;
    std::cout <<"balance: ";
    std::cout <<vertex->balance<< std::endl;
    std::cout <<"left son: ";
    if (vertex->left_son != nullptr) 
    {
        std::cout <<*(vertex->left_son->info)<< std::endl;
    }
    else 
    {
        std::cout << "no left son" << std::endl;
    }
    std::cout <<"right son: ";
    if(vertex->right_son != nullptr){
        std::cout <<*(vertex->right_son->info)<< std::endl;
    }
    else std::cout<<"no right son" << std::endl;
    std::cout <<"parent: ";
    if (vertex->parent != nullptr)
    {
        std::cout <<*(vertex->parent->info)<< std::endl;
    }
    else
    {
        std::cout << "I am the groot"<<std::endl;
    }  
    std::cout << std::endl;
}

template <class T, class M>
void AVLtree<T,M>::printTree() {
    inOrder(root,printVertex);
    std::cout <<"the end"<< std::endl;
}


template <class T, class M>
AVLnode<T,M>* findHelper(AVLnode<T,M>* begin, M to_find){
    if (begin == nullptr)
    {
        return nullptr;
    }
    if(begin->key == to_find) return begin;
    if(begin->key > to_find) return findHelper(begin->left_son,to_find);
    if(begin->key < to_find) return findHelper(begin->right_son, to_find);
    return nullptr;
} 

template <class T, class M>
AVLnode<T,M>* AVLtree<T,M>::find(M to_find)
{
    return findHelper(root, to_find);
}


#endif  