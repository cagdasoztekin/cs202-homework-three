//
//  main.cpp
//  hw03
//
//  Created by çağdaş öztekin sec 1 21201651 on 22/11/14.
//  Copyright (c) 2014 dunkucoder. All rights reserved.
//  IMPORTANT REMARK::I RIPPED OFF THE ISCOMPLETE FUNCTION FROM MY HW02 SOLUTION.
//  Also, isHeap() and isComplete() are meaningless for the way I build my heap,
//  I already make sure it remains a maxheap and a complete binary tree after
//  insertions and deletions, but anyway! :)
//

#include <iostream>
// I hope it's OK that I use math library, it's for log2 and pow
#include <math.h>
#include "hw03.h"
#include <stdio.h>

TreeNode::TreeNode()
{
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    this->key = 0;
}

TreeNode::TreeNode(TreeNode * parent, TreeNode * left, TreeNode * right)
{
    this->parent = parent;
    this->left = left;
    this->right = right;
}

TreeNode::~TreeNode()
{
    this->left = NULL;
    this->right = NULL;
    this->parent = NULL;
}

int TreeNode::check(int height)
{
    // recursively find tree's height by always comparing the heights of subtrees belonging to two children
    // and moving on with the child having the max height, the function returns a value multiple times
    // depending on its number of nodes, however the last value it returns is the actual height of the tree
    // it takes the longest time because it recursively calls itself height - 1 times, taking the longest time
    if(this != NULL)
    {
        height++;
        height = std::max(left->check(height), right->check(height));
    }
    
    return height;
}

