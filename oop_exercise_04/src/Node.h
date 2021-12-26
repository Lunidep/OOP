#pragma once
#ifndef Node_H
#define Node_H

template< typename T > class BinTree;

template< typename T >
class Node{
    friend class BinTree< T >;

public:
    Node() : lhs(NULL), rhs(NULL) {};
    Node(const T& data) :value(data), lhs(NULL), rhs(NULL) {};

    T getvalue() const{ return value; }
    Node*& get_left() {
        return lhs;
    }
    Node*& get_right() {
        return rhs;
    }
private:
    T value;
    Node< T >* lhs;
    Node< T >* rhs;
};

#endif