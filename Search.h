//
// Created by tinti on 2024-05-02.
//

#ifndef LABORATION_3_SEARCH_H
#define LABORATION_3_SEARCH_H



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

bool binary_search(std::vector<int> &, int);

bool binary_tree_search(Node*, const int&);

bool hash_table_search(std::vector<Node*>::iterator, std::vector<Node*>::iterator, const int&);



#endif //LABORATION_3_SEARCH_H
