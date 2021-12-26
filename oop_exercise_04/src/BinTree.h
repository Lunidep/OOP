#pragma once
#ifndef Binnodeee_H
#define Binnodeee_H

#include "Node.h"


template< typename T >
class BinTree {
public:
    BinTree() : root(NULL) {};
    ~BinTree() { recursive_delete(root); };

    bool empty() {
        return root == nullptr;
    }

    void insert(const T& data) { recursive_insert(&root, data); }

    /*
    void remove(const T& data) {
        recursive_remove(&root, data, NULL); 
    }*/
    

    void print() const { recursive_print(root, 0, false); }
    
    void get(const string& path) {
        recursive_search(&root, path, 0);
    }

    void remove(const string& path) { 
        recursive_search(&root, path, 1);
    }

private:
    Node< T >* root;

    void recursive_delete(Node< T >* node) {
        if (node != NULL) {
            recursive_delete(node->lhs);
            recursive_delete(node->rhs);

            delete node;
        }
    }

    //�� ��������� ��� ��������� ������ �������� � node ������, ����� ������� �������� �������
    void recursive_insert(Node< T >** node, const T& data) {
        if (*node == NULL)
            *node = new Node< T >(data);
        else {
            if ((*node)->value >= data)
                recursive_insert(&((*node)->lhs), data);
            else if ((*node)->value < data)
                recursive_insert(&((*node)->rhs), data);
        }
    }

    void recursive_search(Node< T >** node, const string& path, int flag) {
        if ((path != "") && (*node == NULL)) {
            throw invalid_argument("������������ ���� �� ��������!\n\n");
        } 
        
        if (path[0] == 'l')
            recursive_search(&((*node)->lhs), path.substr(1), flag);
        else if (path[0] == 'r')
            recursive_search(&((*node)->rhs), path.substr(1), flag);
        else if (path == "") {
            if (flag == 0) {
                cout << (*node)->value << endl;
            }
            else if (flag == 1){
                recursive_remove(node, (*node)->value, NULL);
            }
        }
        else {
            throw invalid_argument("������������ ������� ��������� ����!\n\n");
        
            //cout << "Error string\n";
            //return;
        }
    }

    Node< T >* minimum(Node< T >* node)
    {
        if (!node->lhs->lhs) return node;
        return minimum(node->lhs);
    }

    void recursive_remove(Node< T >** node, const T& data, Node< T >* parent){        
        if (!(*node)) return;

        if (data < (*node)->value)
            recursive_remove(&((*node)->lhs), data, *node);
        else if (data > (*node)->value)
            recursive_remove(&((*node)->rhs), data, *node);
        else {

            if (!(*node)->lhs && !(*node)->rhs) {//���� ����� � ���������� ���� ���, �� ����� ���� ����� ������� ������ - �������� ����.
                if (parent) {//�������� ������� ���� ���� �������� � ���, ��� ������� � ���� ������ ��� 
                    if (parent->lhs) {
                        if (parent->lhs->value == (*node)->value) { //���� ��������� ����� �������
                            parent->lhs = NULL;
                        }
                    }
                    if (parent->rhs) {
                        if (parent->rhs->value == (*node)->value) { //���� ��������� ������ �������
                            parent->rhs = NULL;
                        }
                    }
                }
                delete *node; // ������ ����� ���������� ������
                *node = NULL;
            }
            else if (!(*node)->lhs || !(*node)->rhs) { // ���� � ��������� ������� ���� ���� �� ���� �������
                Node< T >* nodeToRemove = NULL;
                if ((*node)->lhs) { //������� ���� ������ ������������� ������� ��������� �������
                    nodeToRemove = (*node)->lhs;
                }
                else {
                    nodeToRemove = (*node)->rhs;
                }
                //����������� ��� ������ �� ������������� ������� ��������� �������
                (*node)->lhs = nodeToRemove->lhs;
                (*node)->rhs = nodeToRemove->rhs;
                (*node)->value = nodeToRemove->value;
                //���������� ������, ���������� ����� ��� ������� �������
                delete nodeToRemove;
            }
            else { //���� � ��������� ������� ���� ��� �������, �� �������� ��������� ���������� ����� ���������� ������� � ������ ��������� ���������� ��������

                if (!(*node)->rhs->lhs) { //���� � ������� ��������� ��� ����� ��������, �� ��� ��������, ��� � ���� �������� �������� ����� ������, � ������ ���� ������ ����������� �������� �� ������� ������� � ��������� �������

                    (*node)->value = (*node)->rhs->value; // ����������� �������� �� ������� �������
                    Node< T >* righnodeIghtChild = (*node)->rhs->rhs;
                    delete (*node)->rhs; // ��������� ������, ���������� ��� ������� �������
                    (*node)->rhs = righnodeIghtChild;
                }
                else {
                    Node< T >* minNodeParent = minimum((*node)->rhs); //����� ����������� �������� � ������ ��������� (�� ����������� �������, ������ ����� ��� ��� ��� �������� ����)
                    (*node)->value = minNodeParent->lhs->value; //����������� �������� �� ����������� �������� � ������ ��������� � ��������� �������
                    delete minNodeParent->lhs;
                    minNodeParent->lhs = NULL;
                }
            }
        }
    }
    
    void recursive_print(Node< T >* node, int level, bool isleft) const {
        if (node == NULL) {
            return;
        }

        recursive_print(node->rhs, level + 1, false);
        for (int i = 0; i < level; i++) {
            cout << "        ";
        }
        if (level != 0) {
            if (isleft) { cout << "*"; }
            else { cout << "*"; }
        }
        else { cout << "#"; }

        cout << "------|";
        cout << node->value << "\n\n";

        recursive_print(node->lhs, level + 1, true);
    }
    
};



#endif