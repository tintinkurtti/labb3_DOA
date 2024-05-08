//
// Created by tinti on 2024-05-02.
//

#ifndef LABORATION_3_SEARCH_H
#define LABORATION_3_SEARCH_H

#include <vector>
#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;
};

struct HashNode{
    int data;
    HashNode* next;
};

bool linear_search(std::vector<int> &, int);

bool binary_search(Node* , int);

Node* create_binary_tree(std::vector<int> &, int, int);

bool binary_tree_search(Node*, int);

bool hash_table_search(std::vector<Node*>::iterator, std::vector<Node*>::iterator, const int&);


#endif //LABORATION_3_SEARCH_H
