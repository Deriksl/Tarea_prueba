#include <iostream>
#include "BinaryTree.cpp" // Including the implementation file directly for simplicity.

int main() {
    BinaryTree<int> tree;

    // Insert nodes into the tree.
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(3);
    tree.Insert(7);
    tree.Insert(12);
    tree.Insert(17);

    std::cout << "Inorder traversal: ";
    tree.InOrder(tree.GetRoot());
    std::cout << std::endl;

    std::cout << "Preorder traversal: ";
    tree.PreOrder(tree.GetRoot());
    std::cout << std::endl;

    std::cout << "Postorder traversal: ";
    tree.PostOrder(tree.GetRoot());
    std::cout << std::endl;

    // Test Predecessor function.
    BinaryTree<int>::Node<int>* node = tree.Search(12);
    if (node != nullptr) {
        BinaryTree<int>::Node<int>* predecessor = tree.Predecessor(node);
        if (predecessor != nullptr) {
            std::cout << "Predecessor of 12 is: " << predecessor->data << std::endl;
        }
        else {
            std::cout << "No predecessor found." << std::endl;
        }
    }

    // Test iterative traversals.
    std::cout << "Iterative Inorder traversal: ";
    tree.InOrderIterative();
    std::cout << std::endl;

    std::cout << "Iterative Preorder traversal: ";
    tree.PreOrderIterative();
    std::cout << std::endl;

    std::cout << "Iterative Postorder traversal: ";
    tree.PostOrderIterative();
    std::cout << std::endl;

    return 0;
}
