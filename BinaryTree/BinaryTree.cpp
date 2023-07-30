#include <iostream>
#include <stack>

template<typename T>
class BinaryTree
{
public: // Corregido: Declarar Node como public para que Predecessor tenga acceso.
    template <typename U>
    struct Node
    {
    public:
        Node(U in_data, Node<U>* in_parent, Node<U>* in_left = nullptr, Node<U>* in_right = nullptr) :
            data(in_data), parent(in_parent), left(in_left), right(in_right)
        {
        }

        ~Node()
        {
        }

        U data;
        Node<U>* parent;
        Node<U>* left;
        Node<U>* right;
    };

    Node<T>* root;

public:
    BinaryTree() : root(nullptr)
    {
    }


    ~BinaryTree()
    {
        while (root != nullptr)
        {
            DeleteNode(root);
        }
    }

    Node<T>* GetRoot()
    {
        return root;
    }

    Node<T>* MinimumFromNode(Node<T>* in_root)
    {
        Node<T>* temp = in_root;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    Node<T>* Minimum()
    {
        return MinimumFromNode(root);
    }

    T MinimumValue()
    {
        Node<T>* temp = Minimum();
        if (temp != nullptr)
        {
            return temp->data;
        }
    }

    Node<T>* MaximumFromNode(Node<T>* in_root)
    {
        Node<T>* temp = in_root;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    Node<T>* Maximum()
    {
        return MaximumFromNode(root);
    }

    T MaximumValue()
    {
        Node<T>* temp = Maximum();
        if (temp != nullptr)
        {
            return temp->data;
        }
    }

    Node<T>* Search(T value)
    {
        Node<T>* temp = root;
        while (temp != nullptr && temp->data != value)
        {
            if (value < temp->data)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        return temp;
    }

    void Insert(T value)
    {
        Node<T>* temp = root;
        Node<T>* temp_parent = nullptr;
        while (temp != nullptr)
        {
            if (value < temp->data)
            {
                temp_parent = temp;
                temp = temp->left;
            }
            else
            {
                temp_parent = temp;
                temp = temp->right;
            }
        }

        Node<T>* newNode = new Node<T>(value, temp_parent);
        if (temp_parent == nullptr)
        {
            root = newNode;
        }
        else if (value < temp_parent->data)
        {
            temp_parent->left = newNode;
        }
        else
        {
            temp_parent->right = newNode;
        }
    }

    Node<T>* Sucessor(Node<T>* in_x)
    {
        if (in_x->right != nullptr)
        {
            return MinimumFromNode(in_x->right);
        }
        else
        {
            Node<T>* current = in_x;
            Node<T>* temp_parent = in_x->parent;
            while (temp_parent != nullptr && in_x == temp_parent->left)
            {
                current = temp_parent;
                temp_parent = current->parent;
            }
            return temp_parent;
        }
    }

    Node<T>* Predecessor(Node<T>* in_x)
    {
        if (in_x->left != nullptr)
        {
            return MaximumFromNode(in_x->left);
        }

        Node<T>* temp_parent = in_x->parent;
        while (temp_parent != nullptr && in_x == temp_parent->left)
        {
            in_x = temp_parent;
            temp_parent = temp_parent->parent;
        }

        return temp_parent;
    }

    void InOrder(Node<T>* in_x)
    {
        if (in_x != nullptr)
        {
            InOrder(in_x->left);
            std::cout << in_x->data << ", ";
            InOrder(in_x->right);
        }
    }

    void PreOrder(Node<T>* in_x)
    {
        if (in_x != nullptr)
        {
            std::cout << in_x->data << ", ";
            PreOrder(in_x->left);
            PreOrder(in_x->right);
        }
    }

    void PostOrder(Node<T>* in_x)
    {
        if (in_x != nullptr)
        {
            PostOrder(in_x->left);
            PostOrder(in_x->right);
            std::cout << in_x->data << ", ";
        }
    }

    void Transplant(Node<T>* in_u, Node<T>* in_v)
    {
        if (in_u->parent == nullptr)
        {
            root = in_v;
        }
        else if (in_u == in_u->parent->left)
        {
            in_u->parent->left = in_v;
        }
        else
        {
            in_u->parent->right = in_v;
        }
        if (in_v != nullptr)
        {
            in_v->parent = in_u->parent;
        }
    }

    void DeleteNode(Node<T>* in_z)
    {
        if (in_z->left == nullptr)
        {
            Transplant(in_z, in_z->right);
        }
        else if (in_z->right == nullptr)
        {
            Transplant(in_z, in_z->left);
        }
        else
        {
            Node<T>* Y = MinimumFromNode(in_z->right);
            if (Y != in_z->right)
            {
                Transplant(Y, Y->right);
                Y->right = in_z->right;
                Y->right->parent = Y;
            }
            Transplant(in_z, Y);
            Y->left = in_z->left;
            Y->left->parent = Y;
        }

        delete in_z;
    }

    void InOrderIterative()
    {
        std::stack<Node<T>*> nodeStack;
        Node<T>* current = root;

        while (current != nullptr || !nodeStack.empty())
        {
            while (current != nullptr)
            {
                nodeStack.push(current);
                current = current->left;
            }

            current = nodeStack.top();
            nodeStack.pop();

            std::cout << current->data << ", ";

            current = current->right;
        }
    }

    void PreOrderIterative()
    {
        std::stack<Node<T>*> nodeStack;
        if (root != nullptr)
            nodeStack.push(root);

        while (!nodeStack.empty())
        {
            Node<T>* current = nodeStack.top();
            nodeStack.pop();

            std::cout << current->data << ", ";

            if (current->right != nullptr)
                nodeStack.push(current->right);

            if (current->left != nullptr)
                nodeStack.push(current->left);
        }
    }

    void PostOrderIterative()
    {
        std::stack<Node<T>*> nodeStack;
        Node<T>* current = root;
        Node<T>* lastVisited = nullptr;

        while (current != nullptr || !nodeStack.empty())
        {
            if (current != nullptr)
            {
                nodeStack.push(current);
                current = current->left;
            }
            else
            {
                Node<T>* temp = nodeStack.top();
                if (temp->right != nullptr && temp->right != lastVisited)
                {
                    current = temp->right;
                }
                else
                {
                    std::cout << temp->data << ", ";
                    lastVisited = temp;
                    nodeStack.pop();
                }
            }
        }
    }
};

int main()
{
    BinaryTree<int> tree;

    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(8);
    tree.Insert(2);
    tree.Insert(4);
    tree.Insert(7);
    tree.Insert(9);

    std::cout << "InOrder Recursive: ";
    tree.InOrder(tree.GetRoot());
    std::cout << std::endl;

    std::cout << "InOrder Iterative: ";
    tree.InOrderIterative();
    std::cout << std::endl;

    std::cout << "PreOrder Recursive: ";
    tree.PreOrder(tree.GetRoot());
    std::cout << std::endl;

    std::cout << "PreOrder Iterative: ";
    tree.PreOrderIterative();
    std::cout << std::endl;

    std::cout << "PostOrder Recursive: ";
    tree.PostOrder(tree.GetRoot());
    std::cout << std::endl;

    std::cout << "PostOrder Iterative: ";
    tree.PostOrderIterative();
    std::cout << std::endl;

    int value = 7;
    typename BinaryTree<int>::Node<int>* node = tree.Search(value);
    if (node != nullptr)
    {
        std::cout << "Found node with value " << value << std::endl;
        typename BinaryTree<int>::Node<int>* predecessor = tree.Predecessor(node);
        if (predecessor != nullptr)
            std::cout << "Predecessor of " << value << " is " << predecessor->data << std::endl;
        else
            std::cout << "No predecessor for " << value << std::endl;
    }
    else
    {
        std::cout << "Node with value " << value << " not found" << std::endl;
    }

    return 0;
}
