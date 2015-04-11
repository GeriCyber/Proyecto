#ifndef ELEMENT_H
#define ELEMENT_H
#include <iostream>
#include <list>
#include <string>
using namespace std;
//======================================================================
/* Clase Element */
class Element
{
	private:
		string tag;
		list<string> attrList;
		string inner;
	public:
	    Element();														// Constructor por defecto
		Element(string tn);												// Crea un elemento (recibe TAGNAME)
		Element(string tn, list<string> l);								// Crea un elemento (recibe TAGNAME y ATTRLIST)
		Element(string tn, list<string> l, string nner);				// Crea un elemento (recibe TAGNAME, ATTRLIST y INNERHTML)
		Element(list<string> l, string nner);							// Crea un elemento (recibe TAGNAME y INNERHTML)
		Element(const Element &e);										// Constructor copia
		Element &operator=(const Element &e);							// Sobrecarga del operador =
		string tagName();												// Devuelve el nombre del elemento
		list<string> attributeList();									// Devuelve la lista de atributos del elemento
		string innerHTML();												// Devuelve el texto guardado en el nodo
		void setTagName(const string tn);								// Cambia el nombre del elemento
		void setAttributeList(const list<string> L);					// Cambia la lista de atributos del elemento
		void setInnerHTML(const string ihtml);							// Cambia el texto guardado en el elemento
		//~Element();
};
//======================================================================
Element::Element()
{
	tag = "";
	inner = "";
}
//======================================================================
Element::Element(string tn)
{
	tag = tn;
	inner = "";
}
//======================================================================
Element::Element(string tn, list<string> l)
{
	tag = tn;
	attrList = l;
	inner = "";
}
//======================================================================
Element::Element(string tn, list<string> l, string nner)
{
	tag = tn;
	attrList = l;
	inner = nner;
}
//======================================================================
Element::Element(list<string> l, string nner)
{
	attrList = l;
	inner = nner;
}
//======================================================================
Element::Element(const Element &e)
{
	tag = e.tag;
	attrList = e.attrList;
	inner = e.inner;
}
//======================================================================
Element &Element::operator=(const Element &e)
{
   if(this != &e)
   {  
		tag = e.tag;
		attrList = e.attrList;
		inner = e.inner;
   }
   return *this;
}
//======================================================================
string Element::tagName()
{
	return tag;
}
//======================================================================
list<string> Element::attributeList()
{
	return attrList;
}
//======================================================================
string Element::innerHTML()
{
	return inner;
}
//======================================================================
void Element::setTagName(const string tn)
{
	tag= tn;
}
//======================================================================
void Element::setAttributeList(const list<string> L)
{
	attrList = L;
}
//======================================================================
void Element::setInnerHTML(const string ihtml)
{
	inner = ihtml;
}
	
#endif		
