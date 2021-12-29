
#include <queue>


//https://leetcode.com/problems/populating-next-right-pointers-in-each-node/
/*
 * 	This is a Tree Depth First Search/ Breadth First Search Problem
 *
 * 	First, the most intuitive way is that, if we obtain the nodes layer by layer, and in an orderly manner from left
 * 	to right, then we could keep connecting the node to the next node in line. This way they get connected easily
 *
 * 	This technique uses Breadth First Search, and is easily implemented using a Queue, since FIFO rule applies.
 * 	Just be careful to know which node is in the current layer. Don't go accidentally connect the next layer's node!
 *
 * 	==============================================================================================
 *
 * 	How could we do this using recursion, which is Depth First Search?
 *
 * 	The hardest part of the problem isn't to connect the left and right child, but actually to connect those who
 * 	don't really share a direct parent, Like:
 *
 * 					( )
 * 					/ \
 * 				  ( ) ( )
 * 				  / \ / \
 * 				( )(A)(B)( )
 *
 * 	Indeed. using Depth First Search, how would we know that A and B are supposed to be connected?
 * 	The idea is: By the time we reach A and B, both their parents should already be have their next pointer populated.
 * 	In this case, A's parent next pointer will be pointing to B's parent.
 *
 * 	Therefore, in recurson, what we do is:
 * 		1. Connect left child to right child
 * 		2. Connect right child to root's next node's right child. Like this:
 *
 * 			(root) ----> (next)
 * 			/	\		 /	 \
 * 		(  )   (A)     (B)   ( )
 *
 * 			root.right.next = root.next.left;
 */



class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;
        std::queue<Node*> bfs;
        bfs.push(root);

        while (!bfs.empty()) {
            int layerSize = bfs.size();

            while (layerSize-- > 0) {
                Node* n = bfs.front();
                bfs.pop();

                //	If it is not the last element in the layer. The last element remains pointing to null
                if (layerSize > 0) 
                    n->next = bfs.front();

                if (n->left) {
                    bfs.push(n->left);
                    bfs.push(n->right);
                }
            }
        }
        return root;
    }

    //	Depth First Search solution
    Node* connect2(Node* root) {
        //	Base case: no connection to do
        if ( !root || !(root->left) ) return root;

        //	First 2 nodes need to manually conenct
        root->left->next = root->right;

        // To interconnect between nodes that don't share parents, use ROOT node's next pointer
        if (root->next)
            root->right->next = root->next->left;

        connect2(root->left);
        connect2(root->right);
        return root;
    }
};

