#include "ebook.h"

// can be instantiated specifying only the isbn, everything else has a default value
eBook::eBook ( QString isbn, QString title, QString publisher, QString cover, unsigned int year, unsigned int rating,
			   QString author, QString genre, QString format, float size, unsigned int pages )
	: LibraryItem(isbn, title, publisher, cover, year, rating), author(author), genre(genre), format(format), fileSize(size), pages(pages) {}

// virtual clone method overloaded
eBook* eBook::clone() const {
	return new eBook ( *this );
}

// getter methods
QString eBook::getAuthor() const {
	return author;
}

QString eBook::getGenre() const {
	return genre;
}

QString eBook::getFormat() const {
	return format;
}

float eBook::getFileSize() const {
	return fileSize;
}

unsigned int eBook::numberOfPages() const {
	return pages;
}

// setter methods
void eBook::setAuthor ( QString newAuthor ) {
	author = newAuthor;
}

void eBook::setGenre ( QString newGenre ) {
	genre = newGenre;
}

void eBook::setFormat ( QString newFormat ) {
	format = newFormat;
}

void eBook::setFileSize ( float newFileSize ) {
	fileSize = newFileSize;
}

void eBook::setPages ( unsigned int numberOfPages ) {
	pages = numberOfPages;
}

// operators
bool eBook::operator==(const eBook& b) const {
	return getIsbn() == b.getIsbn();
}

ostream& operator<<(ostream& os, const eBook& b) {
	return os << "ISBN: " << b.getIsbn() << " Title: " << b.getTitle();
}
