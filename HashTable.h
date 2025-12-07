#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include <string>
#include "PRA_2025_P1/ListLinked.h"  // ¡¡¡¡MODIFICAR!!!!

using namespace std;
template <typename V>
class HashTable: public Dict<V> {

    private:
       int n;
       int max;
       ListLinked<TableEntry<V>>* table;

       int h(string key){
	       int c=0;
	       for(int i=0; i < key.size();i++){
	       		c += int(key.at(i));
	       }
       		return	(c % max); 
       };

    public:
        //Constructor
        HashTable(int size){
	 	this -> n = 0;
		this -> max = size;		
		this -> table = new ListLinked<TableEntry<V>>[size];
	}
	
	//Destructor
	~HashTable(){
		delete [] table;
	}

	int capacity() const{
		return this->max;
	}

	friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th){
		out << "HashTable [entries: "; 
		 
		out << th.n;
		out <<" , capacity: "<< th.capacity() << "]"<< endl;
		out << "==========" << endl;

		for(int i = 0; i < th.max; i++){
			out << "== Cubeta " << i << " ==" << endl;
			out << th.table[i];
		}
		out << "==========" << endl;
		return out;
	}


	V operator[](std::string key){
		return	search(key);
	}

	void insert(string key, V value) override {
		if (table[h(key)].search(TableEntry<V>(key)) != -1) {
			throw std::runtime_error("La clave ya existe");
		}
		table[h(key)].prepend(TableEntry<V>(key, value));
		n++;
	}

	V search(string key) override {
		int pos = table[h(key)].search(TableEntry<V>(key));
		if (pos == -1) {
			throw std::runtime_error("La clave no existe");
		}
		return table[h(key)].get(pos).value;
	}

	V remove(string key)override{
		int pos = table[h(key)].search(TableEntry<V>(key));
		if (pos == -1) {
			throw std::runtime_error("La clave no existe");
		}
		V val = table[h(key)].get(pos).value;
		table[h(key)].remove(pos);
		n--;
		return val;
	}

	int entries()override{
		return n;
	}
	
};

#endif
