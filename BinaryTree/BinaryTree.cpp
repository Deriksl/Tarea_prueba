#include <iostream>
#include <stack>

// Clase BinaryTree
template<typename T>
class BinaryTree
{
public:
    // Nodo del árbol
    template <typename U>
    struct Node
    {
        Node(U in_data, Node<U>* in_parent, Node<U>* in_left = nullptr, Node<U>* in_right = nullptr) :
            data(in_data), parent(in_parent), left(in_left), right(in_right)
        {
        }

        ~Node()
        {
        }

        U data; // Datos almacenados en el nodo.
        Node<U>* parent; // Puntero al nodo padre.
        Node<U>* left; // Puntero al nodo hijo izquierdo.
        Node<U>* right; // Puntero al nodo hijo derecho.
    };

    Node<T>* root; // Puntero al nodo raíz del árbol.

public:
    // Constructor de la clase BinaryTree
    BinaryTree() : root(nullptr)
    {
    }

    // Destructor de la clase BinaryTree
    ~BinaryTree()
    {
        while (root != nullptr)
        {
            DeleteNode(root);
        }
    }

    // Obtiene el nodo raíz del árbol.
    Node<T>* GetRoot()
    {
        return root;
    }

    // Obtiene el nodo mínimo de un subárbol a partir del nodo raíz de dicho subárbol.
    Node<T>* MinimumFromNode(Node<T>* in_root)
    {
        Node<T>* temp = in_root;
        while (temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }

    // Obtiene el nodo mínimo desde la raíz del árbol.
    Node<T>* Minimum()
    {
        return MinimumFromNode(root);
    }

    // Obtiene el valor mínimo del árbol.
    T MinimumValue()
    {
        Node<T>* temp = Minimum();
        if (temp != nullptr)
        {
            return temp->data;
        }
    }

    // Obtiene el nodo máximo de un subárbol a partir del nodo raíz de dicho subárbol.
    Node<T>* MaximumFromNode(Node<T>* in_root)
    {
        Node<T>* temp = in_root;
        while (temp->right != nullptr)
        {
            temp = temp->right;
        }
        return temp;
    }

    // Obtiene el nodo máximo del árbol.
    Node<T>* Maximum()
    {
        return MaximumFromNode(root);
    }

    // Obtiene el valor máximo del árbol.
    T MaximumValue()
    {
        Node<T>* temp = Maximum();
        if (temp != nullptr)
        {
            return temp->data;
        }
    }

    // Busca un valor en el árbol y devuelve el nodo que contiene dicho valor.
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

    // Inserta un valor en el árbol.
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

        // Cuando se sale del bucle, temp es nullptr, y temp_parent es el padre del nodo que vamos a insertar.
        Node<T>* newNode = new Node<T>(value, temp_parent);

        if (temp_parent == nullptr)
        {
            // Si temp_parent es nullptr, entonces el árbol estaba vacío y el nuevo nodo será la raíz.
            root = newNode;
        }
        else if (value < temp_parent->data)
        {
            // Si el valor es menor al valor del nodo padre, lo insertamos en el subárbol izquierdo.
            temp_parent->left = newNode;
        }
        else
        {
            // Si el valor es mayor o igual al valor del nodo padre, lo insertamos en el subárbol derecho.
            temp_parent->right = newNode;
        }
    }

    // Obtiene el sucesor (nodo que va después) del nodo in_x en el árbol.
    Node<T>* Sucessor(Node<T>* in_x)
    {
        if (in_x->right != nullptr)
        {
            // Si el nodo in_x tiene subárbol derecho, entonces el sucesor es el nodo mínimo de ese subárbol derecho.
            return MinimumFromNode(in_x->right);
        }
        else
        {
            // Si el nodo in_x no tiene subárbol derecho, entonces el sucesor es el primer nodo padre cuyo hijo izquierdo es el nodo in_x.
            Node<T>* current = in_x;
            Node<T>* temp_parent = in_x->parent;
            while (temp_parent != nullptr && in_x == temp_parent->right)
            {
                current = temp_parent;
                temp_parent = current->parent;
            }
            return temp_parent;
        }
    }

    // Obtiene el predecesor (nodo que va antes) del nodo in_x en el árbol.
    Node<T>* Predecessor(Node<T>* in_x)
    {
        if (in_x->left != nullptr)
        {
            // Si el nodo in_x tiene subárbol izquierdo, entonces el predecesor es el nodo máximo de ese subárbol izquierdo.
            return MaximumFromNode(in_x->left);
        }

        // Si el nodo in_x no tiene subárbol izquierdo, entonces el predecesor es el primer nodo padre cuyo hijo derecho es el nodo in_x.
        Node<T>* temp_parent = in_x->parent;
        while (temp_parent != nullptr && in_x == temp_parent->left)
        {
            in_x = temp_parent;
            temp_parent = temp_parent->parent;
        }

        return temp_parent;
    }

    // Recorre el árbol en orden (izquierda - raíz - derecha) de forma recursiva.
    void InOrder(Node<T>* in_x)
    {
        if (in_x != nullptr)
        {
            InOrder(in_x->left); // Recorre el subárbol izquierdo.
            std::cout << in_x->data << ", "; // Visita el nodo raíz.
            InOrder(in_x->right); // Recorre el subárbol derecho.
        }
    }

