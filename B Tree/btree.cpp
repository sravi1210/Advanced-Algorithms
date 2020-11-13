#include<string>
#include "node.h"
#include "btree.h"
using namespace std;

// Tree initializationbtree::splitChild(s, 0);
btree::btree(){
  root = new node();
  root->setLeaf(true);
  root->setNumKeys(0);
}

tuple<node*, int> btree::search(node* subtree, int key){
  // Implementation based on CLRS
  int i = 1;
  // Find the right key position.
  while ( i <= subtree->getNumKeys() & key > subtree->getKeyAtIndex(i)){
    i++;
  }
  // If key matches, return the result as a tuple.
  if (i <= subtree->getNumKeys() & key == subtree->getKeyAtIndex(i)){
    return make_tuple(subtree, i);
  }
  else{
    // Key does not matches and is a leaf node, return NULL.
    if (subtree->getLeaf()){
      return make_tuple(static_cast<node*>(NULL), 0);
    }
    // Search recursively the correct subtree.
    else return search(subtree->getChildAtIndex(i), key);
  }
}

void btree::insert(btree* tree, int key){
  // Implementation based on CLRS
  node* root = tree->root;
  // If root is full, split it.
  if (root->getNumKeys() == (2 * MIN_DEGREE) - 1){
    node* s = new node();
    tree->root = s;
    s->setLeaf(false);
    s->setNumKeys(0);
    s->setChildAtIndex(root, 0);
    btree::splitChild(s, 0);
    btree::insertNonFull(s, key);
  }
  else{
    btree::insertNonFull(root, key);
  }
}

void btree::insertNonFull(node* x, int key){
  // Implementation based on CLRS
  cout << "Insert node full called on " << key << endl;
  int i = x->getNumKeys();
  // If the node is a leaf node, insert at the correct position.
  if (x->getLeaf()){
    while (i > 0 and key < x->getKeyAtIndex(i - 1)){
      x->setKeyAtIndex(x->getKeyAtIndex(i - 1), i);
      i--;
    }
    x->setKeyAtIndex(key, i);
    x->setNumKeys(x->getNumKeys() + 1);
  }
  else{
    // Is the node is not a leaf node, find the candidate child.
    while(i > 0 & key < x->getKeyAtIndex(i - 1)){
      i--;
    }
    i++;
    // If the child is full, split it.
    if (x->getChildAtIndex(i - 1)->getNumKeys() == (2 * MIN_DEGREE) - 1){
      btree::splitChild(x, i - 1);
      if (key > x->getKeyAtIndex(i - 1)){
        i++;
      }
    }
    btree::insertNonFull(x->getChildAtIndex(i - 1), key);
  }
}

void btree::splitChild(node* x, int i){
  // Implementation based on CLRS
  cout << "Splitting child at index " << i << endl;
  node* z = new node();
  node* y = x->getChildAtIndex(i);
  z->setLeaf(y->getLeaf());
  z->setNumKeys(MIN_DEGREE - 1);

  for (int j = 0; j < MIN_DEGREE - 1; j++){
    z->setKeyAtIndex(y->getKeyAtIndex(j + MIN_DEGREE), j);
  }

  if (!y->getLeaf()){
    for (int j = 0; j <= MIN_DEGREE; j++){
      z->setChildAtIndex(y->getChildAtIndex(j+MIN_DEGREE), j);
    }
  }
  y->setNumKeys(MIN_DEGREE - 1);
  for (int j = x->getNumKeys(); j >= i + 1; j--){
    x->setChildAtIndex(x->getChildAtIndex(j), j + 1);
  }
  x->setChildAtIndex(z, i + 1);
  for (int j = x->getNumKeys(); j > i; j--){
    x->setKeyAtIndex(x->getKeyAtIndex(j - 1), j);
  }
  x->setKeyAtIndex(y->getKeyAtIndex(MIN_DEGREE - 1), i);
  x->setNumKeys(x->getNumKeys() + 1);
}

void btree::postOrderTraversal(node* subtree, int depth){
  // Print the vertical tree for debugging.
  // The number of times '-' illustrate the depth of the node within the tree.
  // Please check the provided test case.
  int nodesPresent = subtree->getNumKeys();
  if (subtree->getLeaf()){
    for (int j = nodesPresent - 1; j >= 0; j--){
      cout <<  std::string(depth + 1, '-') << subtree->getKeyAtIndex(j) << endl;
    }
  }
  else{
    for (int j = nodesPresent; j > 0; j--){
      btree::postOrderTraversal(subtree->getChildAtIndex(j), depth + 1);
      cout <<  std::string(depth + 1, '-') << subtree->getKeyAtIndex(j - 1) << endl;
    }
    btree::postOrderTraversal(subtree->getChildAtIndex(0), depth + 1);
  }
}
