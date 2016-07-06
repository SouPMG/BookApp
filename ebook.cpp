#include "ebook.h"

// can be instantiated specifying only the isbn, everything else has a default value
ebook::ebook ( QString isbn, QString title, QString publisher, QString cover, unsigned int year, unsigned int rating,
			   QString author, QString genre, QString format, float size, unsigned int pages )
	: libraryItem(isbn, title, publisher, cover, year, rating), author(author), genre(genre), format(format), fileSize(size), pages(pages) {}

// virtual clone method overloaded
ebook* ebook::clone() const {
	return new ebook ( *this );
}

// getter methods
QString ebook::getAuthor() const {
	return author;
}

QString ebook::getGenre() const {
	return genre;
}

QString ebook::getFormat() const {
	return format;
}

float ebook::getFileSize() const {
	return fileSize;
}

unsigned int ebook::numberOfPages() const {
	return pages;
}

// setter methods
void ebook::setAuthor ( QString newAuthor ) {
	author = newAuthor;
}

void ebook::setGenre ( QString newGenre ) {
	genre = newGenre;
}

void ebook::setFormat ( QString newFormat ) {
	format = newFormat;
}

void ebook::setFileSize ( float newFileSize ) {
	fileSize = newFileSize;
}

void ebook::setPages ( unsigned int numberOfPages ) {
	pages = numberOfPages;
}

// operators
bool ebook::operator==(const ebook& b) const {
	return getIsbn() == b.getIsbn();
}

ostream& operator<<(ostream& os, const ebook& b) {
	return os << "ISBN: " << b.getIsbn() << " Title: " << b.getTitle();
}
