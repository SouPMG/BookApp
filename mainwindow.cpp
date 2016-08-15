#include "mainwindow.h"
#include "additemwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow configuration
	resize(800, 600);

	// setup mainwindow welcome text
	ui->mainTextLabel->setText("<h1>Welcome to BookApp!</h1> <p>From here you can add or remove books from your library or edit them from the list.</p>");
	ui->mainTextLabel->setFixedHeight(55);

	// setup library text
	ui->libraryLabel->setText("Your library:");

	connectActions();

	// setup test library //
	model = new QStringListModel(this);

	Library *userLibrary = new Library();
	Book *theBook = new Book("123456");
	userLibrary->addItem(theBook);

	QStringList list;
	list << userLibrary->extract()->getTitle();

	model->setStringList(list);

	ui->libraryListView->setModel(model);
	// /setup test library //
}

MainWindow::~MainWindow() {
	delete ui;
}

// actions
void MainWindow::addItemActionTriggered() {
	AddItemWindow *addNewItem = new AddItemWindow(this);
	addNewItem->show();
}

void MainWindow::removeItemActionTriggered() {
	model->removeRows(ui->libraryListView->currentIndex().row(), 1);
}

void MainWindow::aboutActionTriggered() {
	QMessageBox::information(this, "About", "BookApp® 2016 <br/> Mattia Giacobbe");
}

void MainWindow::connectActions() const {
	connect(ui->addItemAction,    SIGNAL(triggered()), this, SLOT(addItemActionTriggered()));
	connect(ui->removeItemAction, SIGNAL(triggered()), this, SLOT(removeItemActionTriggered()));
	connect(ui->aboutAction,      SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));
}