// check if all parents' keys are larger than their children's keys
bool TreeNode::checkHeap(TreeNode* ptr)
{
    if(ptr != NULL)
    {
        if(ptr->left != NULL)
        {
            if(ptr->key >= ptr->left->key)
            {
                checkHeap(ptr->left);
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
        if(ptr->right != NULL)
        {
            if(ptr->key >= ptr->right->key)
            {
                checkHeap(ptr->right);
            }
            else
            {
                return false;
            }
        }
        else
        {
            return true;
        }
    }
    else
    {
        return true;
    }
    
    return true;
}

void TreeNode::setKey(int key)
{
    this->key = key;
}

Heap::Heap()
{
    size = 0;
    this->root = NULL;
    this->lastNodeInLevelOrder = NULL;
}

Heap::~Heap()
{
    this->root = NULL;
}

int Heap::getSize()
{
    return size;
}

bool Heap::isEmpty()
{
    return size == 0;
}

// can a heap with size 0 be a complete binary tree?... that's the ultimate question :s
bool Heap::isComplete()
{
    // status 2 means every node with height h-1 has two children so far
    int height = 0;
    int status = 2;
    // height is found here
    height = root->check(height);
    int curHeight = 1;
    // count is used to check if all nodes with height h-1 apply the rules
    int count = 0;
//    return size > 0 && root->checkComplete(curHeight, status, height, count);
    return root->checkComplete(curHeight, status, height, count);
}

// can a heap with size 0 be a heap? :s
bool Heap::isHeap()
{
    return size > 0 && this->root->checkHeap(root);
}

TreeNode* Heap::getRoot()
{
    return root;
}

// prints all the nodes, I used it to debug the code
void Heap::printNodes(TreeNode* ptr, int& count)
{
    if(ptr != NULL){
        printf("Node number %d, with item %d\n", count, ptr->key);
        if(ptr->left != NULL){
            count++;
            Heap::printNodes(ptr->left, count);
        }
        if(ptr->right != NULL){
            count++;
            Heap::printNodes(ptr->right, count);
        }
    }
}

// returns bth power of number a
int pow(int a, int b)
{
    int sum = 1;
    for(int i = b; i > 0; i--)
    {
        sum *= a;
    }
    if(b >= 0)
        return sum;
    else // so that a tree with height 1 counts as a complete tree
        return 1;
}

bool TreeNode::checkComplete(int curHeight, int &status, int height, int &count)
{
    // a tree with height 2 is checked and it's status determined right away because special conditions apply to it
    // however, it's open to discussion how efficient it is to check every time if the height equals 2 especially
    // in a recursive function that will mostly check completeness of trees with heights much larger than 2
    if(height == 2)
    {
        return (left != NULL && right != NULL) || (left != NULL && right == NULL);
    }
    // goes on looking until it find the nodes with height (height - 1), to check completeness of the tree by checking
    // the children of nodes with height - 1
    if(curHeight < height - 1 && this != NULL)
    {
        this->left->checkComplete(curHeight + 1, status, height, count);
        this->right->checkComplete(curHeight + 1, status, height, count);
    }
    // now that the nodes with height (height - 1) are found, **I'd like to emphasize this checks the nodes from left to right**
    else if(this != NULL)
    {
        // status 2 means there has not yet been encountered a node of height - 1 that does not have two children
        // as long as appropriate trees are encountered count is incremented, if not it is not incremented
        // in the end function will check to see if count equals the number of nodes with height (height - 1)
        if(status == 2)
        {
            // another node to the right, with two children
            if( (this->right != NULL && this->left != NULL))
            {
                count++;
            }
            // this node only has its left child initialized status is changed to 1
            // status 1 means there has been encountered a node with only its left child initialized
            // if the next node switches the status to 2, or the status remains as 1 it will terminate incrementing
            // count, meaning the tree is not complete
            else if( (this->left != NULL && this->right == NULL))
            {
                status = 1;
                count++;
            }
            // current node has no children, status 0 means no children if status 2 or 1 comes after status 0,
            // the function will terminate incrementing count, meaning the tree is not complete
            else
            {
                count++;
                status = 0;
            }
        }
        // only status 0 can come after status 1, so count is not incremented for other conditions
        else if(status == 1)
        {
            if( (this ->right != NULL && this->left != NULL) || (this->left != NULL && this->right == NULL) )
            {
            }
            else {
                count++;
                status = 0;
            }
        }
        // only status 0 can come after status 0, so count is not incremented for other conditions
        else
        {
            if( (this ->right != NULL && this->left != NULL) || (this->left != NULL && this->right == NULL) )
            {
            }
            else
            {
                count++;
            }
        }
        
    }
    // meaning that the tree is not a full tree without considering nodes with height (height)
    else
    {
        return false;
    }
    
    // all nodes with height (height - 1) satisfy the conditions of a complete tree are counted and it equals to their number
    if(count == pow(2,height-2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Heap::insert(const int &newKey)
{
    // if empty, insert into root...
    if(this->isEmpty())
    {
        root = new TreeNode(NULL, NULL, NULL);
        root->setKey(newKey);
        lastNodeInLevelOrder = root;
        size++;
    }
    else
    {
        // this mean the heap is a full binary tree so the next insertion will be made into the leftmost item
        if(((int)(log2(size)) != ((int)(log2(size+1)))))
        {
            TreeNode* ptr = root;
            while(ptr->left != NULL)
            {
                ptr = ptr->left;
            }
            ptr->left = new TreeNode(ptr, NULL, NULL);
            lastNodeInLevelOrder = ptr->left;
            lastNodeInLevelOrder->setKey(newKey);
            size++;
            // trickle up the last inserted item until it's smaller than its parent
            heapRebuild();
        }
        // the insertion will be made to the sibling of the last node... trivial
        else if(lastNodeInLevelOrder->parent->right == NULL)
        {
            lastNodeInLevelOrder->parent->right = new TreeNode(lastNodeInLevelOrder->parent, NULL, NULL);
            lastNodeInLevelOrder = lastNodeInLevelOrder->parent->right;
            lastNodeInLevelOrder->setKey(newKey);
            size++;
            // trickle up the last inserted item until it's smaller than its parent
            heapRebuild();
        }
        //
        else if(lastNodeInLevelOrder->parent == lastNodeInLevelOrder->parent->parent->left)
        {
            TreeNode* ptr = lastNodeInLevelOrder->parent->parent->right;
            if(ptr->left == NULL)
            {
                ptr->left = new TreeNode(ptr, NULL, NULL);
                lastNodeInLevelOrder = ptr->left;
                lastNodeInLevelOrder->setKey(newKey);
                size++;
                // trickle up the last inserted item until it's smaller than its parent
                heapRebuild();
            }
            else
            {
                // I don't think this part will be necessary as
                // the only possible spot is dealt with the nearest if stmt above
                // but who knows :!
                // not me!
                //// I never lost control :w
                //// you're face!
                //// to face :(
                //// with the man who sold the world :3
                while(ptr->left != NULL)
                {
                    ptr = ptr->left;
                }
                
                ptr->left = new TreeNode(ptr, NULL, NULL);
                lastNodeInLevelOrder = ptr->left;
                lastNodeInLevelOrder->setKey(newKey);
                size++;
                // trickle up the last inserted item until it's smaller than its parent
                heapRebuild();
            }
        }
        // this is rather complex...
        else if(lastNodeInLevelOrder->parent == lastNodeInLevelOrder->parent->parent->right)
        {
            // traverse until finding a node which is the left child of its parent
            TreeNode* ptr = lastNodeInLevelOrder->parent->parent;
            while(ptr->parent != NULL)
            {
                if(ptr == ptr->parent->right)
                {
                    ptr = ptr->parent;
                }
                else
                {
                    ptr = ptr->parent->right;
                    break;
                }
            }
            
            // find its leftmost node, whose left child will be the insertion location
            while(ptr->left != NULL)
            {
                ptr = ptr->left;
            }
            
            ptr->left = new TreeNode(ptr, NULL, NULL);
            lastNodeInLevelOrder = ptr->left;
            lastNodeInLevelOrder->setKey(newKey);
            size++;
            // trickle up the last inserted item until it's smaller than its parent
            heapRebuild();
        }
    }
}

// traversals in this function are quite similar to the ones in the insertion function
// also this function uses a different heapRebuild -- with a TreeNode pointer parameter
// it checks from the root to the leaves, whereas the heapRebuild() used in insertion checks
// from leaves to the root and has no parameter
void Heap::retrieveAndDelete(int& maxKey)
{
    // if size 1 delete root
    if(size == 1)
    {
        TreeNode* del;
        maxKey = root->key;
        del = root;
        root = NULL;
        lastNodeInLevelOrder = NULL;
        // avoid that memleak
        delete del;
        size--;
    }
    else if(size > 1)
    {
        // if the eventual lastNodeInLevelOrder is not obvious to find, prev will be used to find it
        TreeNode* prev;
        // in any case maxKey will be returned so it's dealt at the beginning,
        maxKey = root->key;
        // then the last node is the leftmost item! find it and delete it.
        if(((int)(log2(size)) != ((int)(log2(size-1)))))
        {
            prev = root;
            
            while(prev->right != NULL)
            {
                prev = prev->right;
            }
            
            root->key = lastNodeInLevelOrder->key;
            TreeNode* del = lastNodeInLevelOrder;
            lastNodeInLevelOrder->parent->left = NULL;
            
            lastNodeInLevelOrder = prev;
            delete del;
            size--;
            // trickle down the root so the heap becomes a max heap again
            heapRebuild(root);
        }
        // get to the left subtree of the parent to reach lastNodeInLevelOrder delete the previous one
        else if(lastNodeInLevelOrder->parent->right == lastNodeInLevelOrder)
        {
            root->key = lastNodeInLevelOrder->key;
            TreeNode* del = lastNodeInLevelOrder;
            
            lastNodeInLevelOrder = lastNodeInLevelOrder->parent->left;
            lastNodeInLevelOrder->parent->right = NULL;
            delete del;
            size--;
            // trickle down the root so the heap becomes a max heap again
            heapRebuild(root);
        }
        else
        {
            if(lastNodeInLevelOrder->parent == lastNodeInLevelOrder->parent->parent->right)
            {
                TreeNode* del;
                prev = lastNodeInLevelOrder->parent->parent->left->right;
                root->key = lastNodeInLevelOrder->key;
                del = lastNodeInLevelOrder;
                lastNodeInLevelOrder->parent->left = NULL;
                lastNodeInLevelOrder = NULL;
                lastNodeInLevelOrder = prev;
                delete del;
                size--;
                // trickle down the root so the heap becomes a max heap again
                heapRebuild(root);
            }
            // who knows, not me again.
            else if(lastNodeInLevelOrder->parent == lastNodeInLevelOrder->parent->parent->left)
            {
                prev = lastNodeInLevelOrder->parent;
                while(prev == prev->parent->left)
                {
                    prev = prev->parent;
                }
                
                prev = prev->parent->left;
                while(prev->right != NULL)
                {
                    prev = prev->right;
                }
                // del is used to delete the the retrieved node and lest not be any memory leaks
                TreeNode* del;
                root->key = lastNodeInLevelOrder->key;
                lastNodeInLevelOrder->parent->left = NULL;
                del = lastNodeInLevelOrder;
                lastNodeInLevelOrder = NULL;
                lastNodeInLevelOrder = prev;
                delete del;
                size--;
                // trickle down the root so the heap becomes a max heap again
                heapRebuild(root);
            }
        }
    }
    else
    {
        // david davenport's favourite number.. to signal having accessed a memory location with an arbitrary value!
        maxKey = -27;
    }
}

// trickle down the node until both its childrens keys are smaller than the current node
void Heap::heapRebuild(TreeNode* first)
{
    int temp;
    if(first->left != NULL && first->right != NULL)
    {
        // make sure the node with the larger key among the children is swapped with the parent
        if(first->left->key > first->right->key)
        {
            temp = first->key;
            first->key = first->left->key;
            first->left->key = temp;
            heapRebuild(first->left);
        }
        else
        {
            temp = first->key;
            first->key = first->right->key;
            first->right->key = temp;
            heapRebuild(first->right);
        }
    }
    else if(first->left != NULL)
    {
        if(first->key < first->left->key)
        {
            temp = first->key;
            first->key = first->left->key;
            first->left->key = temp;
            heapRebuild(first->left);
        }
    }
    else if(first->right != NULL)
    {
        if(first->key < first->right->key)
        {
            temp = first->key;
            first->key = first->right->key;
            first->right->key = temp;
            heapRebuild(first->right);
        }
    }
}

// very straightforward compared to the previous heapRebuild(TreeNode* first)
void Heap::heapRebuild()
{
    // trickle up the newly inserted node until its key is smaller than its parent's key
    TreeNode* lastNode = lastNodeInLevelOrder;
    while(lastNode->parent != NULL)
    {
        if(lastNode->parent->key < lastNode->key)
        {
            int temp = lastNode->key;
            lastNode->key = lastNode->parent->key;
            lastNode->parent->key = temp;
        }
        else{
            break;
        }
        
        lastNode = lastNode->parent;
    }
}

int main(int argc, const char * argv[]) {
    
    Heap maxIntHeap;
    int numbers[10] = {0,1,2,3,4,5,6,7,8,9};
    int order[10] = {2,8,5,3,7,6,9,4,0,1};
    int sortedNumbers[10];
    for (int i = 0; i < 10; i++) maxIntHeap.insert(numbers[order[i]]);
    printf("Size: %d\n", maxIntHeap.getSize());
    printf("Is heap: %s\n", maxIntHeap.isHeap() ? "Yes" : "No"); printf("Is complete: %s\n", maxIntHeap.isComplete() ? "Yes" : "No");
    for (int i = 0; i < 10; i++) maxIntHeap.retrieveAndDelete(sortedNumbers[i]);
    printf("Sorted order:");
    for (int i = 0; i < 10; i++)
        printf("%d ", sortedNumbers[i]);
    return 0;
}
