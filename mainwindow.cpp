#include "mainwindow.h"
#include "additemwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow configuration
	resize(800, 600);

	// setup mainwindow welcome text
	ui->mainTextLabel->setText
			("<h1>Welcome to BookApp!</h1> <p>From here you can add or remove books from your library or edit them from the list.</p>");
	ui->mainTextLabel->setFixedHeight(55);

	// setup library text
	ui->libraryLabel->setText("Your library:");

	connectActions();

	// setup library
	model = new QStringListModel(this);
	library = Library();
	ui->libraryListView->setModel(model);
}

MainWindow::~MainWindow() {
	delete ui;
}

// utility methods
void MainWindow::connectActions() const {
	connect(ui->addItemAction,    SIGNAL(triggered()), this, SLOT(addItemActionTriggered()));
	connect(ui->removeItemAction, SIGNAL(triggered()), this, SLOT(removeItemActionTriggered()));
	connect(ui->aboutAction,      SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));
}

void MainWindow::refreshLibraryModel() const {
	QStringList list;
	for (Library::LibraryIterator it = library.begin(); it != library.end(); it++) {
		list << library[it]->getTitle();
	}
	model->setStringList(list);
}

// slots
void MainWindow::addItemActionTriggered() {
	AddItemWindow *addNewItem = new AddItemWindow(this);
	connect(addNewItem, SIGNAL(itemAdded(LibraryItem*)), this, SLOT(addNewLibraryItem(LibraryItem*)));
	addNewItem->show();
}

void MainWindow::removeItemActionTriggered() {
	int position = ui->libraryListView->currentIndex().row();
	Library::LibraryIterator it = library.begin();

	for (int i; i < position; i++) {
		it++;
	}

	library.removeItem(library[it]);

	// remove item from model
	model->removeRows(position, 1);
}

void MainWindow::aboutActionTriggered() {
	QMessageBox::information(this, "About", "BookApp® 2016 <br/> Mattia Giacobbe");
}

void MainWindow::addNewLibraryItem(LibraryItem *newItem) {
	// here we have a new object that needs to be added to the library
	// firstly we identify what type of object we have
	Book *newBook = dynamic_cast<Book*>(newItem);
	if (newBook) {
		// we have a book
		library.addItem(newBook);
		refreshLibraryModel();
		return;
	}
	eBook *newEBook = dynamic_cast<eBook*>(newItem);
	if (newEBook) {
		// we have an e-book
		library.addItem(newEBook);
		refreshLibraryModel();
		return;
	}
}
