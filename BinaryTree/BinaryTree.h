#pragma once

#include <iostream>
// BinaryTree::Node


template<typename T>
class BinaryTree
{
private:
	template <typename U>
	struct Node
	{
	public: // por defecto en una struct, todo es público, pero lo pongo por claridad.
		Node(U in_data, Node<U>* in_parent, Node<U>* in_left = nullptr, Node<U>* in_right = nullptr) :
			data(in_data), parent(in_parent), left(in_left), right(in_right)
		{
		}

		~Node()
		{
		}

		U data; // datos que va a guardar este nodo.
		Node<U>* parent; // referencia al nodo padre de este nodo dentro del árbol.
		Node<U>* left; // Hijo izquierdo
		Node<U>* right; // Hijo derecho.
	};

	Node<T>* root; // Nodo raíz del árbol.

public:
	BinaryTree() : root(nullptr)
	{
	}

	~BinaryTree()
	{
		// Aquí es donde sí tenemos que destruir los nodos restantes
		// PENDIENTE.
		while (root != nullptr)
		{
			DeleteNode(root);
		}
	}

	Node<T>* GetRoot()
	{
		return root;
	}

	// regresa el mínimo de un Subárbol a partir del nodo raíz de dicho subárbol.
	Node<T>* MinimumFromNode(Node<T>* in_root)
	{
		Node<T>* temp = in_root;
		while (temp->left != nullptr)
		{
			temp = temp->left;
		}
		return temp;
	}

	// regresa el mínimo desde la raíz del árbol
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

	// Máximo de un subárbol con raíz en in_root
	Node<T>* MaximumFromNode(Node<T>* in_root)
	{
		Node<T>* temp = in_root;
		while (temp->right != nullptr)
		{
			temp = temp->right;
		}
		return temp;
	}

