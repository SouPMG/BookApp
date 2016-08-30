#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "library.h"
#include "libraryitem.h"
#include "book.h"
#include "ebook.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
		Q_OBJECT

	private:
		// ui manager
		Ui::MainWindow *ui;

		// private fields
		Library library;
		QStringListModel *model;

		// private utility methods
		void loadLibrary();
		void connectActions() const;
		void refreshLibraryView() const;

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

    signals:
        void editButtonClicked(LibraryItem*);

	private slots:
		// actions
		void addItemActionTriggered();
		void removeItemActionTriggered();
		void aboutActionTriggered();

		// library handling
		void addNewLibraryItem(LibraryItem*);
		void showDetails(QModelIndex);

        // edit item slots
		void emitEditButtonClicked();
        void editItemTriggered(LibraryItem*);
		void editLibraryItem(LibraryItem*);

		// start reading slots
		void startReading();
		void updateTimeRead(int);
		void resetTimeRead();

		// save library slot
		void saveLibrary();
};

#endif // MAINWINDOW_H
