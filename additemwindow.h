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
		Ui::AddItemWindow *ui;
		QVBoxLayout *mainLayout;
		void setupAddItemForm();

	public:
		explicit AddItemWindow(QWidget *parent = 0);
		~AddItemWindow();

	private slots:
		void newItemSubmitted();
		void addBookForm();
		void addEBookForm();

};

#endif // ADDITEMWINDOW_H
