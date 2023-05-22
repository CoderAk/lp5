#include <iostream>
#include <omp.h>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    vector<TreeNode*> children;
    TreeNode(int x) : val(x) {}
};

void pBFS(TreeNode* root) {
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int qs = q.size();
        #pragma omp parallel for
        for (int i = 0; i < qs; i++) {
            TreeNode* node;
            #pragma omp critical
            {
                node = q.front();
                cout << node->val << " ";
                q.pop();
            }
            for (TreeNode* child : node->children) {
                #pragma omp critical
                {
                    q.push(child);
                }
            }
        }
    }
}

void pDFS(TreeNode* root) {
    stack<TreeNode*> s;
    s.push(root);
    while (!s.empty()) {
        int ss = s.size();
        #pragma omp parallel for
        for (int i = 0; i < ss; i++) {
            TreeNode* node;
            #pragma omp critical
            {
                node = s.top();
                cout << node->val << " ";
                s.pop();
            }
            int numChildren = node->children.size();
            for (int j = numChildren - 1; j >= 0; j--) {
                #pragma omp critical
                {
                    s.push(node->children[j]);
                }
            }
        }
    }
}

int main() {
    // Construct Tree
    TreeNode* tree = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);
    TreeNode* node8 = new TreeNode(8);
    TreeNode* node9 = new TreeNode(9);
    TreeNode* node10 = new TreeNode(10);
    TreeNode* node11 = new TreeNode(11);
    TreeNode* node12 = new TreeNode(12);
    TreeNode* node13 = new TreeNode(13);
    TreeNode* node14 = new TreeNode(14);
    TreeNode* node15 = new TreeNode(15);

    tree->children.push_back(node2);
    tree->children.push_back(node3);
    tree->children.push_back(node4);
    node2->children.push_back(node5);
    node2->children.push_back(node6);
    node3->children.push_back(node7);
    node3->children.push_back(node8);
    node3->children.push_back(node9);
    node4->children.push_back(node10);
    node4->children.push_back(node11);
    node5->children.push_back(node12);
    node5->children.push_back(node13);
    node6->children.push_back(node14);
    node7->children.push_back(node15);

    /*
    Our Tree Looks like this:
                1
           /    |    \
          2     3      4
        /  \  / | \    / \
       5   6  7 8 9   10  11
      / \  |  |     
     12 13 14 15     
              

    */

    cout << "Parallel BFS: ";
    pBFS(tree);
    cout << "\n";
    cout << "Parallel DFS: ";
    pDFS(tree);
}
