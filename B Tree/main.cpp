#include <iostream>
#include "node.h"
#include "btree.h"

using namespace std;


int main(){
  btree* tree = NULL;
  int key;
  int choice;
  node* searchResult;
  int searchResultIndex;
  do {
    cout << "1. Create new tree" << endl;
    cout << "2. Add new key to the tree" << endl;
    cout << "3. Search a key in the tree" << endl;
    cout << "4. Postorder traversal of the tree" << endl;
    cout << "Any other choice to exit" << endl;
    cout << "Enter your choice:";
    cin >> choice;
    cout << "You entered " << choice << endl;

    switch(choice){
      case 1:
        if(tree != NULL){
          delete tree;
        }
        tree = new btree();
        break;
      
      case 2:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        cout << "Enter key to add ";
        cin >> key;
        tree->insert(tree, key);
        break;
      case 3:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        cout << "Enter key to search";
        cin >> key;
        tie(searchResult, searchResultIndex) = tree->search(tree->root, key);
        if(searchResult == NULL){
           cout << "Key " << key << " not found." << endl;
        }
        else{
          cout << "Key " << key << " found" << endl;
        }
        break;
      case 4:
        if(tree == NULL){
          cout << "Create a new tree first" << endl;
          break;
        }
        tree->postOrderTraversal(tree->root, 0);
        break;

      default:
        return 0;
    }
  }
  while(true);
    return 0;

}
