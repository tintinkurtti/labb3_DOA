//
// Created by tinti on 2024-05-02.
//

#include <vector>
#include "Search.h"


bool linear_search(std::vector<int> &vec, int value){
    for (int i = 0; i < vec.size(); i++){
        if (vec[i] == value){
            return i;
        }
    }
    return false;
}

bool binary_search(std::vector<int> &vec, int value){
    int low = 0;
    int high = vec.size() - 1;
    while (low <= high){
        int mid = (low + high) / 2;
        if (vec[mid] == value){
            return mid;
        }
        else if (vec[mid] < value){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return false;
}

bool binary_tree_search(Node* root, const int& value){
    if (root == nullptr){
        return false;
    }
    if (root->data == value){
        return true;
    }
    if (root->data < value){
        return binary_tree_search(root->right, value);
    }
    return binary_tree_search(root->left, value);
}

bool hash_table_search(std::vector<HashNode*>::iterator begin, std::vector<HashNode*>::iterator end, const int& value){
    HashNode* node_index = *(begin + (value % std::distance(begin, end)));
    while (node_index != nullptr){
        if (node_index->data == value){
            return true;
        }
        node_index = node_index->next;
    }
    return false;
}
