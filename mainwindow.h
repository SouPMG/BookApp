#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "book.h"
#include "library.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
		Q_OBJECT

	private:
		Ui::MainWindow *ui;
		QStringListModel *model;

		void connectActions() const;

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		// actions
		void addItemActionTriggered();
		void removeItemActionTriggered();
		void aboutActionTriggered();
};

#endif // MAINWINDOW_H
