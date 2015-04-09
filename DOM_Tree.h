#ifndef DOM_TREE_H
#define DOM_TREE_H
#include "Node.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;
//======================================================================
/*Clase DOM_Tree */
class DOM_Tree
{
	private:
		Node* nodoRaiz;
		Node* copyNodes(Node *ptrNodo);									// Copia los nodos del arbol
		void destroyNodes(Node *ptrNodo);								// Destruye los nodos del arbol
		Node* construir(string s);										// Crea y retorna un nuevo nodo (recibe STRING)
		//Element construir_raiz(string &s);								// Construye el elemento la raiz y lo retorna
		Node* buscar_getElementByID(string s, Node *p);					// Busca el nodo con el ID dado
	public:
		DOM_Tree();														// Constructor por defecto
		DOM_Tree(Element e, list<DOM_Tree> L);							// Constructor con parametros
		DOM_Tree(const DOM_Tree &orig);									// Constructor copia
		DOM_Tree &operator=(const DOM_Tree &orig);						// Sobrecarga del operador =
		void copy(DOM_Tree &Arbol);	
		void construir_publico(string s);									// Copia un arbol
		bool es_nulo();													// Devuelve "true" si el arbol esta vacio
		DOM_Tree childNode(int p);										// Devuelve el hijo correspondiente a la posición p del arbol
		void appendChild(const int p, const DOM_Tree Arbol);			// Agrega un nuevo hijo en la posición p del arbol
		void appendChild(const DOM_Tree Arbol);							// Agrega un nuevo hijo en la ultima posicion
		void appendChild(string s);										// Agrega un nuevo hijo en la ultima posicion (Recibe STRING)
		void appendChild(int p, string s);								// Agrega un nuevo hijo en la posición p del arbol (Recibe STRING)
		void removeChild(int p);										// Elimina el hijo de la posición p del arbol.
		void replaceChild(int p, DOM_Tree Arbol);						// Cambia el subarbol de la posición p por otro subarbol dado
		void replaceChild(int p, string s);								// Cambia el subarbol de la posición p por un strind dado
		DOM_Tree getElement(string s);									// Devuelve el subarbol cuya raiz es el element que tenga el ID dado	
		~DOM_Tree();													// Destructor
		friend ostream& operator << (ostream &out,const DOM_Tree &A)		// Sobrecarga del operador <<
		{
			DOM_Tree aux;
			list<string> L;
		
			//cout << "Entro sobrecarga" << endl;
			if(A.nodoRaiz != NULL)
			{
				//cout << "Entro sobrecarga 1" << endl;
				if(A.nodoRaiz -> getElement().get_tagName() == "document")
				{
					//cout << "Entro sobrecarga 2" << endl;
					out << "<!doctype html>" << endl;
					if(A.nodoRaiz -> getFirstChild() != NULL) // esto lo puedes quitar
					{
						aux.nodoRaiz = A.nodoRaiz -> getFirstChild();
						//cout << "entro doctype" << endl;
						out << aux;
					}
				}
				else
				{
					//cout << "Entro sobrecarga 3" << endl;
					out << "<" << A.nodoRaiz -> getElement().get_tagName();
					if(!A.nodoRaiz -> getElement().attributeList().empty())
					{
						L = A.nodoRaiz -> getElement().attributeList();
						while(!L.empty())
						{
							out << " " << L.front();
							L.pop_front();
						}
					}
					out << ">" << endl;;
						
					if(!A.nodoRaiz -> getElement().get_innerHTML().empty())
						out << A.nodoRaiz -> getElement().get_innerHTML() << endl;;
					//cout << "Entro resursion" << endl;
					if(A.nodoRaiz -> getFirstChild() != NULL) // esto lo puedes quitar
					{
						aux.nodoRaiz = A.nodoRaiz -> getFirstChild();
						out << aux;
					}
					//cout << "salio recursion" << endl;
					out << "</" << A.nodoRaiz -> getElement().get_tagName() << ">" << endl;;
					//cout << "Entro resursion 2" << endl;
					if(A.nodoRaiz-> getNextSibling() != NULL) // esto lo puedes quitar
					{
						aux.nodoRaiz = A.nodoRaiz-> getNextSibling();
						out << aux;
					}
					//cout << "salio recursion 2" << endl;
						
				}
			}
			aux.nodoRaiz=NULL;
			return out;
		}
};
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
Node* DOM_Tree::construir(string s) //revisar metodo
{
	Node *nuevo;
	string aux, cadena, nner,aux1,atri;
	int m,i=0, cont=0;
	Element e;
	list<string> L;
	
	if(s.empty())
	{
		nuevo = NULL;
	}
	else
	{
		size_t n = s.find(">");
		if(n != string::npos)
		{
			aux = s.substr(2,n-2);
			if(aux == "doctype html")
			{
				aux = "document";
				//cout << "taganme:" << aux << endl;
				e.set_tagNAme(aux);
				///cout << "tagname:" << e.get_tagName() << endl;
				s.erase(s.begin(),s.begin()+n+1);
				//nuevo = new Node(e);
				//cout << "Recursion 1" << endl;
				cadena = s;
				m = s.length();
				s.erase(s.begin(),s.begin()+m);
				/*if(s.empty())
				{
					cout << "s es vacia" << endl;
				}*/
			}
			else
			{
				size_t j = s.find(" ");
				if(j != string::npos)
				{
					if(j < n)
					{
						aux = s.substr(1, j-1); // tagname
						//cout << "Tagname1:" << aux << endl;
						e.set_tagNAme(aux);
						///cout << "tagname:" << e.get_tagName() << endl;
						s.erase(s.begin(),s.begin()+j+1);
						//cout << " S" << s << endl;
					}
					else
					{
						aux = s.substr(1,n-1);
						//cout << "Tagname2:" << aux << endl;
						e.set_tagNAme(aux);		//tagname
						///cout << "tagname:" << e.get_tagName() << endl;
						s.erase(s.begin(), s.begin()+n);
						//cout << "S1" << s << endl;
					}
					
					if(s[0] != '>')
					{
						n = s.find(">");
						if(n != string::npos)
						{
							aux1 = s.substr(0,n);
							///cout << "atributo:" << aux1 << endl;
							s.erase(s.begin(), s.begin()+n+1);
							m = aux1.length(); // m= longitud de los atributos 
							while(i <= m)
							{
								if(aux1[i] == ' ')
								{
									cont++;
								}
								i++;
							}
							
							if(cont > 0)
							{
								i=0;
								while(i < cont)       // si hay mas atributos los metera en la lista
								{
									n = aux1.find(" ");
									if(n != string::npos)
									{
										atri = aux1.substr(0,n-1);
										///cout << "atributo:" << atri << endl;
										L.push_back(atri);
										aux1.erase(aux1.begin(), aux1.begin()+n+1);
									}
									i++;
								}
								///cout << "atributo:" << aux1 << endl;
								L.push_back(aux1);
							}
							else
							{
								L.push_back(aux1);
							}
							e.setAttributeList(L);
						}
					}
					else
					{
						s.erase(s.begin());

					}
					
					if(s[0] == '<') //verifica si tiene inner
					{
						if(s[1] == '/') // verifica si no tiene hijos
						{
							n = s.find(">");
							if(n != string::npos)
							{
								s.erase(s.begin(), s.begin()+n+1);
							}
						}
						else
						{
							n = s.find(aux);
							//cout << aux << endl;
							if(n != string::npos)
							{
								cadena = s.substr(0, n-2);
								//cout << "Hijo:" << cadena << endl;
								m = aux.length();
								s.erase(s.begin(),s.begin()+n+m+1);
								//cout << "S1" << s << endl;
							}
						}
					}
					else
					{
						n = s.find("<");
						if(n != string::npos)
						{
							//validar con npos
							nner = s.substr(0,n);
							s.erase(s.begin(),s.begin()+n+1);	//n
							//cout << "Inner:" << nner << endl;
							e.setInnerHTML(nner);
							///cout << "Inner:" << e.get_innerHTML() << endl;
							j = s.find(">");
							//cout << j << endl;
							if(j != string::npos)
							{
								s.erase(s.begin(), s.begin()+j);
								s.erase(s.begin());
								//cout << "s:" << s << endl;
							}
						}
					}
				}
			}
			/*if(!s.empty())
			{
				cout << "Hermano: " << s << endl;
			}
			if(!cadena.empty())
			{
				cout << "Hijo: " << cadena << endl;
			}*/
			nuevo = new Node(e);
		}
		//cout << "Recursion 2 " << endl;
		nuevo -> setFirstChild(construir(cadena));
		//cout << "Recursion 3" << endl;
		nuevo -> setNextSibling(construir(s));
		//cout << "paso" << endl;	
		
	}
	return nuevo;
}
//======================================================================
void DOM_Tree::construir_publico(string s)
{
	nodoRaiz = construir(s); //copynodes
	//cout << "salio construir" << endl;
}		
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
   {  
	  destroyNodes(nodoRaiz);		// fsdfsgsgv 
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
void DOM_Tree::copy(DOM_Tree &Arbol)
{
	nodoRaiz = copyNodes(Arbol.nodoRaiz);
}
//======================================================================
bool DOM_Tree::es_nulo()
{
	return(nodoRaiz == NULL);
}
//======================================================================
DOM_Tree DOM_Tree::childNode(int p) //validar p
{
	Node *aux;
	DOM_Tree A;
	int i=1;
	
	aux = nodoRaiz -> getFirstChild();
	
	while(aux != NULL && i < p)		// !=
	{
		aux = aux -> getNextSibling(); //aqui creo que es aux, obviar
		i++;
	}
	
	if(i == p && aux != NULL)
	{
		A.nodoRaiz = copyNodes(aux);
	}
	return(A);
}
//======================================================================
void DOM_Tree::appendChild(const int p, const DOM_Tree Arbol)
{
	Node *aux, *ant;
	int i,longi=1;
	if(p == 1)
	{
		aux = nodoRaiz -> getFirstChild();
		nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
		nodoRaiz -> getFirstChild() -> setNextSibling(aux);
	}
	else
	{
		aux = nodoRaiz-> getFirstChild();
		ant = aux;
		while(aux != NULL)
		{
			ant = aux;
			aux -> getNextSibling();
			longi++;
		}
		
		if(p == longi + 1)
		{
			ant -> setNextSibling(copyNodes(Arbol.nodoRaiz));
			ant -> getNextSibling() -> setNextSibling(NULL);
		}
		else
		{
			ant = nodoRaiz ->getFirstChild();
			aux = ant -> getNextSibling();
			for (i = 2; i < p; i++)
			{
				ant = aux;
				aux = aux -> getNextSibling();
			}
			if(i == p)
			{
				ant -> setNextSibling(copyNodes(Arbol.nodoRaiz));
				ant -> getNextSibling() -> setNextSibling(aux);
			}
		}	
	}
}
//======================================================================
void DOM_Tree::appendChild(const DOM_Tree Arbol)
{
	Node *act,*ant;
	
	act = nodoRaiz -> getFirstChild();
	
	if(act == NULL)
	{
		nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
	}
	else
	{
		ant = act;
		while(act != NULL)
		{
			ant = act;
			act = act ->getFirstChild();
		}
		ant -> setNextSibling(copyNodes(Arbol.nodoRaiz));
		ant -> getNextSibling() -> setNextSibling(NULL);
	}
}
//======================================================================
void DOM_Tree::appendChild(string s)
{
	DOM_Tree A;
	Node *act, *ant;
	string aux;
	
	if(!s.empty())
	{
		//A.nodoRaiz -> setElement(construir_raiz(s));
		//A.nodoRaiz -> setFirstChild(construir(s));        // Enlaza el nodo raiz con su hijo izquierdo 
		A.construir_publico(s);
		cout << "salio" << endl;
		act = nodoRaiz -> getFirstChild();
		if(act == NULL)
		{
			A.nodoRaiz -> setFirstChild(copyNodes(A.nodoRaiz));
		}
		else
		{
			ant = act;
			while(act != NULL)
			{
				ant = act;
				act = act ->getFirstChild();
			}
			ant -> setNextSibling(copyNodes(A.nodoRaiz));
			ant -> getNextSibling() -> setNextSibling(NULL);
		}
	}
}
//======================================================================
void DOM_Tree::appendChild(int p, string s)
{
	Node *aux, *ant;
	int i,longi=1;
	DOM_Tree A;
	
	if(!s.empty())
	{
		//A.nodoRaiz -> setElement(construir_raiz(s));
		A.nodoRaiz -> setFirstChild(construir(s));
	
		if(p == 1)
		{
			aux = nodoRaiz -> getFirstChild();
			nodoRaiz -> setFirstChild(copyNodes(A.nodoRaiz));
			nodoRaiz -> getFirstChild() -> setNextSibling(aux);
		}
		else
		{
			aux -> getFirstChild();
			ant = aux;
			while(aux != NULL)
			{
				ant = aux;
				aux -> getNextSibling();
				longi++;
			}
		
			if(p == longi + 1)
			{
				ant -> setNextSibling(copyNodes(A.nodoRaiz));
				ant -> getNextSibling() -> setNextSibling(NULL);
			}
			else
			{
				ant = nodoRaiz ->getFirstChild();
				aux = ant -> getNextSibling();
				for (i = 2; i < p; i++)
				{
					ant = aux;
					aux = aux -> getNextSibling();
				}
				if(i == p)
				{
					ant -> setNextSibling(copyNodes(A.nodoRaiz));
					ant -> getNextSibling() -> setNextSibling(aux);
				}	
			}	
		}
	}
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
void DOM_Tree::replaceChild(int p, DOM_Tree Arbol)
{
	Node *aux, *sig;
	int i=2;
	
	aux = nodoRaiz -> getFirstChild();
	if(p == 1)
	{
		nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
		nodoRaiz -> getFirstChild() -> setNextSibling(aux -> getNextSibling());
		destroyNodes(aux);
	}
	else
	{
		sig = aux -> getNextSibling();
		while(sig != NULL && i < p)
		{
			aux = sig;
			sig = sig -> getNextSibling();
			i++;
		}
		if(i == p)
		{
			aux -> setNextSibling(copyNodes(Arbol.nodoRaiz));
			aux -> getNextSibling() -> setNextSibling(sig -> getNextSibling());
			destroyNodes(sig);
		}
	}
}
//======================================================================
void DOM_Tree::replaceChild(int p, string s)
{
	Node *aux, *sig;
	int i=2;
	DOM_Tree Arbol;
	
	//Arbol.nodoRaiz -> setElement(construir_raiz(s));
	//Arbol=Arbol.construir_publico(s);
	
	aux = nodoRaiz -> getFirstChild();
	if(p == 1)
	{
		nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
		nodoRaiz -> getFirstChild() -> setNextSibling(aux -> getNextSibling());
		destroyNodes(aux);
	}
	else
	{
		sig = aux -> getNextSibling();
		while(sig != NULL && i < p)
		{
			aux = sig;
			sig = sig -> getNextSibling();
			i++;
		}
		if(i == p)
		{
			aux -> setNextSibling(copyNodes(Arbol.nodoRaiz));
			aux -> getNextSibling() -> setNextSibling(sig -> getNextSibling());
			destroyNodes(sig);
		}
	}
}
//======================================================================
Node* DOM_Tree::buscar_getElementByID(string s, Node *p)
{
	bool located=false;
	string cadena;
	
	if(p != NULL)
	{
		if(!p ->getElement().attributeList().empty())
		{
			list<string> L;
			L = p -> getElement().attributeList();
			
			while(!L.empty() && !located)
			{
				cadena=L.front();
				L.pop_front();
				if(cadena[0] == 'i' && cadena[1] == 'd')
				{
					cadena = cadena.substr(4,cadena.size()-5);
					if(cadena == s)
					{
						located=true;
					}
				}
			}
		}
		if(located)
		{
			return p;
		}
		else
		{
			buscar_getElementByID(s,p->getFirstChild());
			buscar_getElementByID(s,p->getNextSibling());
		}
	}
}
//======================================================================
DOM_Tree DOM_Tree::getElement(string s)
{
	DOM_Tree A;
	A.nodoRaiz=copyNodes(buscar_getElementByID(s,nodoRaiz));
	return (A);
}
//======================================================================
DOM_Tree::~DOM_Tree()
{
	destroyNodes(nodoRaiz);
}                    
#endif	
