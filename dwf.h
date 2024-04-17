/*
    DWF,即Dustwind‘s Functions，集成了我个人常用的一些功能。
*/
#pragma once
#ifndef DWF_H
#define DWF_H


#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
namespace dwf
{
    class Bigint
    {
    public:
        Bigint();
        Bigint(std::string num);
        ~Bigint();

        std::string tostring() const;
        std::string getNum() const;


        bool operator>(const Bigint&) const;
        bool operator<(const Bigint&) const;
        bool operator>=(const Bigint&) const;
        bool operator<=(const Bigint&) const;
        Bigint operator+(const Bigint&) const;
        Bigint operator-(const Bigint&) const;
        Bigint operator*(const Bigint&) const;
        Bigint operator-() const;

    protected:
        std::string num;
        bool isNegative;
        int* cutStr2Piece(std::string);
        void reverseInt(int*, int);
        std::string cutZero(std::string);
        bool checkNum(std::string);
        int compare(const Bigint&, const Bigint&) const;

        void plus(int);
        void plus(std::string);
        void multiply(int);
        void multiply(std::string);
        void subtraction(int);
        void subtraction(std::string);
    };
    struct node
    {
        int val;
        node* lchild;
        node* rchild;
    };
    class BinaryTree
    {
    public:
        BinaryTree();
        BinaryTree(int val);
        BinaryTree(int *values,int n);
        BinaryTree(std::vector<int> &values);
        void insert(int val);
        void setNodeVal(int val,int newval);
        void preOrder()const;
        void inOrder()const;
        void postOrder()const;
        void layerOrder()const;
    protected:
        void _insert(int val, node* &p);
        void _preOrder(node* p)const;
        void _inOrder(node *p)const;
        void _postOrder(node *p)const;
        void _layerOrder(node* p)const;
        void _setNodeVal(int val,int newval, node* p)const;
        node* _newNode(int val);
        node* p_root;
    };

    void bubbleSort(int* nums,int n);
    void fastSort(int* nums,int n);
    void _fastSort(int* nums, int n, int lo, int hi);
    //unsigned int count;
}

#endif

