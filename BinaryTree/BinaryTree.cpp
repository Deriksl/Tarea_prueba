#include "BinaryTree.h"

// Implementación de la función Predecessor.
template<typename T>
typename BinaryTree<T>::Node<T>* BinaryTree<T>::Predecessor(Node<T>* in_x) {
    if (in_x->left != nullptr) {
        return MaximumFromNode(in_x->left);
    }
    else {
        Node<T>* current = in_x;
        Node<T>* temp_parent = in_x->parent;
        while (temp_parent != nullptr && temp_parent->left == current) {
            current = current->parent;
            temp_parent = current->parent;
        }
        return temp_parent;
    }
}

// Implementación de la función InOrderIterative.
template<typename T>
void BinaryTree<T>::InOrderIterative() {
    std::stack<Node<T>*> nodeStack;
    Node<T>* current = root;

    while (current != nullptr || !nodeStack.empty()) {
        while (current != nullptr) {
            nodeStack.push(current);
            current = current->left;
        }

        current = nodeStack.top();
        nodeStack.pop();
        std::cout << current->data << ", ";

        current = current->right;
    }
}

// Implementación de la función PreOrderIterative.
template<typename T>
void BinaryTree<T>::PreOrderIterative() {
    if (root == nullptr) {
        return;
    }

    std::stack<Node<T>*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node<T>* current = nodeStack.top();
        nodeStack.pop();
        std::cout << current->data << ", ";

        if (current->right != nullptr) {
            nodeStack.push(current->right);
        }
        if (current->left != nullptr) {
            nodeStack.push(current->left);
        }
    }
}

// Implementación de la función PostOrderIterative.
template<typename T>
void BinaryTree<T>::PostOrderIterative() {
    if (root == nullptr) {
        return;
    }

    std::stack<Node<T>*> nodeStack;
    std::stack<T> outputStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node<T>* current = nodeStack.top();
        nodeStack.pop();
        outputStack.push(current->data);

        if (current->left != nullptr) {
            nodeStack.push(current->left);
        }
        if (current->right != nullptr) {
            nodeStack.push(current->right);
        }
    }

    while (!outputStack.empty()) {
        std::cout << outputStack.top() << ", ";
        outputStack.pop();
    }
}

