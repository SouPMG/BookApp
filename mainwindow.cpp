#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow welcome text
	ui->mainTextLabel->setText("<h1>Welcome to BookApp!</h1> <p>From here you can add or remove books from your library or edit them from the list.</p>");
	ui->mainTextLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

	// setup library text
	ui->libraryLabel->setText("Your library:");

	// setup library
	model = new QStringListModel(this);

	library *userLibrary = new library();
	book *theBook = new book("123456");
	userLibrary->addItem(theBook);

	QStringList list;
	list << userLibrary->extract()->getTitle();

	model->setStringList(list);

	ui->libraryListView->setModel(model);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_actionAddBook_triggered() {
	QMessageBox::information(this, "Title", "Opening file");
}

void MainWindow::on_actionRemoveBook_triggered() {
	model->removeRows(ui->libraryListView->currentIndex().row(), 1);
}

void MainWindow::on_actionAboutBookApp_triggered() {
	QMessageBox::information(this, "About", "BookApp® 2016 <br/> Mattia Giacobbe");
}
