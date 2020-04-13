#include <stdio.h>
#include <math.h>
#include "the1.h"

/*
 * This function gets a parameter that indicateswhether user will give initial values or not. If it evaluates false,
 * you will simply set all values of thearray -1. Otherwise, you will scan an integer from the user stating the number
 * of values that s/he willenter. User will enter that many integer index and value pairs. If the value for that index
 * is insertedbefore, or the index or the value is out of the range, you will simply ignore it.
*/
void initialize_the_tree(int binary_tree[MAX_LENGTH], int a) {
    int i,size,loc,data,parent;
    for(i=0 ; i < MAX_LENGTH ; ++i){
        binary_tree[i]=-1;
        }
    
    if(a!=0){
        scanf("%d",&size);
        for(i=0 ; i < size ; ++i){
            scanf("%d%d",&loc,&data);
            
            if (binary_tree[loc]==-1 && loc!=0){
                parent=(loc-1)/2;
                if(binary_tree[parent]!=-1)
                    binary_tree[loc]=data;
            }
            else if(loc==0)
                binary_tree[0]=data;
        }
    }
}

/*
 * This function gets index of parent node, 'l'eft, 'r'ight or 'i'tself for where to insert and integer value.
 * If the value for the inserted node already exists, it ignores and does nothing.
 */
void insert_node(int binary_tree[MAX_LENGTH], int loc, char where, int value) {
    int parent;
    if(where=='i' && binary_tree[loc]==-1 && loc!=0){
        parent=(loc-1)/2;
        if(binary_tree[parent]!=-1)
                    binary_tree[loc]=value;
    }
    else if(where=='i' && binary_tree[loc]==-1 && loc==0)
        binary_tree[0]=value;
    else if(where=='l' && loc!=-1 && binary_tree[2*loc+1]==-1 && 2*loc+1 < MAX_LENGTH)
        binary_tree[2*loc+1]=value;
    else if(where=='r' && loc!=-1 && binary_tree[2*loc+2]==-1 && 2*loc+2 < MAX_LENGTH)
        binary_tree[2*loc+2]=value;
}

/*
 * This method  gets  the  index  of  the  node  to  be  deleted.   If  a  node  is  to  be deleted, all of its
 * descendants will be also purged.  Deleting means putting -1 value to the proper area in the array.
 */
void delete_node_rec(int binary_tree[MAX_LENGTH], int node) {
    if(node<MAX_LENGTH && binary_tree[node]!=-1){
        binary_tree[node]=-1;
        delete_node_rec(binary_tree, (2*node+1));
        delete_node_rec(binary_tree, (2*node+2));
    }
}

void tabs(int i){
    if(i>0){
        printf("\t");
        tabs(i-1);
    }
}

/*
 * This is  a recursive function that prints the tree in in-order fashion. In other words, it will print the nodes 
 * starting from the left-most child and traverse the rest of the tree in that manner. Printing order will be 
 * <left-child, root, right-child>. It gets the index of the root and the depth value as control variable. Initial 
 * value of the depth will be the height of the tree. Be careful, any sub-tree can be given to the function.
 */
void draw_binary_tree_rec(int binary_tree[MAX_LENGTH], int root, int depth) {
    if (binary_tree[root]!=-1 && depth>0){
        if(2*root+1 < MAX_LENGTH){
            draw_binary_tree_rec(binary_tree,2*root+1,depth-1);
            }
            tabs(depth);
        if(root < MAX_LENGTH)
            printf("%d\n",binary_tree[root]);
        if(2*root+2 < MAX_LENGTH)
            draw_binary_tree_rec(binary_tree,2*root+2,depth-1);
    }
    else if(binary_tree[root]!=-1 && depth==0 && root < MAX_LENGTH){
        printf("%d\n",binary_tree[root]);    
    }
}

/*
 * This is a recursive function that returns the height of the tree.  If given root does not have any child, its height
 * is 0.  Be careful, any sub-tree can be given to the function
 */
int find_height_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int leftdepth,rightdepth;
    if(root==0 && binary_tree[root]==-1)
        return 0;
    else if(2*root+1 > MAX_LENGTH)
        return 0;
    else if(binary_tree[2*root+1]==-1 && binary_tree[2*root+2]==-1){
        return 0;
    }
    
    else if(2*root+1 < MAX_LENGTH){
        leftdepth=find_height_of_tree_rec(binary_tree,2*root+1);
        rightdepth=find_height_of_tree_rec(binary_tree,2*root+2);
        if(leftdepth>rightdepth)
        return leftdepth + 1;
        else
        return rightdepth + 1;
    }
    else
        return 0;
}

