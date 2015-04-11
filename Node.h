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
		Node *first;
		Node *next;
	public:
		Node(): e(Element()), first(NULL), next(NULL) {}	// Constructor por defecto
		Node(Element elmt, Node *fc, Node *ns); 						// Constructor con element y apuntador hijo y hermano
		Node(Element elmt);												// Constructor con element 
		Node(const Node &n);											// Constructor copia
		Node &operator=(const Node &n);									// Sobrecarga del operador =
		Element element() const;										// Devuelve el elemento almacenado en el nodo
		Node* firstChild() const;									// Devuelve el apuntador a su primer hijo
		Node* nextSibling() const;									// Devuelve el apuntador a su hermano derecho
		void setElement(Element elmt);									// Modifica el elemento almacenado en el nodo
		void setFirstChild(Node *firstChild);							// Modifica el apuntador a su primer hijo
		void setNextSibling(Node *nextSibling);							// Modifica el apuntador a su hermano derecho
};
//======================================================================		
 Node::Node(Element elmt, Node *fc, Node *ns)
{
	e = elmt;
	first = fc;
	next = ns;
}
//======================================================================
Node::Node(Element elmt)
{
	e = elmt;
	first = NULL;
	next = NULL;
}
//======================================================================
Node::Node(const Node &n)
{
	e = n.e;
	first = n.first;
	next = n.next;
}
//======================================================================
Node &Node::operator=(const Node &n)
{
	if(this != &n)
	{
		e = n.e;
		first = n.first;
		next = n.next;
	}
	return(*this);
}	
//======================================================================
Element Node::element() const
{
	return e;
}
//======================================================================
Node* Node::firstChild() const
{
	return (first);
}
//======================================================================
Node* Node::nextSibling() const
{
	return (next);
}
//======================================================================
void Node::setElement(Element elmt)
{
	e = elmt;
}
//======================================================================
void Node::setFirstChild(Node *firstChild)
{
	this -> first = firstChild; 
}
//======================================================================
void Node::setNextSibling(Node *nextSibling)
{
	this -> next = nextSibling; 
}
#endif	
