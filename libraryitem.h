#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QString>

class libraryItem {
	private:
		QString isbn;
		QString title;
		QString publisher;
		QString coverImage; // path + file name for the cover image (.jpg or .png)
		unsigned int yearPublished;
		unsigned int rating; // rating: number of stars from 1 to 5
	public:
		// constructor
		libraryItem(QString, QString = "undefined", QString = "undefined", QString = "undefined", unsigned int = 1900, unsigned int = 0);

		// pure virtual methods
		virtual libraryItem* clone() const = 0;

		// setter methods
		QString getIsbn() const;
		QString getTitle() const;
		QString getPublisher() const;
		QString getCoverImage() const;
		unsigned int getYearPublished() const;
		unsigned int getRating() const;

		// getter methods
		void setTitle(QString);
		void setPublisher(QString);
		void setCoverImage(QString);
		void setPublicationYear(unsigned int);
		void rate(unsigned int);
};

#endif // LIBRARYITEM_H
