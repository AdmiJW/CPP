
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
 * 	The solution is, we have a recursive function which will take in TWO, 2 parent nodes as arguments. This 2 parent nodes
 * 	know that the middle nodes have to be connected well!
 *
 * 	Basically, this recursive function will do following:
 *			if node is null return
 *			connect the left node's children
 *			connect the right node's children
 *			connect the left node's right to right node's left (The 'Gap' is now connected)
 *
 *			recurse(left node's children)
 *			recurse(right node's children)
 *			recurse(left node's right & right node's left)     (This ensures that the layer below will always be connected)
 *
 *	==============================================================================================
 *
 *	Introducing the technique to perform Level order traversal using the next pointer in each node
 *
 *	We will keep a leftmost pointer, which only stores the leftmost node in a level. Then, treet this node as parent node
 *	of children. We will conenct the children together.
 *	Now, do we have access to the node next to right children? Yes!
 *	We keep track of the current parent node, and we can access it's next node in level. The next node's left children
 *	is the node we have to connect!
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
            //	Get Layer size
            int layerSize = bfs.size();

            //	Ensure don't go over layer size!
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
        if (!root || !root->left) return root;

        //	First 2 nodes need to manually conenct
        root->left->next = root->right;

        recurse(root->left, root->right);
        return root;
    }

    Node* connect3(Node* root) {
        Node* leftmost = root;

        while (leftmost) {
            Node* curr = leftmost;
            while (curr) {
                connect(curr->left, curr->right);
                if (curr->next)
                    connect(curr->right, curr->next->left);
                curr = curr->next;
            }
            leftmost = leftmost->left;
        }
        return root;
    }

private:
    void recurse(Node* left, Node* right) {
        if (!left) return;
        connect(left->left, left->right);
        connect(right->left, right->right);
        connect(left->right, right->left);

        recurse(left->left, left->right);
        recurse(right->left, right->right);
        recurse(left->right, right->left);
    }
    void connect(Node* left, Node* right) {
        if (!left) return;
        left->next = right;
    }
};