/*
 * This is a recursive function that returns the minimum value given tree contains.
 * Be careful, any sub-tree can be given to the function.
 */
int find_min_of_tree_rec(int binary_tree[MAX_LENGTH], int root) {
    int leftmin,rightmin;
    if(2*root+1 < MAX_LENGTH){
        if(binary_tree[2*root+1]==-1 && binary_tree[2*root+2]==-1){
            return binary_tree[root];
        }
        else if(binary_tree[2*root+1]==-1 && binary_tree[2*root+2]!=-1){
            rightmin=find_min_of_tree_rec(binary_tree,2*root+2);
            if(binary_tree[root]>rightmin){return rightmin;}
            else{return binary_tree[root];};
        }
        else if(binary_tree[2*root+1]!=-1 && binary_tree[2*root+2]==-1){
            leftmin=find_min_of_tree_rec(binary_tree,2*root+1);
            if(binary_tree[root]>leftmin){return leftmin;}
            else{return binary_tree[root];}
        }
        else{
            rightmin=find_min_of_tree_rec(binary_tree,2*root+2);
            leftmin=find_min_of_tree_rec(binary_tree,2*root+1);
    
        
            if(binary_tree[root]>=leftmin && rightmin>=leftmin){return leftmin;}
            else if(binary_tree[root]>=rightmin && leftmin>=rightmin){return rightmin;}
            else{return binary_tree[root];}
            }
        }
    else if(root < MAX_LENGTH)
        return binary_tree[root];
    else
        return MAX_VAL + 1;
}

int power(int base,int exp){
    int i,result;
    result=1;
    for(i=0 ; i < exp ; ++i){
        result *= base;
    }
    return result;
}

int height_itr(int binary_tree[MAX_LENGTH], int root){
  int n,i,layers,result;
  for(n=0 ; power(2,n)*(root+1)-1 < MAX_LENGTH ; ++n){
        layers = power(2,n)*root+ ( power(2,n)-1 );
        for(i=0 ; i <= power(2,n)-1 ; ++i){
            if(layers + i < MAX_LENGTH && binary_tree[layers + i]!=-1)
                result=n;
        }
    }  
    return result;
}

/*
 * This is an iterative function that performs breadth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  it returns the index of the first observation of the value.
 * It gets the index of the root and the integer value that is to be searched.  Be careful, any sub-tree can be given to
 * the function and you will apply level-wise search in the tree
 */
int breadth_first_search_itr(int binary_tree[MAX_LENGTH], int root, int value) {
    int n,i,layers, result;
    int height = height_itr(binary_tree,root);
    if(binary_tree[root]==-1)
        return -1;
    for(n=0 ; n <= height ; ++n){
        layers = power(2,n)*root+ ( power(2,n)-1 );
        for(i=0 ; i <= power(2,n)-1 ; ++i){
            result = layers + i;
            if(binary_tree[result]==value)
                return result;
        }
    }
    return -1;
}

/*
 * This is  a  recursive  function  that  performs  depth-first search on the given tree.  If the value does not appear
 * in the given tree,  it returns -1.  Otherwise,  itreturns the index of the first observation of the value.  It gets
 * the index of the root and the integer valuethat is to be searched.
 * Be careful, any sub-tree can be given to the function.
 */
int depth_first_search_rec(int binary_tree[MAX_LENGTH], int root, int value) {
    if(binary_tree[root]==-1 || root > MAX_LENGTH)
        return -1;
    else if(2*root+1 < MAX_LENGTH && depth_first_search_rec(binary_tree,2*root+1,value)!=-1)
        return depth_first_search_rec(binary_tree,2*root+1,value);
    else if(binary_tree[root]==value)
        return root;
    else if(2*root+2 < MAX_LENGTH && depth_first_search_rec(binary_tree,2*root+2,value)!=-1)
        return depth_first_search_rec(binary_tree,2*root+2,value);
    else
        return -1;
}

/*
 * This is already given to you.
 */
void print_binary_tree_values(int binary_tree[MAX_LENGTH]) {
    int i;
    for (i = 0; i < MAX_LENGTH; i++) {
        if (binary_tree[i] != -1) {
            printf("%d - %d\n", i, binary_tree[i]);
        }
    }
}
