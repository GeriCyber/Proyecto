#ifndef NODO_H
#define NODO_H
#include <iostream>
//======================================================================
template <class T>
class Nodo
{
private:
    Nodo *hizq, *hder;
    T dato;
public:
	Nodo(): dato(T()), hizq(NULL), hder(NULL) {}						//Constructor
	Nodo(const Nodo &n): dato(n.dato), hizq(n.hizq), hder(n.hder) {}	//Constructor copia
	T getDato() const
    {
        return(dato); 				   									//Obtener dato
    }
    void setDato(const T &d)
    {
        dato = d;														//Modificar dato
    };
    Nodo* obt_hizq() const
    {
        return (hizq);    												//Obtener nodo (hijo izquierdo)
    }
    Nodo* obt_hder() const
    {
        return (hder);    												//Obtener nodo (hermano derecho)
    }
    void modf_hizq(Nodo* hizq)
    {
        this -> hizq = hizq;    										//Modificar nodo (hijo izquierdo)
    }
    void modf_hder(Nodo* hder)
    {
        this -> hder = hder;    										//Modificar nodo (hermano derecho)
    }
};
#endif
    
