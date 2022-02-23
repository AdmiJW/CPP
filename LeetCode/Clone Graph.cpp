#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;


//https://leetcode.com/problems/clone-graph
/*
 * 	This is a graph, DFS / BFS problem.
 *
 *  To clone a undirected graph, the hardest part is to establish the undirected connection. How are we going to know:
 *  >	If a node had been created before?
 *  >	If the connection already been established?
 *
 *  We could make a Hashmap, that maps from the original node to the cloned node itself, it can be node's value, or the
 *  node by itself as the key.
 *  Now, For the DFS approach, we need to treat problems seperately, meaning we have to focus on the current node only.
 *  In the final node, the connections must be well established, all the node references must be already there in the
 *  neighbors arraylist.
 *  To achieve this, when we are iterating over the list of neighbors, try to call a DFS function on that neighbor node,
 *  so that it will return a node for us to establish a connection.
 *  What if later the connections are duplicated?
 *  By establishing the connection one way (From current node to the neighbor node, and not the other way around), we
 *  can ensure that no duplicate connection may occur, since in DFS it is already been established)
 *
 *  Therefore the DFS must look like this.
 *  If the node already exists, return directly the node, so the parent recursive call can establish connection onto this
 *  node.
 *  Otherwise, create a new node, iterate over all neighbors and call dfs on them, and return this node.
 */


class Node {
public:
	int val;
	vector<Node*> neighbors;
	Node() {
		val = 0;
		neighbors = vector<Node*>();
	}
	Node(int _val) {
		val = _val;
		neighbors = vector<Node*>();
	}
	Node(int _val, vector<Node*> _neighbors) {
		val = _val;
		neighbors = _neighbors;
	}
};



class Solution {
public:

	// BFS solution
	Node* cloneGraph(Node* node) {
		unordered_map<Node*, Node*> map;
		queue<Node*> toExplore;

		if (!node) return nullptr;

		// Initialize
		map[node] = cloneNode(node);
		toExplore.push(node);

		// General BFS
		while (toExplore.size()) {
			Node* n = toExplore.front();
			toExplore.pop();

			for (Node* neighbor : n->neighbors) {
				if (!map.count(neighbor)) {
					map[neighbor] = cloneNode(neighbor);
					toExplore.push(neighbor);
				}
				map[n]->neighbors.push_back(map[neighbor]);
			}
		}
		return map[node];
	}

	// Clones a node and copy the value, but
	// do not copy neighbors (adjacency list)
	Node* cloneNode(Node* node) {
		if (!node) return nullptr;
		return new Node(node->val, {});
	}
};


