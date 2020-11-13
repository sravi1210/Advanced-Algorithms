#ifndef NODE_H
#define NODE_H
#include<iostream>
#include<bits/stdc++.h>

using namespace std;
#define MIN_DEGREE 3 // This is same as the 't' used in CLRS

class node{
  public:
    bool getLeaf();
    void setLeaf(bool value);

    int getNumKeys();
    void setNumKeys(int value);

    int getKeyAtIndex(int i);
    void setKeyAtIndex(int key, int i);

    node* getChildAtIndex(int i);
    void setChildAtIndex(node* child, int i);
  private:
    int isLeaf;
    int numKeys;
    int keys[2*MIN_DEGREE - 1];
    node* children[2*MIN_DEGREE];
};

#endif
