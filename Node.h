#ifndef NODE_H
#define NODE_H
#include "Element.h"
#include <iostream>
//======================================================================
/* Clase Node */
class Node
{
	private:
		Element e;
		Node *firstChild;
		Node *nextSibling;
	public:
		Node(): e(Element()), firstChild(NULL), nextSibling(NULL) {}	// Constructor por defecto
		Node(Element elmt, Node *fc, Node *ns); 						// Constructor con element y apuntador hijo y hermano
		Node(Element elmt);												// Constructor con element 
		Node(const Node &n);											// Constructor copia
		// Sobrecarga del operador =
		Element getElement() const;										// Devuelve el elemento almacenado en el nodo
		Node* getFirstChild() const;									// Devuelve el apuntador a su primer hijo
		Node* getNextSibling() const;									// Devuelve el apuntador a su hermano derecho
		void setElement(const Element &elmt);							// Modifica el elemento almacenado en el nodo
		void setFirstChild(Node *firstChild);							// Modifica el apuntador a su primer hijo
		void setNextSibling(Node *nextSibling);							// Modifica el apuntador a su hermano derecho
};
//======================================================================		
 Node::Node(Element elmt, Node *fc, Node *ns)
{
	e = elmt;
	firstChild = fc;
	nextSibling = ns;
}
//======================================================================
Node::Node(Element elmt)
{
	e = elmt;
	firstChild = NULL;
	nextSibling = NULL;
}
//======================================================================
Node::Node(const Node &n)
{
	e = n.e;
	firstChild = n.firstChild;
	nextSibling = n.nextSibling;
}
//======================================================================
Element Node::getElement() const
{
	return e;
}
//======================================================================
Node* Node::getFirstChild() const
{
	return (firstChild);
}
//======================================================================
Node* Node::getNextSibling() const
{
	return (nextSibling);
}
//======================================================================
void Node::setFirstChild(Node *firstChild)
{
	this -> firstChild = firstChild; 
}
//======================================================================
void Node::setNextSibling(Node *nextSibling)
{
	this -> nextSibling = nextSibling; 
}
#endif	
