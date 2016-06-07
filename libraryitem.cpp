#include "libraryitem.h"

// Every parameter has a default value except the first one (isbn). For details check libraryitem.h
libraryItem::libraryItem ( string isbn, string title, string publisher, string cover, unsigned int year, unsigned int rating )
	: isbn(isbn), title(title), publisher(publisher), coverImage(cover), yearPublished(year), rating(rating) {}

/* getter methods */

string libraryItem::getIsbn() const {
	return isbn;
}

string libraryItem::getTitle() const {
	return title;
}

string libraryItem::getPublisher() const {
	return publisher;
}

string libraryItem::getCoverImage() const {
	return coverImage;
}

unsigned int libraryItem::getYearPublished() const {
	return yearPublished;
}

unsigned int libraryItem::getRating() const {
	return rating;
}

/* setter methods */

void libraryItem::setTitle ( string newTitle ) {
	title = newTitle;
}

void libraryItem::setPublisher ( string newPublisher ) {
	publisher = newPublisher;
}

void libraryItem::setCoverImage ( string newCoverImage ) {
	coverImage = newCoverImage;
}

void libraryItem::setPublicationYear ( unsigned int newYear ) {
	yearPublished = newYear;
}

void libraryItem::rate ( unsigned int newRating ) {
	rating = newRating;
}
