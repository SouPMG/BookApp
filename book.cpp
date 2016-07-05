#include "book.h"

// can be instantiated specifying only the isbn, everything else has a default value
book::book(QString isbn, QString title, QString publisher, QString cover, unsigned int year, unsigned int rating,
			 QString author, QString genre, unsigned int pages, unsigned int release)
	: libraryItem(isbn, title, publisher, cover, year, rating), author(author), genre(genre), pages(pages), release(release) {}

/* getter methods */

book* book::clone() const {
	return new book ( *this );
}

QString book::getAuthor() const {
	return author;
}

QString book::getGenre() const {
	return genre;
}

unsigned int book::numberOfPages() const {
	return pages;
}

unsigned int book::getReleaseNumber() const {
	return release;
}

/* setter methods */

void book::setAuthor(QString newAuthor) {
	author = newAuthor;
}

void book::setGenre(QString newGenre) {
	genre = newGenre;
}

void book::setPages(unsigned int numberOfPages) {
	pages = numberOfPages;
}

void book::setReleaseNumber(unsigned int releaseNumber) {
	release = releaseNumber;
}

/* Operators */

bool book::operator==(const book& b) const {
	return this->isbn == b.isbn;
}

ostream& operator<<(ostream& os, const book& b) {
	return os << "ISBN: " << b.getIsbn() << " Title: " << b.getTitle();
}
