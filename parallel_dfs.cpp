#include <iostream>
#include <vector>
#include <stack>
#include <omp.h>

// Structure to represent a tree node
struct TreeNode {
    int id;
    std::vector<TreeNode*> children;
    bool visited;

    TreeNode(int _id) : id(_id), visited(false) {}
};

// Function to perform parallel DFS on a tree
void parallelDFS(TreeNode* rootNode) {
    std::stack<TreeNode*> stack;
    #pragma omp parallel shared(stack)
    {
        #pragma omp single
        {
            stack.push(rootNode);
            rootNode->visited = true;
        }

        while (!stack.empty()) {
            TreeNode* current;
            #pragma omp critical
            {
                current = stack.top();
                stack.pop();
            }

            std::cout << "Visited node: " << current->id << " (Thread " << omp_get_thread_num() << ")" << std::endl;

            // Process children of the current node
            #pragma omp task shared(stack)
            {
                for (TreeNode* child : current->children) {
                    #pragma omp critical
                    {
                        if (!child->visited) {
                            stack.push(child);
                            child->visited = true;
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int numNodes;
    std::cout << "Enter the number of nodes in the tree: ";
    std::cin >> numNodes;

    // Create tree nodes
    std::vector<TreeNode*> nodes(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        nodes[i] = new TreeNode(i + 1);
    }

    // Input tree structure
    std::cout << "Enter the tree edges (parent child):" << std::endl;
    for (int i = 1; i < numNodes; ++i) {
        int parent, child;
        std::cin >> parent >> child;

        nodes[parent - 1]->children.push_back(nodes[child - 1]);
    }

    // Perform parallel DFS
    parallelDFS(nodes[0]);

    // Clean up memory
    for (TreeNode* node : nodes) {
        delete node;
    }

    return 0;
}