    // Recorre el árbol en orden (izquierda - raíz - derecha) de forma iterativa.
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

            std::cout << current->data << ", "; // Visita el nodo raíz.

            current = current->right;
        }
    }

    // Recorre el árbol en preorden (raíz - izquierda - derecha) de forma recursiva.
    void PreOrder(Node<T>* in_x)
    {
        if (in_x != nullptr)
        {
            std::cout << in_x->data << ", "; // Visita el nodo raíz.
            PreOrder(in_x->left); // Recorre el subárbol izquierdo.
            PreOrder(in_x->right); // Recorre el subárbol derecho.
        }
    }

    // Recorre el árbol en preorden (raíz - izquierda - derecha) de forma iterativa.
    void PreOrderIterative()
    {
        std::stack<Node<T>*> nodeStack;
        if (root != nullptr)
            nodeStack.push(root);

        while (!nodeStack.empty())
        {
            Node<T>* current = nodeStack.top();
            nodeStack.pop();

            std::cout << current->data << ", "; // Visita el nodo raíz.

            if (current->right != nullptr)
                nodeStack.push(current->right);

            if (current->left != nullptr)
                nodeStack.push(current->left);
        }
    }

    // Recorre el árbol en postorden (izquierda - derecha - raíz) de forma recursiva.
    void PostOrder(Node<T>* in_x)
    {
        if (in_x != nullptr)
        {
            PostOrder(in_x->left); // Recorre el subárbol izquierdo en postorden.
            PostOrder(in_x->right); // Recorre el subárbol derecho en postorden.
            std::cout << in_x->data << ", "; // Visita el nodo raíz.
        }
    }

    // Recorre el árbol en postorden (izquierda - derecha - raíz) de forma iterativa.
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
                    std::cout << temp->data << ", "; // Visita el nodo raíz.
                    lastVisited = temp;
                    nodeStack.pop();
                }
            }
        }
    }

    // Transplanta el subárbol con raíz en in_u por el subárbol con raíz en in_v.
    void Transplant(Node<T>* in_u, Node<T>* in_v)
    {
        if (in_u->parent == nullptr)
        {
            // Si in_u es la raíz del árbol, el nuevo árbol tendrá raíz en in_v.
            root = in_v;
        }
        else if (in_u == in_u->parent->left)
        {
            // Si in_u es un hijo izquierdo, el nuevo subárbol estará en el lugar del subárbol izquierdo de in_u.
            in_u->parent->left = in_v;
        }
        else
        {
            // Si in_u es un hijo derecho, el nuevo subárbol estará en el lugar del subárbol derecho de in_u.
            in_u->parent->right = in_v;
        }

        if (in_v != nullptr)
        {
            // Si in_v no es nullptr, establecemos su padre como el padre de in_u.
            in_v->parent = in_u->parent;
        }
    }

    // Elimina un nodo in_z del árbol.
    void DeleteNode(Node<T>* in_z)
    {
        if (in_z->left == nullptr)
        {
            // Si in_z no tiene subárbol izquierdo, lo reemplazamos por su subárbol derecho.
            Transplant(in_z, in_z->right);
        }
        else if (in_z->right == nullptr)
        {
            // Si in_z no tiene subárbol derecho, lo reemplazamos por su subárbol izquierdo.
            Transplant(in_z, in_z->left);
        }
        else
        {
            // Si in_z tiene ambos subárboles, encontramos el sucesor de in_z y lo reemplazamos por in_z.
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

        delete in_z; // Eliminamos el nodo in_z.
    }
};

// Función principal del programa.
int main()
{
    BinaryTree<int> tree;

    // Insertar valores en el árbol.
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(8);
    tree.Insert(2);
    tree.Insert(4);
    tree.Insert(7);
    tree.Insert(9);

    // Recorrer el árbol en orden (izquierda - raíz - derecha) de forma recursiva.
    std::cout << "InOrder Recursive: ";
    tree.InOrder(tree.GetRoot());
    std::cout << std::endl;

    // Recorrer el árbol en orden (izquierda - raíz - derecha) de forma iterativa.
    std::cout << "InOrder Iterative: ";
    tree.InOrderIterative();
    std::cout << std::endl;

    // Recorrer el árbol en preorden (raíz - izquierda - derecha) de forma recursiva.
    std::cout << "PreOrder Recursive: ";
    tree.PreOrder(tree.GetRoot());
    std::cout << std::endl;

    // Recorrer el árbol en preorden (raíz - izquierda - derecha) de forma iterativa.
    std::cout << "PreOrder Iterative: ";
    tree.PreOrderIterative();
    std::cout << std::endl;

    // Recorrer el árbol en postorden (izquierda - derecha - raíz) de forma recursiva.
    std::cout << "PostOrder Recursive: ";
    tree.PostOrder(tree.GetRoot());
    std::cout << std::endl;

    // Recorrer el árbol en postorden (izquierda - derecha - raíz) de forma iterativa.
    std::cout << "PostOrder Iterative: ";
    tree.PostOrderIterative();
    std::cout << std::endl;

    int value = 7;
    // Buscar el nodo con el valor especificado.
    typename BinaryTree<int>::Node<int>* node = tree.Search(value);
    if (node != nullptr)
    {
        std::cout << "Found node with value " << value << std::endl;

        // Encontrar el predecesor del nodo encontrado.
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

