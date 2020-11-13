#ifndef BTREE_H
#define BTREE_H
#include"node.h"
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class btree{
  public:
    btree();
    tuple<node*, int> search(node* subtree, int key);
    void insert(btree*, int key);
    void insertNonFull(node* x, int key);
    void splitChild(node* x, int i);
    void postOrderTraversal(node* x, int depth);
    node* root;
};

#endif
