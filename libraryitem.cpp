#include "libraryitem.h"

// Every parameter has a default value except the first one (isbn). For details check libraryitem.h
LibraryItem::LibraryItem(QString isbn, QString title, QString publisher, QString cover, unsigned int year, unsigned int rating, int time)
    : isbn(isbn), title(title), publisher(publisher), coverImage(cover), yearPublished(year), rating(rating), timeRead(time) {}

// getter methods
QString LibraryItem::getIsbn() const {
	return isbn;
}

QString LibraryItem::getTitle() const {
	return title;
}

QString LibraryItem::getPublisher() const {
	return publisher;
}

QString LibraryItem::getCoverImage() const {
	return coverImage;
}

unsigned int LibraryItem::getYearPublished() const {
	return yearPublished;
}

unsigned int LibraryItem::getRating() const {
	return rating;
}

float LibraryItem::getTimeRead() const {
    return timeRead;
}

// setter methods
void LibraryItem::setIsbn(QString newIsbn) {
	isbn = newIsbn;
}

void LibraryItem::setTitle(QString newTitle) {
	title = newTitle;
}

void LibraryItem::setPublisher(QString newPublisher) {
	publisher = newPublisher;
}

void LibraryItem::setCoverImage(QString newCoverImage) {
	coverImage = newCoverImage;
}

void LibraryItem::setPublicationYear(unsigned int newYear) {
	yearPublished = newYear;
}

void LibraryItem::rate(unsigned int newRating) {
	rating = newRating;
}

void LibraryItem::setTimeRead(int newTimeRead) {
    timeRead = newTimeRead;
}

// other methods
void LibraryItem::addTimeRead(int timeToAdd) {
    timeRead += timeToAdd;
}

// operators
bool LibraryItem::operator==(const LibraryItem& item) const {
	return getIsbn() == item.getIsbn();
}
