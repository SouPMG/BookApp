#include "book.h"

// can be instantiated specifying only the isbn, everything else has a default value
Book::Book(QString isbn, QString title, QString publisher, QString cover, unsigned int year, unsigned int rating, float time,
			 QString author, QString genre, unsigned int pages, unsigned int release)
    : LibraryItem(isbn, title, publisher, cover, year, rating, time), author(author), genre(genre), pages(pages), release(release) {}

// virtual clone method overloaded
Book* Book::clone() const {
	return new Book ( *this );
}

// getter methods
QString Book::getAuthor() const {
	return author;
}

QString Book::getGenre() const {
	return genre;
}

unsigned int Book::numberOfPages() const {
	return pages;
}

unsigned int Book::getReleaseNumber() const {
	return release;
}

// setter methods
void Book::setAuthor(QString newAuthor) {
	author = newAuthor;
}

void Book::setGenre(QString newGenre) {
	genre = newGenre;
}

void Book::setPages(unsigned int numberOfPages) {
	pages = numberOfPages;
}

void Book::setReleaseNumber(unsigned int releaseNumber) {
	release = releaseNumber;
}

// operators
bool Book::operator==(const Book& b) const {
	return getIsbn() == b.getIsbn();
}

ostream& operator<<(ostream& os, const Book& b) {
	return os << "ISBN: " << b.getIsbn() << " Title: " << b.getTitle();
}
