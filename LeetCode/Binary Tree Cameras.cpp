#include <unordered_set>
#include <array>
using namespace std;

//https://leetcode.com/problems/binary-tree-cameras/
/*
 * 	This is a Dynamic Programming, Tree Depth First Search (Postorder Traversal), Greedy Problem
 *
 * 	I couldn't do it without looking at solution
 *
 * 	By observation, you'll see that instead of placing a camera at leaf nodes, placing at their parent is more optimal.
 * 	Therefore, using this idea, we can have a HashSet of observed nodes, and perform postorder traversal and adding
 * 	cameras along the way.
 * 	We perform postorder traversal because of the order where root is explored only after its children had been explored.
 *
 * 	The criteria to put camera are:
 * 		>	Parent is null, and the node itself is not yet observed
 * 		>	Any of children is not observed
 *
 * 	----------------------------------------------------------------------
 *
 * 	The DP approach is a bit more advanced (and for me, hard to figure), but for those who are familiar, seems straightforward
 *
 * 	First, realize that a node can be strictly in 3 states only:
 *
 * 		1	Camera is installed at this node
 * 		2	No camera is installed, but is monitored by its children
 * 		3	Not monitored.
 *
 * 	To achieve above states, those properties must be satisfy by its children. Since DP asserts the node's children MUST
 *  be monitored:
 *
 * 		1	Since camera is installed at this node, children can be either 1,2,3 (NO restriction)
 * 		2	Either left child or right child has camera installed (1). The other can be (1) or (2)
 * 		3	To be not monitored, children must strictly be in state (2), because presence of camera in children
 * 			means parent will be monitored too.
 *
 * 	For each node, query its children and get an array of size 3 representing the minumum camera needed to achieve that state.
 */

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};



class Solution {
public:

	//	Greedy Approach	
	int minCameraCover(TreeNode* root) {
		unordered_set<TreeNode*> covered;
		covered.insert(nullptr);
		return greedy(root, nullptr, covered);
	}
	int greedy(TreeNode* root, TreeNode* parent, unordered_set<TreeNode*>& covered) {
		if (!root) return 0;
		int ans = 0;
		ans += greedy(root->left, root, covered);
		ans += greedy(root->right, root, covered);

		//	> If the parent is null (root node), and node itself is not yet covered, OR
		//	> Any of the child is not covered
		if ((!parent & !covered.count(root)) || !covered.count(root->left) || !covered.count(root->right)) {
			ans += 1;
			covered.insert(root);
			covered.insert(parent);
			covered.insert(root->left);
			covered.insert(root->right);
		}
		return ans;
	}





	//	DP Approach
	int minCameraCover2(TreeNode* root) {
		array<int, 3> res = dp(root);
		return min(res[0], res[1]);
	}
	//	The DP array returned is of state:
	//	{ installed camera, monitored but no cameraa, not monitored }
	array<int, 3> dp(TreeNode* root) {
		if (!root) return { 1,0,0 };

		auto leftStates = dp(root->left);
		auto rightStates = dp(root->right);

		//	Install here. Children can in any states
		int installHere = 1 +
			min(leftStates[0], min(leftStates[1], leftStates[2]))
			+
			min(rightStates[0], min(rightStates[1], rightStates[2]));

		//	Monitored but no camera. Children must at least 1 is monitored. Ohter one can be monitored or installed cam
		int isMonitored = min(
			leftStates[0] + min(rightStates[0], rightStates[1]),
			rightStates[0] + min(leftStates[0], leftStates[1])
		);

		//	Not monitored. Children must strictly be monitored but no cam.
		//	If children install camera, then this node (parent) won't be unmonitored!
		int unMonitored = leftStates[1] + rightStates[1];
	
		return { installHere, isMonitored, unMonitored };
	}
};