	// Máximo de todo el árbol.
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
				// Los valores repetidos, se añadirán como nodos en el subárbol derecho
				// porque así lo establece el pseudocódigo del libro.
				// Pero hay otras variantes que lo pueden manejar de otra manera,para obtener ciertos beneficios.
				temp = temp->right;
			}
		}
		// temp puede ser nullptr si no se encontró un nodo con data==value; si sí se encontró, pues temp es 
		// dicho nodo.
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
				// Los valores repetidos, se añadirán como nodos en el subárbol derecho
				// porque así lo establece el pseudocódigo del libro.
				// Pero hay otras variantes que lo pueden manejar de otra manera,para obtener ciertos beneficios.
				temp_parent = temp;
				temp = temp->right;
			}
		}

		// Cuando se salga de este while, ya estamos donde deberíamos de insertar Value
		// Necesitamos decirle a este nodo nuevo, quién es su nodo padre.		
		Node<T>* newNode = new Node<T>(value, temp_parent);
		// Ahora hacemos la conexión de padre a hijo, dependiendo de si es hijo izquierdo o derecho.
		if (temp_parent == nullptr)
		{
			// entonces el árbol estaba vacío.
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
			// entonces sí tiene un subárbol derecho. Necesitamos el nodo más chico de dicho subárbol derecho
			return MinimumFromNode(in_x->right);
		}
		else
		{
			// empezamos con el padre del nodo al cual queremos encontrar su sucesor.
			Node<T>* current = in_x;  // current es 9
			Node<T>* temp_parent = in_x->parent; // temp parent es 8
			while (temp_parent != nullptr && temp_parent->right == current)
			{
				// Si seguimos siendo el hijo derecho de nuestro padre, todavía no vamos a romper este while.
				current = current->parent; // ahora current es 5
				temp_parent = current->parent; // ahora el padre de current es nullptr
			}
			return temp_parent; // se regresa el nodo nullptr
		}
	}

	// Aquí iría la función Predecessor()
	// Node<T>* Predecessor(Node<T>* in_x)
	//{}


	/*
	*	In Order
		Viaja al sub-árbol izquierdo de este nodo, recursivamente.
		Visita el nodo actual.
		Viaja al sub-árbol derecho de este nodo, recursivamente.
	*/
	void InOrder(Node<T>* in_x)
	{
		if (in_x != nullptr)
		{
			InOrder(in_x->left);
			std::cout << in_x->data << ", ";
			InOrder(in_x->right);
		}
		// Si no, no se hace nada, y solo se sale de la función.
	}

	/*
	*	Pre-Order
	Visita el nodo actual.
	Viaja al sub-árbol izquierdo de este nodo, recursivamente.
	Viaja al sub-árbol derecho de este nodo, recursivamente.
	*/
	void PreOrder(Node<T>* in_x)
	{
		if (in_x != nullptr)
		{
			std::cout << in_x->data << ", ";
			PreOrder(in_x->left);
			PreOrder(in_x->right);
		}
		// Si no, no se hace nada, y solo se sale de la función.
	}

	/*
	*	Post-Order
	Viaja al sub-árbol izquierdo de este nodo, recursivamente.
	Viaja al sub-árbol derecho de este nodo, recursivamente.
	Visita el nodo actual.
	*/
	void PostOrder(Node<T>* in_x)
	{
		if (in_x != nullptr)
		{
			PostOrder(in_x->left);
			PostOrder(in_x->right);
			std::cout << in_x->data << ", ";
		}
		// Si no, no se hace nada, y solo se sale de la función.
	}

	void Transplant(Node<T>* in_u, Node<T>* in_v)
	{
		if (in_u->parent == nullptr)
		{
			// Entonces U es el nodo raíz. Actualizamos la raíz del árbol
			root = in_v;
		}
		else if (in_u == in_u->parent->left)
		{
			// Si U es el hijo izquierdo de su padre, 
			// le dices al padre que ahora su hijo izquierdo 
			// será V
			in_u->parent->left = in_v;
		}
		else
		{
			// Si no era el hijo izquierdo, entonces era el derecho
			// y hay que actualizarlo de U a V
			in_u->parent->right = in_v;
		}
		if (in_v != nullptr)
		{
			// Si V sí es un nodo, pone que el padre de V
			// es el mismo que el padre de U
			in_v->parent = in_u->parent;
		}
	}

	void DeleteNode(Node<T>* in_z)
	{

		if (in_z->left == nullptr)
		{
			// Si el hijo izquierdo de Z es nullptr,
			// entonces remplazamos Z por su hijo derecho.
			Transplant(in_z, in_z->right);
		}
		else if (in_z->right == nullptr)
		{
			// Si el hijo derecho de Z es nullptr,
			// entonces remplazamos Z por su hijo izquierdo.
			Transplant(in_z, in_z->left);
		}
		else
		{
			// Todo esto es para el caso 3, que es el complicado del Delete
			// Primero, obtenemos el sucesor de Z
			Node<T>* Y = MinimumFromNode(in_z->right);
			// Checamos que Y no sea el sucesor inmediato a la derecha
			if (Y != in_z->right)
			{
				// Entonces este es el caso engorroso.
				Transplant(Y, Y->right);
				// Después, le decimos a Y que su derecha es ahora la 
				// derecha del Nodo Z que estamos quitando.
				Y->right = in_z->right;
				// Y le decimos al hijo derecho de Z que ahora su padre debe ser Y
				Y->right->parent = Y;
			}
			// Mover al sucesor al espacio de Z (al que vamos a quitar)
			Transplant(in_z, Y);
			// Quitarle el subárbol izquierdo a Z y dárselo a Y
			Y->left = in_z->left;
			// Decirle al subárbol izquierdo de Y, que ponga a Y como su padre
			Y->left->parent = Y;
		}

		// finalmente, sin importar cuál caso de Delete se usó, es necesario borrar al nodo Z.
		delete in_z;
	}

};