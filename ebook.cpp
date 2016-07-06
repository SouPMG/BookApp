#include "ebook.h"

// can be instantiated specifying only the isbn, everything else has a default value
ebook::ebook ( string isbn, string title, string publisher, string cover, unsigned int year, unsigned int rating,
			   string author, string genre, string format, float size, unsigned int pages )
	: libraryItem(isbn, title, publisher, cover, year, rating), author(author), genre(genre), format(format), size(size), pages(pages) {}

// virtual clone method overloaded
ebook* ebook::clone() const {
	return new ebook ( *this );
}

// getter methods
string ebook::getAuthor() const {
	return author;
}

string ebook::getGenre() const {
	return genre;
}

string ebook::getFormat() const {
	return format;
}

float ebook::getFileSize() const {
	return fileSize;
}

unsigned int ebook::numberOfPages() const {
	return pages;
}

// setter methods
void ebook::setAuthor ( string newAuthor ) {
	author = newAuthor;
}

void ebook::setGenre ( string newGenre ) {
	genre = newGenre;
}

void ebook::setFormat ( string newFormat ) {
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
	return this->isbn == b.isbn;
}

ostream& operator<<(ostream& os, const ebook& b) {
	return os << "ISBN: " << b.getIsbn() << " Title: " << b.getTitle();
}
