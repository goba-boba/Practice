#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

int maxDiameter = 0;

int height(TreeNode* root) {
    if (!root) return 0;

    int leftH = height(root->left);
    int rightH = height(root->right);

    maxDiameter = max(maxDiameter, leftH + rightH);

    return 1 + max(leftH, rightH);
}

int diameterOfBinaryTree(TreeNode* root) {
    height(root);
    return maxDiameter;
}
int main() {
    setlocale(LC_ALL, "Russian");

    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(12);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(25);
    root->left->right = new TreeNode(30);
    root->right->right = new TreeNode(36);

    cout << "Диаметр дерева: " << diameterOfBinaryTree(root) << endl;

    return 0;
}
