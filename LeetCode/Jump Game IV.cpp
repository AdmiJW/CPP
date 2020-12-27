#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;


//https://leetcode.com/problems/jump-game-iv/
/*
 *  This is a Graph Traversal - BFS problem.
 *
 *  We want to find the shortest distance from the starting node to the end node, with the steps of either:
 *  		>	Go to next node
 *  		>	Go to previous node
 *  		>	Go to node with same value
 *
 *  Therefore we need to Record all the nodes with the same value, by the index in the array. We can use a HashMap
 *  for this
 *
 *  We can choose to record the shortest distance needed to reach a particular node, using a HashMap as well.
 *
 *  On each Node, we have to record the distances to
 *  	-	Nodes of same values
 *  	-	Next node and Previous node
 *
 *  Whenever we detected we had reached the end node, immediately return the distance to it.
 *
 *  -----------------------
 *
 *  However, consider case 1,7,7,7,7,7,7,7,7,7,7,7,77,7,7,7...2. There are many 7 in between. In the worst case, we might
 *  have to go through all the 7's!. On each node 7, we have to go through all the indices of nodes with value 7, causing
 *  O(N^2) time! We must need to optimize it!
 *
 *  ----------------------------------------------------------------------------------------------------
 *
 *  One little optimization is, through observation, we see that actually for a series of nodes with same value, like
 *  7,7,7,7, only the first one and last one is important! Therefore, we might just ignore the intemeidate nodes when
 *  constructing the graph. This solves the earlier problem where the nodes are bunched together, but now consider
 *  another case:
 *
 *  		1,2,7,2,7,2,7,2,7... 3
 *
 *  Since they are seperated, solution above won't work! Is there a better way?
 *
 *  ----------------------------------------------------------------------------------------------------
 *
 *  The key is, since we are using BFS, when we had traversed to a node for first time, we must be having the shortest
 *  distance so far. Therefore, The other nodes having the same value, we will just write to them ONCE, that is during
 *  we first explored the node of this value. After that, we immediately delete the record of nodes with same value.
 *  Therefore the subsequent times we met the node, we won't be checking each one again, causing O(N^2) time!
 *
 *  -----------------------------------------------------------------------------------------------------
 *
 *  Can we optimize space? Instead of using HashMap which records which node has which shortest distance from origin,
 *  remember thta we are using BFS, which we know the distance is just the 'layer' of BFS! Just keep a variable that
 *  keep tracks of the layers we have been through, and that is our distance!
 */
 //https://leetcode.com/problems/jump-game-iv/
 /*
  *  This is a Graph Traversal - BFS problem.
  *
  *  We want to find the shortest distance from the starting node to the end node, with the steps of either:
  *  		>	Go to next node
  *  		>	Go to previous node
  *  		>	Go to node with same value
  *
  *  Therefore we need to Record all the nodes with the same value, by the index in the array. We can use a HashMap
  *  for this
  *
  *  We can choose to record the shortest distance needed to reach a particular node, using a HashMap as well.
  *
  *  On each Node, we have to record the distances to
  *  	-	Nodes of same values
  *  	-	Next node and Previous node
  *
  *  Whenever we detected we had reached the end node, immediately return the distance to it.
  *
  *  -----------------------
  *
  *  However, consider case 1,7,7,7,7,7,7,7,7,7,7,7,77,7,7,7...2. There are many 7 in between. In the worst case, we might
  *  have to go through all the 7's!. On each node 7, we have to go through all the indices of nodes with value 7, causing
  *  O(N^2) time! We must need to optimize it!
  *
  *  ----------------------------------------------------------------------------------------------------
  *
  *  One little optimization is, through observation, we see that actually for a series of nodes with same value, like
  *  7,7,7,7, only the first one and last one is important! Therefore, we might just ignore the intemeidate nodes when
  *  constructing the graph. This solves the earlier problem where the nodes are bunched together, but now consider
  *  another case:
  *
  *  		1,2,7,2,7,2,7,2,7... 3
  *
  *  Since they are seperated, solution above won't work! Is there a better way?
  *
  *  ----------------------------------------------------------------------------------------------------
  *
  *  The key is, since we are using BFS, when we had traversed to a node for first time, we must be having the shortest
  *  distance so far. Therefore, The other nodes having the same value, we will just write to them ONCE, that is during
  *  we first explored the node of this value. After that, we immediately delete the record of nodes with same value.
  *  Therefore the subsequent times we met the node, we won't be checking each one again, causing O(N^2) time!
  *
  *  -----------------------------------------------------------------------------------------------------
  *
  *  Can we optimize space? Instead of using HashMap which records which node has which shortest distance from origin,
  *  remember thta we are using BFS, which we know the distance is just the 'layer' of BFS! Just keep a variable that
  *  keep tracks of the layers we have been through, and that is our distance!
  */

