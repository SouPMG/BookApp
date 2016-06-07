#ifndef BOOK_H
#define BOOK_H

#include <string>
#include "libraryitem.h"

class book : public libraryItem {
	private:
		string author;
		string genre;
		unsigned int pages;
		unsigned int release;
	public:
		// constructor
		book ( string, string = "undefined", string = "undefined", string = "undefined", unsigned int = 1900, unsigned int = 0,
			   string = "undefined", string = "undefined", unsigned int = 0, unsigned int = 0 );

		// implementation of pure virtual methods inherited by libraryItem
		virtual book* clone() const;

		// getter methods
		string getAuthor() const;
		string getGenre() const;
		unsigned int numberOfPages() const;
		unsigned int getReleaseNumber() const;

		// setter methods
		void setAuthor ( string );
		void setGenre ( string );
		void setPages ( unsigned int );
		void setReleaseNumber ( unsigned int );
};

#endif // BOOK_H
