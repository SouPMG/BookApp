#ifndef LIBRARY_H
#define LIBRARY_H

#include "libraryitem.h"

template <class T>
class library {
	private:
		// internal private class node
		template <class T>
		class node {
			public:
				node();
				node(const T&, node*);
				T info;
				node* next;
		};
		node* first;

	public:
		library();
		bool empty() const;
		void addItem(T);
		void removeItem(T);
		T extract();
};

#endif // LIBRARY_H
