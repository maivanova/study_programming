#include <iostream>
#include <algorithm>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	int maxPathSum(TreeNode* root) {
		int maxSum = std::numeric_limits<int>::min();
		maxPathSumHelper(root, maxSum);
		return maxSum;
	}

private:
	int maxPathSumHelper(TreeNode* node, int& maxSum) {
		if (!node) {
			return 0;
		}

		int leftMax = std::max(maxPathSumHelper(node->left, maxSum), 0);
		int rightMax = std::max(maxPathSumHelper(node->right, maxSum), 0);

		int currentSum = node->val + leftMax + rightMax;
		maxSum = std::max(maxSum, currentSum);

		return node->val + std::max(leftMax, rightMax);
	}
};

int main() {
	TreeNode* root = new TreeNode(-20);
	root->left = new TreeNode(10);
	root->right = new TreeNode(15);
	root->right->left = new TreeNode(5);
	root->right->right = new TreeNode(13);

	Solution solution;
	int result = solution.maxPathSum(root);

	std::cout << result << std::endl;

	delete root->left;
	delete root->right->left;
	delete root->right->right;
	delete root->right;
	delete root;

	return 0;
}


