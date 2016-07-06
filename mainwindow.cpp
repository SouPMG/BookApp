#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	library<book> *userLibrary = new library<book>();
	book *theBook = new book("123456");
	userLibrary->addItem(*theBook);

	QStringList list;
	list << userLibrary->extract().getIsbn();

	model->setStringList(list);

	ui->libraryListView->setModel(model);
}

MainWindow::~MainWindow() {
	delete ui;
}
