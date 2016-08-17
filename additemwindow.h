#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>
#include "libraryitem.h"
#include "book.h"
#include "ebook.h"

namespace Ui {
	class AddItemWindow;
}

class AddItemWindow : public QDialog {
		Q_OBJECT

	private:
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

		// class widgets to show only when selected
		QGroupBox *bookFormGroup;
		QGroupBox *eBookFormGroup;

		Ui::AddItemWindow *ui;
		void setupAddItemForm();
		unsigned int getCurrentRating() const;
		unsigned int getCurrentRelease() const;

	public:
		explicit AddItemWindow(QWidget *parent = 0);
		~AddItemWindow();

	signals:
		void itemAdded(LibraryItem*);

	private slots:
		void newItemSubmitted();
		void showBookForm();
		void showEBookForm();

};

#endif // ADDITEMWINDOW_H
