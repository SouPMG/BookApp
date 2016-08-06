#ifndef LIBRARY_H
#define LIBRARY_H

#include "libraryitem.h"

class library {
	private:
		// internal private class node
		class node {
			public:
				node();
				node(libraryItem*, node*);
				libraryItem* info; // pointer to pure virtual base class
				node* next;
		};
		node* first;

	public:
		library();
		bool empty() const;
		void addItem(libraryItem*);
		void removeItem(libraryItem*);
		libraryItem* extract();
};

#endif // LIBRARY_H
