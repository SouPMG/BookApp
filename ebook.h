#ifndef EBOOK_H
#define EBOOK_H

#include <iostream>
#include <QString>
#include "libraryitem.h"

using std::ostream;

class ebook : public libraryItem {
	private:
		QString author;
		QString genre;
		QString format; // pdf, doc, epub, ...
		float fileSize; // in MB
		unsigned int pages;
	public:
		// constructor
		ebook(QString, QString = "undefined", QString = "undefined", QString = "undefined", unsigned int = 1900, unsigned int = 0,
				QString = "undefined", QString = "undefined", QString = "undefined", float = 0, unsigned int = 0);

		// implementation of pure virtual methods inherited by libraryItem
		virtual ebook* clone() const;

		// getter methods
		QString getAuthor() const;
		QString getGenre() const;
		QString getFormat() const;
		float getFileSize() const;
		unsigned int numberOfPages() const;

		// setter methods
		void setAuthor(QString);
		void setGenre(QString);
		void setFormat(QString);
		void setFileSize(float);
		void setPages(unsigned int);

		// operators
		bool operator==(const ebook&) const;
};

// external operators
ostream& operator<<(ostream&, const ebook&);

#endif // EBOOK_H