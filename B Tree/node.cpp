#include "node.h"
using namespace std;

void node::setLeaf(bool value){
  isLeaf = value; 
}

bool node::getLeaf(){
  return isLeaf;
}

void node::setNumKeys(int value){
  numKeys = value;
}

int node::getNumKeys(){
  return numKeys;
}

int node::getKeyAtIndex(int i){
  return keys[i];
}

node* node::getChildAtIndex(int i){
  return children[i];
}

void node::setChildAtIndex(node* child, int i){
  children[i] = child;
}

void node::setKeyAtIndex(int key, int i){
  keys[i] = key;
}
