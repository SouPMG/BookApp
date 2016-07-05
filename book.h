#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <QString>
#include "libraryitem.h"

using std::ostream;

class book : public libraryItem {
	private:
		QString author;
		QString genre;
		unsigned int pages;
		unsigned int release;
	public:
		// constructor calling libraryItem constructor first
		book(QString, QString = "undefined", QString = "undefined", QString = "undefined", unsigned int = 1900, unsigned int = 0,
			   QString = "undefined", QString = "undefined", unsigned int = 0, unsigned int = 0);

		// implementation of pure virtual methods inherited by libraryItem
		virtual book* clone() const;

		// getter methods
		QString getAuthor() const;
		QString getGenre() const;
		unsigned int numberOfPages() const;
		unsigned int getReleaseNumber() const;

		// setter methods
		void setAuthor(QString);
		void setGenre(QString);
		void setPages(unsigned int);
		void setReleaseNumber(unsigned int);

		// operators
		bool operator==(const book&) const;
};

// external operators
ostream& operator<<(ostream&, const book&) const;

#endif // BOOK_H
