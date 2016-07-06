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

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();
};

#endif // MAINWINDOW_H
