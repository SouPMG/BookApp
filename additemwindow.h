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

		QLabel *isbnLabel;
		QLineEdit *isbnTextField;

		QLabel *titleLabel;
		QLineEdit *titleTextField;

		QLabel *publisherLabel;
		QLineEdit *publisherTextField;

		QLabel *coverImageLabel;
		QLineEdit *coverImageTextField;

		QLabel *yearPublishedLabel;
		QComboBox *yearPublishedField;

		QLabel *ratingLabel;
		QRadioButton *ratingOneStarField;
		QRadioButton *ratingTwoStarField;
		QRadioButton *ratingThreeStarField;
		QRadioButton *ratingFourStarField;
		QRadioButton *ratingFiveStarField;

		// book info
		QLabel *bookAuthorLabel;
		QLineEdit *bookAuthorTextField;

		QLabel *bookGenreLabel;
		QComboBox *bookGenreField;

		QLabel *bookPagesLabel;
		QSpinBox *bookPagesField;

		QLabel *bookReleaseLabel;
		QComboBox *bookReleaseField;

		// e-book info
		QLabel *eBookAuthorLabel;
		QLineEdit *eBookAuthorTextField;

		QLabel *eBookGenreLabel;
		QComboBox *eBookGenreField;

		QLabel *fileFormatLabel;
		QComboBox *fileFormatField;

		QLabel *fileSizeLabel;
		QSpinBox *fileSizeField;

		QLabel *eBookPagesLabel;
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
