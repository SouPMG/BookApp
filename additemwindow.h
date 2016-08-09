#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>
#include <QtCore>
#include <QtWidgets>

namespace Ui {
	class AddItemWindow;
}

class AddItemWindow : public QDialog {
		Q_OBJECT

	private:
		// class widgets to show only when selected
		QGroupBox *bookFormGroup;
		QGroupBox *eBookFormGroup;

		Ui::AddItemWindow *ui;
		void setupAddItemForm();

	public:
		explicit AddItemWindow(QWidget *parent = 0);
		~AddItemWindow();

	private slots:
		void newItemSubmitted();
		void showBookForm();
		void showEBookForm();

};

#endif // ADDITEMWINDOW_H
