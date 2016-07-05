#include "libraryitem.h"

// Every parameter has a default value except the first one (isbn). For details check libraryitem.h
libraryItem::libraryItem(QString isbn, QString title, QString publisher, QString cover, unsigned int year, unsigned int rating)
	: isbn(isbn), title(title), publisher(publisher), coverImage(cover), yearPublished(year), rating(rating) {}

/* getter methods */

QString libraryItem::getIsbn() const {
	return isbn;
}

QString libraryItem::getTitle() const {
	return title;
}

QString libraryItem::getPublisher() const {
	return publisher;
}

QString libraryItem::getCoverImage() const {
	return coverImage;
}

unsigned int libraryItem::getYearPublished() const {
	return yearPublished;
}

unsigned int libraryItem::getRating() const {
	return rating;
}

/* setter methods */

void libraryItem::setTitle(QString newTitle) {
	title = newTitle;
}

void libraryItem::setPublisher(QString newPublisher) {
	publisher = newPublisher;
}

void libraryItem::setCoverImage(QString newCoverImage) {
	coverImage = newCoverImage;
}

void libraryItem::setPublicationYear(unsigned int newYear) {
	yearPublished = newYear;
}

void libraryItem::rate(unsigned int newRating) {
	rating = newRating;
}
