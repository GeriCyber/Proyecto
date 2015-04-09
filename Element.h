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
		string tagName;
		list<string> attrList;
		string innerHTML;
	public:
	    Element();														// Constructor por defecto
		Element(string tn);												// Crea un elemento (recibe TAGNAME)
		Element(string tn, list<string> l);								// Crea un elemento (recibe TAGNAME y ATTRLIST)
		Element(string tn, list<string> l, string inner);				// Crea un elemento (recibe TAGNAME, ATTRLIST y INNERHTML)
		Element(list<string> l, string inner);							// Crea un elemento (recibe TAGNAME y INNERHTML)
		Element(const Element &e);										// Constructor copia
		Element &operator=(const Element &e);							// Sobrecarga del operador =
		string get_tagName();											// Devuelve el nombre del elemento
		list<string> attributeList();									// Devuelve la lista de atributos del elemento
		string get_innerHTML();											// Devuelve el texto guardado en el nodo
		void set_tagNAme(const string tn);								// Cambia el nombre del elemento
		void setAttributeList(const list<string> L);					// Cambia la lista de atributos del elemento
		void setInnerHTML(const string ihtml);							// Cambia el texto guardado en el elemento
		//~Element();
};
//======================================================================
Element::Element()
{
	tagName = "";
	innerHTML = "";
}
//======================================================================
Element::Element(string tn)
{
	tagName = tn;
	innerHTML = "";
}
//======================================================================
Element::Element(string tn, list<string> l)
{
	tagName = tn;
	attrList = l;
	innerHTML = "";
}
//======================================================================
Element::Element(string tn, list<string> l, string inner)
{
	tagName = tn;
	attrList = l;
	innerHTML = inner;
}
//======================================================================
Element::Element(list<string> l, string inner)
{
	attrList = l;
	innerHTML = inner;
}
//======================================================================
Element::Element(const Element &e)
{
	tagName = e.tagName;
	attrList = e.attrList;
	innerHTML = e.innerHTML;
}
//======================================================================
Element &Element::operator=(const Element &e)
{
   if(this != &e)
   {  
		tagName = e.tagName;
		attrList = e.attrList;
		innerHTML = e.innerHTML;
   }
   return *this;
}
//======================================================================
string Element::get_tagName()
{
	return tagName;
}
//======================================================================
list<string> Element::attributeList()
{
	return attrList;
}
//======================================================================
string Element::get_innerHTML()
{
	return innerHTML;
}
//======================================================================
void Element::set_tagNAme(const string tn)
{
	tagName = tn;
}
//======================================================================
void Element::setAttributeList(const list<string> L)
{
	attrList = L;
}
//======================================================================
void Element::setInnerHTML(const string ihtml)
{
	innerHTML = ihtml;
}
	
#endif		
