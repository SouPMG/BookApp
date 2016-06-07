#include "book.h"

// can be instantiated specifying only the isbn, everything else has a default value
book::book ( string isbn, string title, string publisher, string cover, unsigned int year, unsigned int rating,
			 string author, string genre, unsigned int pages, unsigned int release )
	: libraryItem(isbn, title, publisher, cover, year, rating), author(author), genre(genre), pages(pages), release(release) {}

/* getter methods */

book* book::clone() const {
	return new book ( *this );
}

string book::getAuthor() const {
	return author;
}

string book::getGenre() const {
	return genre;
}

unsigned int book::numberOfPages() const {
	return pages;
}

unsigned int book::getReleaseNumber() const {
	return release;
}

/* setter methods */

void book::setAuthor ( string newAuthor ) {
	author = newAuthor;
}

void book::setGenre ( string newGenre ) {
	genre = newGenre;
}

void book::setPages ( unsigned int numberOfPages ) {
	pages = numberOfPages;
}

void book::setReleaseNumber ( unsigned int releaseNumber ) {
	release = releaseNumber;
}
