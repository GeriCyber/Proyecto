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
		int identacion;
		Node* copyNodes(Node *ptrNodo);									// Copia los nodos del arbol
		void destroyNodes(Node *ptrNodo);								// Destruye los nodos del arbol
		Node* Constructer(string s);									// Crea y retorna un nuevo nodo (recibe STRING)
	public:
		DOM_Tree();														// Constructor por defecto
		DOM_Tree(Element e, list<DOM_Tree> L);							// Constructor con parametros
		DOM_Tree(const DOM_Tree &orig);									// Constructor copia
		DOM_Tree &operator=(const DOM_Tree &orig);						// Sobrecarga del operador =
		void Public_Constructer(string s);								// Genera un arbol con un string dado
		bool es_nulo();													// Devuelve "true" si el arbol esta vacio
		DOM_Tree childNode(int p);										// Devuelve el hijo correspondiente a la posición p del arbol
		void appendChild(const int p, const DOM_Tree Arbol);			// Agrega un nuevo hijo en la posición p del arbol
		void appendChild(const DOM_Tree Arbol);							// Agrega un nuevo hijo en la ultima posicion
		void appendChild(string s);										// Agrega un nuevo hijo en la ultima posicion (Recibe STRING)
		void appendChild(int p, string s);								// Agrega un nuevo hijo en la posición p del arbol (Recibe STRING)
		void removeChild(int p);										// Elimina el hijo de la posición p del arbol.
		void replaceChild(int p, DOM_Tree Arbol);						// Cambia el subarbol de la posición p por otro subarbol dado
		void replaceChild(int p, string s);								// Cambia el subarbol de la posición p por un strind dado
		DOM_Tree getElementByID(string s);								// Devuelve el subarbol cuya raiz es el element que tenga el ID dado	
		friend ostream& operator << (ostream &out,const DOM_Tree &A);	// Sobrecarga del operador <<
		~DOM_Tree();													// Destructor
};
//======================================================================
ostream& operator << (ostream &out,const DOM_Tree &A)		
{
	DOM_Tree aux;
	list<string> L;
		
	if(A.nodoRaiz != NULL)
	{
		if(A.nodoRaiz -> element().tagName() == "document")
		{
			for (int i = 1; i <= A.identacion; i++)
					out << "\t";
			out << "<!doctype html>" << endl;
			if(A.nodoRaiz -> firstChild() != NULL)
			{
				aux.nodoRaiz = A.nodoRaiz -> firstChild();
				aux.identacion = A.identacion;
				out << aux;
			}
		}
		else
		{	
			if(!A.nodoRaiz -> element().attributeList().empty())
			{
				for (int i = 1; i <= A.identacion; i++)
					out << "\t";
				
				out << "<" << A.nodoRaiz -> element().tagName();
				L = A.nodoRaiz -> element().attributeList();
				while(!L.empty())
				{
					out << " " << L.front();
					L.pop_front();
				}
				
				out << ">";
				if(!A.nodoRaiz -> element().innerHTML().empty())
					out << A.nodoRaiz -> element().innerHTML();
				
			}
			else
			{
				for (int i = 1; i <= A.identacion; i++)
					out << "\t";
					
				out << "<" << A.nodoRaiz -> element().tagName() << ">";
				
				if(!A.nodoRaiz -> element().innerHTML().empty())
					out << A.nodoRaiz -> element().innerHTML();
				else
					out << endl;
					
			}
			if(A.nodoRaiz-> firstChild() != NULL && !A.nodoRaiz -> element().innerHTML().empty())
			{
				out << endl;
			}
			
			if(A.nodoRaiz -> firstChild() != NULL)
			{
				aux.nodoRaiz = A.nodoRaiz -> firstChild();
				aux.identacion = A.identacion + 1;
				out << aux;
			}
			if(A.nodoRaiz -> element().innerHTML().empty())
			{
				for (int i = 1; i <= A.identacion; i++)
				out << "\t";
			}
			else
			{
				if(A.nodoRaiz-> firstChild() != NULL)
				{
					for (int i = 1; i <= A.identacion; i++)
					out << "\t";
				}
			}
				
			out << "</" << A.nodoRaiz -> element().tagName() << ">" << endl;
			if(A.nodoRaiz-> nextSibling() != NULL) 
			{
				aux.nodoRaiz = A.nodoRaiz-> nextSibling();
				aux.identacion = A.identacion;
				out << aux;
			}
		}
	}
	else
		out << "DROM_Tree vacio!" << endl;
	aux.nodoRaiz=NULL;
	return out;
}
//======================================================================
void DOM_Tree::destroyNodes(Node *ptrNodo)	
{
	if(ptrNodo != NULL)
	{
		if(ptrNodo -> nextSibling() != NULL) 
			destroyNodes(ptrNodo -> nextSibling());
			
		if(ptrNodo -> firstChild() != NULL)
			destroyNodes(ptrNodo -> firstChild());	
			
		delete ptrNodo;	 // Destruir el nodo
		ptrNodo = NULL;	// Colocar en nulo
	}
}
//======================================================================
Node* DOM_Tree::Constructer(string s)
{
    Node *nuevo;
    string aux, cadena, nner,aux1,atri;
    int m,i=0, cont=0,j;
    Element e;
    list<string> L;

    if(s.empty())
        nuevo = NULL;

    else
    {
        size_t n = s.find(">");
        if(n != string::npos)
        {
            aux = s.substr(2,n-2);											
            if(aux == "doctype html" || aux == "DOCTYPE html") 			//solo para doctype
            {
                aux = "document";
                e.setTagName(aux);
                s.erase(s.begin(),s.begin()+n+1);
                cadena = s;
                m = s.length();
                s.erase(s.begin(),s.begin()+m);
            }
            else
            {
                j = s.find(" ");

                //cout << "Entro" << endl;
                if(j < n && j >= 0)
                {
                    aux = s.substr(1, j-1); // tagname
                    e.setTagName(aux);
                    s.erase(s.begin(),s.begin()+j+1);
                }
                else
                {

                    aux = s.substr(1,n-1);
                    e.setTagName(aux);		//tagname
                    s.erase(s.begin(), s.begin()+n);
                }

                if(s[0] != '>')
                {
                    n = s.find(">");
                    if(n != string::npos)
                    {
                        aux1 = s.substr(0,n);
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
                                    L.push_back(atri);
                                    aux1.erase(aux1.begin(), aux1.begin()+n+1);
                                }
                                i++;
                            }
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
                    s.erase(s.begin());

                if(s[0] == '<') //verifica si tiene inner
                {
                    if(s[1] == '/') // verifica si no tiene hijos
                    {
                        n = s.find(">");
                        if(n != string::npos)
                            s.erase(s.begin(), s.begin()+n+1);
                    }
                    else
                    {
                        n = s.find(aux);
                        if(n != string::npos)
                        {
                            cadena = s.substr(0, n-2);
                            m = aux.length();
                            s.erase(s.begin(),s.begin()+n+m+1);
                        }
                    }
                }
                else
                {
                    n = s.find("<");
                    if(n != string::npos)
                    {
                        nner = s.substr(0,n);
                        s.erase(s.begin(),s.begin()+n);
                        e.setInnerHTML(nner);
                        j = s.find(">");
                        if(s[0] == '<' && s[1] != '/')
                        {
							n = s.find(aux);
							if(n != string::npos)
							{
								cadena = s.substr(0, n-2);
								m = aux.length();
								s.erase(s.begin(),s.begin()+n+m+1);
							}
						}
						j = s.find(">");
                        if(j != -1)
                        {
                            s.erase(s.begin(), s.begin()+j);
                            s.erase(s.begin());
                        }
                    }
                }
            }
        }
        nuevo = new Node(e);
        nuevo -> setFirstChild(Constructer(cadena));
        nuevo -> setNextSibling(Constructer(s));
    }
    return nuevo;
}
//======================================================================
void DOM_Tree::Public_Constructer(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if(s[i] == '\\' && s[i+1] == 'n')
			s.erase(i,2);
		
		if(s[i] == '\\' && s[i+1] == 't')
			s.erase(i,2);
	}
	
	nodoRaiz = Constructer(s);
	identacion = 0;
}		
//======================================================================
DOM_Tree::DOM_Tree()
{
	nodoRaiz = NULL;
	identacion = 0;
}
//======================================================================
DOM_Tree::DOM_Tree(Element e, list<DOM_Tree> L)
{
	Node *aux;

	nodoRaiz = new Node(e);
	identacion = 0;
	if(!L.empty())
	{
		nodoRaiz -> setFirstChild(copyNodes(L.front().nodoRaiz));
		L.pop_front();
		aux = nodoRaiz -> firstChild();
		while(!L.empty()) 
		{
			aux -> setNextSibling(copyNodes(L.front().nodoRaiz));
			L.pop_front();
			aux = aux -> nextSibling();
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
	  destroyNodes(nodoRaiz);		
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
		aux = new Node(ptrNodo -> element());
		aux -> setFirstChild(copyNodes(ptrNodo -> firstChild()));
		aux -> setNextSibling(copyNodes(ptrNodo -> nextSibling()));
		return aux;
	}
}
//======================================================================
bool DOM_Tree::es_nulo()
{
	return(nodoRaiz == NULL);
}
//======================================================================
// La posicion debe estar previamente validada!
DOM_Tree DOM_Tree::childNode(int p) 
{
	Node *aux;
	DOM_Tree A;
	int i=1;
	
	aux = nodoRaiz -> firstChild();
	
	while(aux != NULL && i < p)		
	{
		aux = aux -> nextSibling(); 
		i++;
	}
	
	if(i == p && aux != NULL)
	{
		A.nodoRaiz = copyNodes(aux);
		A.nodoRaiz -> setNextSibling(NULL);
	}
	return(A);
}
//======================================================================
// La posicion debe estar previamente validada!
void DOM_Tree::appendChild(const int p, const DOM_Tree Arbol)
{
	Node *aux, *ant;
	int i,longi=1;
	if(nodoRaiz == NULL)
	{
		nodoRaiz = copyNodes(Arbol.nodoRaiz);
	}
	else
	{
		if(p == 1)
		{
			aux = nodoRaiz -> firstChild();
			nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
			nodoRaiz -> firstChild() -> setNextSibling(aux);
		}
		else
		{
			aux = nodoRaiz-> firstChild();
			ant = aux;
			while(aux != NULL)
			{
				ant = aux;
				aux = aux -> nextSibling();
				longi++;
			}
			if(p == longi + 1)
			{
				ant -> setNextSibling(copyNodes(Arbol.nodoRaiz));
				ant -> nextSibling() -> setNextSibling(NULL);
			}
			else
			{
				ant = nodoRaiz ->firstChild();
				aux = ant -> nextSibling();
				for (i = 2; i < p; i++)
				{
					ant = aux;
					aux = aux -> nextSibling();
				}
				if(i == p)
				{
					ant -> setNextSibling(copyNodes(Arbol.nodoRaiz));
					ant -> nextSibling() -> setNextSibling(aux);
				}
			}	
		}
	}
}
//======================================================================
void DOM_Tree::appendChild(const DOM_Tree Arbol)
{
	Node *act,*ant;
	if(nodoRaiz != NULL)
	{
		act = nodoRaiz -> firstChild();
		if(act == NULL)
			nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
			
		else
		{			
			ant = act;
			while(act != NULL)
			{
				ant = act;
				act = act ->nextSibling();
			}
			ant -> setNextSibling(copyNodes(Arbol.nodoRaiz));
			ant -> nextSibling() -> setNextSibling(NULL);
		}
	}
	else
		nodoRaiz = copyNodes(Arbol.nodoRaiz);
}
//======================================================================
void DOM_Tree::appendChild(string s)
{
	DOM_Tree A;
	if(!s.empty())	
	{
		A.Public_Constructer(s);
		appendChild(A);
	}
}
//======================================================================
// La posicion debe estar previamente validada!
void DOM_Tree::appendChild(int p, string s)
{
	DOM_Tree A;
	if(!s.empty())
	{
		A.Public_Constructer(s);
		appendChild(p,A);
	}
}
//======================================================================
// La posicion debe estar previamente validada!
void DOM_Tree::removeChild(int p)
{
	Node *aux, *elim;
	int i;
	if(p > 0)
	{
		if(p == 1)
		{
			elim = nodoRaiz -> firstChild();
			nodoRaiz -> setFirstChild(nodoRaiz -> firstChild() -> nextSibling());
		}
		else
		{
			aux = nodoRaiz -> firstChild();
			for(i = 2; i < p; i++)
			{
				aux = aux -> nextSibling();
			}
			elim = aux -> nextSibling();
			aux -> setNextSibling(aux -> nextSibling() -> nextSibling());
		}
		elim -> setNextSibling(NULL);
		destroyNodes(elim);
	}
}
//======================================================================
// La posicion debe estar previamente validada!
void DOM_Tree::replaceChild(int p, DOM_Tree Arbol)			
{
	Node *aux, *sig;
	int i=2;
	
	aux = nodoRaiz -> firstChild();
	if(p == 1)
	{
		nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
		nodoRaiz -> firstChild() -> setNextSibling(aux -> nextSibling());
	}
	else
	{
		sig = aux -> nextSibling();
		while(sig != NULL && i < p)
		{
			aux = sig;
			sig = sig -> nextSibling();
			i++;
		}
		if(i == p)
		{
			aux -> setNextSibling(copyNodes(Arbol.nodoRaiz));
			aux -> nextSibling() -> setNextSibling(sig -> nextSibling());
		}
	}
}
//======================================================================
// La posicion debe estar previamente validada!
void DOM_Tree::replaceChild(int p, string s)							
{
	Node *aux, *sig;
	int i=2;
	DOM_Tree Arbol;
	
	Arbol.Public_Constructer(s);
	
	aux = nodoRaiz -> firstChild();
	if(p == 1)
	{
		nodoRaiz -> setFirstChild(copyNodes(Arbol.nodoRaiz));
		nodoRaiz -> firstChild() -> setNextSibling(aux -> nextSibling());
	}
	else
	{
		sig = aux -> nextSibling();
		while(sig != NULL && i < p)
		{
			aux = sig;
			sig = sig -> nextSibling();
			i++;
		}
		if(i == p)
		{
			aux -> setNextSibling(copyNodes(Arbol.nodoRaiz));
			aux -> nextSibling() -> setNextSibling(sig -> nextSibling());
		}
	}
}
//======================================================================
DOM_Tree DOM_Tree::getElementByID(string s)
{
	bool located=false;
	string cadena;
	DOM_Tree A,B;
	
	if(nodoRaiz != NULL)
	{
		if(!nodoRaiz -> element().attributeList().empty())
		{
			list<string> L;
			L = nodoRaiz -> element().attributeList();
			
			while(!L.empty() && !located)
			{
				cadena=L.front();
				L.pop_front();
				if(cadena[0] == 'i' && cadena[1] == 'd')
				{
					cadena = cadena.substr(4,cadena.size()-5);
					if(cadena == s)
						located=true;
				}
			}
		}
		if(located)
		{
			B.nodoRaiz = copyNodes(nodoRaiz);
			B.nodoRaiz -> setNextSibling(NULL);
			return B;
		}
		else
		{
			if(nodoRaiz->firstChild() != NULL)	
			{
				A.nodoRaiz = nodoRaiz->firstChild();
				B=A.getElementByID(s);
			}	
			
			if(nodoRaiz ->nextSibling() != NULL)	
			{
				A.nodoRaiz = nodoRaiz->nextSibling();
				B=A.getElementByID(s);
			}
		}
	}
	A.nodoRaiz=NULL;
	return B;
}
//======================================================================
DOM_Tree::~DOM_Tree()
{
	destroyNodes(nodoRaiz);
}                    
#endif	
