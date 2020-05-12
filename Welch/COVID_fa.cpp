#include <iostream>

template <typename ValueType>
class BinTree{

protected:

    class Node{ 

    private:
        ValueType value;
        Node *left;
        Node *right;
        int count{0};

        Node(const Node &);
        Node & operator=(const Node &); // másoló konstruktor és értékadás-
        Node(const Node &&);
        Node & operator=(const Node &&);

    public: 
        Node(ValueType value): value(value), left(nullptr), right(nullptr) {}
        ValueType getValue(){return value;}
        Node * leftChild(){return left;}
        Node * rightChild(){return right;}
        void leftChild(Node * node){left = node;}
        void rightChild(Node * node){right = node;}
        int getCount(){return count;}
        void incCount(){++count;}
    };

    Node *root; //gyökér
    Node *treep; //fán belüli fa mutató
    int depth{0};

private: 
    

    BinTree(const BinTree &);
    BinTree & operator=(const BinTree &); 
    BinTree(const BinTree &&);
    BinTree & operator=(const BinTree &&);
    
public:
    BinTree(Node *root = nullptr, Node *treep = nullptr): root(root), treep(treep) {}
    ~BinTree()
    {
        deltree(root);
    }
    BinTree & operator<<(ValueType value);
    void print(){print(root, std::cout);}
    void print(Node *node, std::ostream & os);
    void deltree(Node *node);

};

template <typename ValueType, ValueType vr, ValueType v0>
class ZLWTree : public BinTree<ValueType> {

public:
    ZLWTree(): BinTree<ValueType>(new typename BinTree<ValueType>:: Node(vr)) {
        this->treep = this->root;
    }
    ZLWTree & operator<<(ValueType value);

};

template <typename ValueType>
BinTree<ValueType> & BinTree<ValueType>::operator<<(ValueType value)
{
    if(!treep) {
        root = treep = new Node(value);
    } else if (treep -> getValue() == value){
        treep -> incCount();
    } else if(treep -> getValue() > value)
    {
        if(!treep -> leftChild())
        {
            treep -> leftChild(new Node(value));
        }else
        {
            treep = treep -> leftChild();
            *this << value; 
        }
    } else if(treep -> getValue() < value)
    {
        if(!treep -> rightChild())
        {
            treep -> rightChild(new Node(value));
        }else
        {
            treep = treep -> rightChild();
            *this << value; 
        }
    }

    treep = root;

    return *this;
}
template <typename ValueType, ValueType vr, ValueType v0>
ZLWTree<ValueType, vr, v0> & ZLWTree<ValueType, vr, v0>::operator<<(ValueType value)
{
    if (value == v0)
    {
        if (!this -> treep -> leftChild())
        {
            typename BinTree<ValueType>::Node * node = new typename BinTree<ValueType>::Node(value);
            this -> treep -> leftChild(node);
            this -> treep = this -> root;
        } 
        else 
        {
            this -> treep = this -> treep -> leftChild();
        }
    } 
    else
    {
        if (!this -> treep -> rightChild())
        {
            typename BinTree<ValueType>::Node * node = new typename BinTree<ValueType>::Node(value);
            this -> treep -> rightChild(node);
            this -> treep = this -> root;
        } 
        else 
        {
            this -> treep = this -> treep -> rightChild();
        }
    }
    

    return *this;
}
template <typename ValueType>
void BinTree<ValueType>::print(Node *node, std::ostream & os)
{
    if(node)
    {
        ++depth;
        print(node -> leftChild(), os);

        for(int i = 0; i < depth; ++i)
        {
            os << "---";
        }
        
        os << node -> getValue() << ' ' << depth << ' ' << node -> getCount() << ' ' << std::endl;

        print(node -> rightChild(), os);
        --depth;
    }
}

template <typename ValueType>
void BinTree<ValueType>::deltree(Node *node)
{
    if(node)
    {
        deltree(node -> leftChild());
        deltree(node -> rightChild());

        delete node;
    }
}

int main(int  argc, char** argv, char ** env)
{
    BinTree<int> bt;

    bt << 8 << 9 << 5 << 2 << 7;

    bt.print();

    std::cout << std::endl;

    ZLWTree<char, '/', '0'> zt;

    zt << '0' << '1' << '1' << '1' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << 
        '0' << '0' << '0' << '1' << '1' << '1';

    zt.print();
}
