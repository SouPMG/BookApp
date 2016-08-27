#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QString>

class LibraryItem {
	private:
		QString isbn;
		QString title;
		QString publisher;
		QString coverImage; // path + file name for the cover image (.jpg or .png)
		unsigned int yearPublished;
		unsigned int rating; // rating: number of stars from 1 to 5
		int timeRead; // time reading actual item in seconds
	public:
		// constructor
		LibraryItem(QString, QString = "undefined", QString = "undefined", QString = "undefined", unsigned int = 1900, unsigned int = 0, int = 0);

		// pure virtual methods
		virtual LibraryItem* clone() const = 0;

        // getter methods
		QString getIsbn() const;
		QString getTitle() const;
		QString getPublisher() const;
		QString getCoverImage() const;
		unsigned int getYearPublished() const;
		unsigned int getRating() const;
        float getTimeRead() const;

        // setter methods
		void setIsbn(QString);
		void setTitle(QString);
		void setPublisher(QString);
		void setCoverImage(QString);
		void setPublicationYear(unsigned int);
		void rate(unsigned int);
		void setTimeRead(int);

        // other methods
		void addTimeRead(int);
		void resetTimer();

		// operators
		bool operator==(const LibraryItem&) const;
};

#endif // LIBRARYITEM_H
