#ifndef EDITITEMWINDOW_H
#define EDITITEMWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include "libraryitem.h"
#include "book.h"
#include "ebook.h"

namespace Ui {
    class EditItemWindow;
}

class EditItemWindow : public QDialog {
    Q_OBJECT

    private:
        Ui::EditItemWindow *ui;

		// window widgets - to extend with new data types

		// basic info
		QRadioButton *radioButtonBook;
		QRadioButton *radioButtonEBook;

		QLineEdit *isbnTextField;
		QLineEdit *titleTextField;
		QLineEdit *publisherTextField;
		QLineEdit *coverImageTextField;
		QComboBox *yearPublishedField;

		QRadioButton *ratingOneStarField;
		QRadioButton *ratingTwoStarField;
		QRadioButton *ratingThreeStarField;
		QRadioButton *ratingFourStarField;
		QRadioButton *ratingFiveStarField;

		// book info
		QLineEdit *bookAuthorTextField;
		QComboBox *bookGenreField;
		QSpinBox *bookPagesField;
		QComboBox *bookReleaseField;

		// e-book info
		QLineEdit *eBookAuthorTextField;
		QComboBox *eBookGenreField;
		QComboBox *fileFormatField;
		QSpinBox *fileSizeField;
		QSpinBox *eBookPagesField;

		// item identification property
		QString itemType;

        void setUpEditForm(LibraryItem*);
		// handling of generica item data
		QGroupBox *addBasicInfo(LibraryItem*);

		// handling of specific library items data (add a function for every new item type)
		QGroupBox *addBookInfo(Book*);
		QGroupBox *addEBookInfo(eBook*);

		// utility methods
		unsigned int getCurrentRating() const;
		unsigned int getCurrentRelease() const;

		bool emptyFields() const;

    public:
        explicit EditItemWindow(LibraryItem *item, QWidget *parent = 0);
        ~EditItemWindow();

	signals:
		void itemEdited(LibraryItem*);

	private slots:
		void editDataSubmitted();

};

#endif // EDITITEMWINDOW_H
