#ifndef DOM_TREE_H
#define DOM_TREE_H
#include "Node.h"
#include "Element.h"
#include <iostream>
#include <list>
using namespace std;
//======================================================================
/*Clase DOM_Tree */
class DOM_Tree
{
	private:
		Node *nodoRaiz;
		Node* copyNodes(Node *ptrNodo);									// Copia los nodos del arbol
		void destroyNodes(Node *ptrNodo);								// Destruye los nodos del arbol
	public:
		DOM_Tree();														// Constructor por defecto
		DOM_Tree(Element e, list<DOM_Tree> L);							// Constructor con parametros
		DOM_Tree(const DOM_Tree &orig);									// Constructor copia
		DOM_Tree &operator=(const DOM_Tree &orig);						// Sobrecarga del operador =
		// Sobrecarga operador << 
		void copiar(DOM_Tree &Arbol);									// Copia un arbol
		bool es_nulo();													// Devuelve "true" si el arbol esta vacio
		DOM_Tree childNode(int p);
		void appendChild(int p, DOM_Tree Arbol);
		void removeChild(int p);										// Elimina el hijo de la posición p del arbol.
		void replaceChild(int p, DOM_Tree Arbol);
		DOM_Tree getElementByID(Element e); 								
		~DOM_Tree();													// Destructor
};
//======================================================================
DOM_Tree::DOM_Tree()
{
	nodoRaiz = NULL;
}
//======================================================================
DOM_Tree::DOM_Tree(Element e, list<DOM_Tree> L)
{
	Node *aux;

	nodoRaiz = new Node(e);
	
	if(!L.empty())
	{
		nodoRaiz -> setFirstChild(copyNodes(L.front().nodoRaiz));
		L.pop_front();
		aux = nodoRaiz -> getFirstChild();
		while(!L.empty()) 
		{
			aux -> setNextSibling(copyNodes(L.front().nodoRaiz));
			L.pop_front();
			aux = aux -> getNextSibling();
		}
	}
}
//======================================================================
DOM_Tree::DOM_Tree(const DOM_Tree &orig)
{
	nodoRaiz = copyNodes(orig.nodoRaiz);
}
//======================================================================
DOM_Tree &DOM_Tree::operator=(const DOM_Tree &orig)
{
   if(this != &orig)
   {  destroyNodes(nodoRaiz);
      nodoRaiz = copyNodes(orig.nodoRaiz);
   }
   return *this;
}
//======================================================================
Node* DOM_Tree::copyNodes(Node *ptrNodo)
{
	Node *aux;

	if(ptrNodo == NULL) 
		return NULL;
	else
	{
		aux = new Node(ptrNodo -> getElement());
		aux -> setFirstChild(copyNodes(ptrNodo -> getFirstChild()));
		aux -> setNextSibling(copyNodes(ptrNodo -> getNextSibling()));
		return aux;
	}
}
//======================================================================
void DOM_Tree::copiar(DOM_Tree &Arbol)
{
	nodoRaiz = copyNodes(Arbol.nodoRaiz);
}
//======================================================================
bool DOM_Tree::es_nulo()
{
	return(nodoRaiz == NULL);
}
//======================================================================
void DOM_Tree::removeChild(int p)
{
	Node *aux, *elim;
	int i;
	
	if(p == 1)
	{
		elim = nodoRaiz -> getFirstChild();
		nodoRaiz -> setFirstChild(nodoRaiz -> getFirstChild() -> getNextSibling());
	}
	else
	{
		aux = nodoRaiz -> getFirstChild();
		for(i = 2; i < p; i++)
		{
			aux = aux -> getNextSibling();
		}
		elim = aux -> getNextSibling();
		aux -> setNextSibling(aux -> getNextSibling() -> getNextSibling());
	}
	elim -> setNextSibling(NULL);
	destroyNodes(elim);
}
//======================================================================
void DOM_Tree::destroyNodes(Node *ptrNodo)	
{
	if(ptrNodo != NULL)
	{
		if(ptrNodo -> getNextSibling() != NULL) 
			destroyNodes(ptrNodo -> getNextSibling());
			
		if(ptrNodo -> getFirstChild() != NULL)
			destroyNodes(ptrNodo -> getFirstChild());	
			
		delete ptrNodo;	 // Destruir el nodo
		ptrNodo = NULL;	// Colocar en nulo
	}
}
//======================================================================
DOM_Tree::~DOM_Tree()
{
	destroyNodes(nodoRaiz);
}                    
#endif	
