#include "mainwindow.h"
#include "additemwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow welcome text
	ui->mainTextLabel->setText("<h1>Welcome to BookApp!</h1> <p>From here you can add or remove books from your library or edit them from the list.</p>");
	ui->mainTextLabel->setFixedHeight(55);

	// setup library text
	ui->libraryLabel->setText("Your library:");

	connectActions();

	// setup library //
	model = new QStringListModel(this);

	library *userLibrary = new library();
	book *theBook = new book("123456");
	userLibrary->addItem(theBook);

	QStringList list;
	list << userLibrary->extract()->getTitle();

	model->setStringList(list);

	ui->libraryListView->setModel(model);
	// /setup library //
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::connectActions() const {
	connect(ui->addItemAction, SIGNAL(triggered(bool)), this, SLOT(addItemActionTriggered(bool)));
	connect(ui->removeItemAction, SIGNAL(triggered(bool)), this, SLOT(removeItemActionTriggered(bool)));
	connect(ui->aboutAction, SIGNAL(triggered(bool)), this, SLOT(aboutActionTriggered(bool)));
}

void MainWindow::addItemActionTriggered(bool) {
	AddItemWindow *addNewItem = new AddItemWindow(this);
	addNewItem->show();
}

void MainWindow::removeItemActionTriggered(bool) {
	model->removeRows(ui->libraryListView->currentIndex().row(), 1);
}

void MainWindow::aboutActionTriggered(bool) {
	QMessageBox::information(this, "About", "BookApp® 2016 <br/> Mattia Giacobbe");
}