class Solution {
public:
	int minJumps(vector<int>& arr) {
		const int len = arr.size();

		//	Construct of the graph which maps a value to indices of array which share the same value
		//	Explicitly exclude the starting node. We don't want to come back to starting node
		unordered_map<int, vector<int>> graph;
		for (int i = 0; i < len; ++i) {

			//	Optimization Technique - 
			//  Say we have 3,3,3,3. The middle two 3's actually don't make a difference. So we skip them
			if ((i - 1 >= 0 && arr[i - 1] == arr[i]) && (i + 1 < len && arr[i + 1] == arr[i])) continue;

			if (graph.count(arr[i])) graph.emplace(arr[i], vector<int>() );
			graph[arr[i]].push_back(i);
		}

		//	Construction of the state recording HashMap - Index -> distance
		//	Preferred to use HashMap because not all node necessary is explored in BFS or DFS
		unordered_map<int, int> dist;
		dist[0] = 0;

		//	Queue of the index to be explored
		queue<int> queue;
		queue.push(0);

		//	Exploration BFS begins
		while (!queue.empty()) {
			int idx = queue.front(); queue.pop();
			int dis = dist[idx];

			//	Reached the end index. Since is BFS it shall be shortest path
			if (idx == len - 1) return dis;

			for (int shared : graph[arr[idx]]) {
				//	Only write when the shared node is never touched before
				if (!dist.count(shared)) {
					dist[shared] = dis + 1;
					queue.push(shared);
				}
			}

			//	Left side
			if (idx - 1 > 0 && !dist.count(idx - 1)) {
				dist[idx - 1] = dis + 1;
				queue.push(idx - 1);
			}

			// Right side
			if (idx + 1 < len && !dist.count(idx + 1)) {
				dist[idx + 1] = dis + 1;
				queue.push(idx + 1);
			}
		}
		return -1;
	}



	//	Since we are BFS, we guarantee that when we retrieved the node, it will be at minimum distance from start
	//	Therefore for nodes with same value, after assigning each one of them a value, immediately delete them
	//	since the job is done: We assigned them with minimum distance already!
	//	Also, we don't have to make a map from index to distance. Using BFS property of counting layer (Like counting
	//	depth of BT), we can just use a visited Set
	int minJumps2(vector<int> arr) {
		const int len = arr.size();

		//	Construct of the graph which maps a value to indices of array which share the same value
		//	Explicitly exclude the starting node. We don't want to come back to starting node
		unordered_map<int, vector<int>> graph;
		for (int i = 0; i < len; ++i) {
			if (!graph.count(arr[i])) graph[arr[i]] = vector<int>();
			graph[arr[i]].push_back(i);
		}

		unordered_set<int> visited;
		visited.insert(0);

		//	Queue of the indices to be explored in BFS
		queue<int> queue;
		queue.push(0);

		int layerDepth = 0;

		//	Exploration BFS begins
		while (!queue.empty()) {
			int f = queue.size();

			while (f-- > 0) {
				int idx = queue.front(); queue.pop();

				//	Reached the end index. Since is BFS it shall be shortest path
				if (idx == len - 1) return layerDepth;

				if (graph.count(arr[idx])) {
					for (int shared : graph[arr[idx]]) {
						if (visited.insert(shared).second)
							queue.push(shared);
					}
					//	Remove so we don't have to iterate once more!
					graph.erase(arr[idx]);
				}

				//	Left side
				if (idx - 1 > 0 && visited.insert(idx - 1).second)
					queue.push(idx - 1);

				//	Right side
				if (idx + 1 < len && visited.insert(idx + 1).second)
					queue.push(idx + 1);

			}
			++layerDepth;
		}
		return -1;
	}
};