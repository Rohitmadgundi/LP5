#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

struct TreeNode {
    int data;
    std::vector<TreeNode*> children;
};

TreeNode* createNode(int data) {
    TreeNode* newNode = new TreeNode;
    newNode->data = data;
    return newNode;
}

TreeNode* buildTree() {
    int rootData, numNodes;
    std::cout << "Enter root node data: ";
    std::cin >> rootData;
    std::cout << "Enter the number of nodes: ";
    std::cin >> numNodes;

    std::vector<TreeNode*> nodes(numNodes);
    nodes[0] = createNode(rootData);

    for (int i = 1; i < numNodes; ++i) {
        int parentIndex, childData;
        std::cout << "Enter parent index and child data: ";
        std::cin >> parentIndex >> childData;

        TreeNode* newNode = createNode(childData);
        nodes[parentIndex]->children.push_back(newNode);
        nodes[i] = newNode;
    }

    return nodes[0]; // Return the root node
}

void parallelBFS(TreeNode* root) {
    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        #pragma omp parallel
        {
            #pragma omp for
            for (int i = 0; i < q.size(); ++i) {
                TreeNode* curr = q.front();
                q.pop();

                #pragma omp critical
                std::cout << curr->data << " ";

                for (const auto& child : curr->children) {
                    #pragma omp critical
                    q.push(child);
                }
            }
        }
    }
}

int main() {
    TreeNode* root = buildTree();

    std::cout << "Parallel BFS traversal: ";
    parallelBFS(root);
    std::cout << std::endl;

    return 0;
}
