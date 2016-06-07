#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>

using std::string;

class libraryItem {
	private:
		string isbn;
		string title;
		string publisher;
		string coverImage; // path + file name for the cover image (.jpg or .png)
		unsigned int yearPublished;
		unsigned int rating; // rating: number of stars from 1 to 5
	public:
		// constructor
		libraryItem ( string, string = "undefined", string = "undefined", string = "undefined", unsigned int = 1900, unsigned int = 0 );

		// pure virtual methods
		virtual libraryItem* clone() const = 0;


		// setter methods
		string getIsbn() const;
		string getTitle() const;
		string getPublisher() const;
		string getCoverImage() const;
		unsigned int getYearPublished() const;
		unsigned int getRating() const;

		// getter methods
		void setTitle ( string );
		void setPublisher ( string );
		void setCoverImage ( string );
		void setPublicationYear ( unsigned int );
		void rate ( unsigned int );
};

#endif // LIBRARYITEM_H
