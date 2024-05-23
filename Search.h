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

bool linear_search(std::vector<int>&, int);

bool binary_search(std::vector<int> &, int);

Node* create_binary_tree(std::vector<int> &, int, int);

bool binary_tree_search(Node*, int);

bool hash_table_search(std::vector<HashNode*>::iterator, std::vector<HashNode*>::iterator, int);

void insert_hash_node(std::vector<HashNode*>::iterator, std::vector<HashNode*>::iterator, int);

std::vector<HashNode*> create_hash_table(std::vector<int> &);

int calculate_hash_depth(std::vector<HashNode*>::iterator begin, std::vector<HashNode*>::iterator end);

int calculate_hash_load(std::vector<HashNode*>::iterator begin, std::vector<HashNode*>::iterator end);



#endif //LABORATION_3_SEARCH_H
