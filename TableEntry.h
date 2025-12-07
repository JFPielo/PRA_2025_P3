#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>
using namespace std;

template <typename V> 
class TableEntry {
    public:
		//Atributos
		string key;
		V value;
	
	//Constructor 2 párametros
	TableEntry(string key, V value){
		this -> key = key;
		this -> value = value;
	}
	//Constructor 1 parámetro
	TableEntry(string key){
		this -> key = key; 
		this -> value = V{};
	}
	//Constructor vacío 
	TableEntry(){
		this -> key = "";
		this -> value = V{};
	}

	//Operador ==
	friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
	 	return (te1.key==te2.key) ? true : false;	
	}
	
	//Operador !=
	friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
	
		return (te1.key!=te2.key) ? true : false;	
	}

	//Operador << 
	friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
		out << "('" << te.key << "' " << "=>" << te.value << ")";
		return out;
	}
	
};

#endif
