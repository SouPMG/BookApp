#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemwindow.h"
#include "edititemwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow configuration
	resize(800, 600);
    ui->mainContent->setCurrentIndex(0);

	// setup mainwindow welcome text
	ui->mainTextLabel->setText("<h1>Welcome to BookApp!</h1>"
							   "<p>From here you can add or remove books from your library or edit them from the list.</p>");
	ui->mainTextLabel->adjustSize();

	// setup library text
	ui->libraryLabel->setText("Your library:");

	connectActions();
    connect(ui->libraryListView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));

    // connect edit button clicked signal to mainwindow slot that will re-emit custom clicked signal with proper parameters
    connect(ui->editItemButton, SIGNAL(clicked(bool)), this, SLOT(emitEditButtonClicked(bool)));
    connect(this, SIGNAL(editButtonClicked(LibraryItem*)), this, SLOT(editItemTriggered(LibraryItem*)));

	// setup library variables
	library = Library();

	/**/Book *tempBook = new Book("12345", "Trial Book", "Myself", "/etc/opt/fuck", 1993, 5);
	/**/library.addItem(tempBook);

	model = new QStringListModel(this);

	/**/QStringList tempList;
	/**/tempList << tempBook->getTitle();
	/**/model->setStringList(tempList);

	ui->libraryListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->libraryListView->setSelectionMode(QAbstractItemView::SingleSelection);
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

void MainWindow::refreshLibraryView() const {
	QStringList list;
	for (Library::LibraryIterator it = library.begin(); it != library.end(); it++) {
		list << library[it]->getTitle();
	}
	model->setStringList(list);
}

// slots
void MainWindow::aboutActionTriggered() {
	QMessageBox::information(this, "About", "BookApp® 2016 <br/> Mattia Giacobbe");
}

void MainWindow::addItemActionTriggered() {
	AddItemWindow *addNewItem = new AddItemWindow(this);
	connect(addNewItem, SIGNAL(itemAdded(LibraryItem*)), this, SLOT(addNewLibraryItem(LibraryItem*)));
	addNewItem->show();
}

void MainWindow::removeItemActionTriggered() {
	int position = ui->libraryListView->currentIndex().row();
	QMessageBox::StandardButton reply;

	if (position >= 0) {
		reply = QMessageBox::question(this, "Delete item", "Are you sure you want to delete this item?", QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			Library::LibraryIterator it = library.begin();
			for (int i; i < position; i++) {
				it++;
			}

			// remove item from container
			library.removeItem(library[it]);

			// remove item from model
			model->removeRows(position, 1);

			// switch to welcome text on stacked widget
			ui->mainContent->setCurrentIndex(0);
		}
	}
}

void MainWindow::addNewLibraryItem(LibraryItem *newItem) {
	// here we have a new object that needs to be added to the library
	// firstly we identify what type of object we have
	Book *newBook = dynamic_cast<Book*>(newItem);
	if (newBook) {
		// we have a book
		library.addItem(newBook);
		refreshLibraryView();
		return;
	}
	eBook *newEBook = dynamic_cast<eBook*>(newItem);
	if (newEBook) {
		// we have an e-book
		library.addItem(newEBook);
		refreshLibraryView();
		return;
	}
}

void MainWindow::showDetails(QModelIndex index) {
	int position = index.row();
    LibraryItem *selectedItemGeneric = library.at(position);

    ui->isbnData->setText(selectedItemGeneric->getIsbn());
    ui->titleData->setText(selectedItemGeneric->getTitle());
    ui->publisherData->setText(selectedItemGeneric->getPublisher());
    ui->yearData->setText(QString::number(selectedItemGeneric->getYearPublished()));
    ui->ratingData->setText(QString::number(selectedItemGeneric->getRating()));

	// again, let's see what kind of item we have
	Book *selectedItemBook = dynamic_cast<Book*>(selectedItemGeneric);
	if (selectedItemBook) {
        // we have a book so we add additional book info
        ui->bookAuthorData->setText(selectedItemBook->getAuthor());
        ui->bookGenreData->setText(selectedItemBook->getGenre());
        ui->bookPagesData->setText(QString::number(selectedItemBook->numberOfPages()));
        ui->bookReleaseData->setText(QString::number(selectedItemBook->getReleaseNumber()));

        ui->eBookInfoGroup->hide();
        ui->bookInfoGroup->show();
	}
	eBook *selectedItemEBook = dynamic_cast<eBook*>(selectedItemGeneric);
	if (selectedItemEBook) {
        // we have an e-book so we add additional e-book info
        ui->eBookAuthorData->setText(selectedItemEBook->getAuthor());
        ui->eBookGenreData->setText(selectedItemEBook->getGenre());
        ui->eBookFormatData->setText(selectedItemEBook->getFormat());
        ui->eBookSizeData->setText(QString::number(selectedItemEBook->getFileSize()));
        ui->eBookPagesData->setText(QString::number(selectedItemEBook->numberOfPages()));

        ui->bookInfoGroup->hide();
        ui->eBookInfoGroup->show();
	}

	// switch to stack widget item data view side
	ui->mainContent->setCurrentIndex(1);
}

// edit button slots
void MainWindow::emitEditButtonClicked(bool) {
    QModelIndex index = ui->libraryListView->currentIndex();
    int position = index.row();
    LibraryItem *selectedItem = library.at(position);

    emit editButtonClicked(selectedItem);
}

void MainWindow::editItemTriggered(LibraryItem *itemToEdit) {
    EditItemWindow *editWindow = new EditItemWindow(itemToEdit);
	connect(editWindow, SIGNAL(itemEdited(LibraryItem*)), this, SLOT(editLibraryItem(LibraryItem*)));
    editWindow->show();
}

void MainWindow::editLibraryItem(LibraryItem *editedData) {
	// returning from edit window we still have the item edited selected
	int position = ui->libraryListView->currentIndex().row();
	library.editItemAt(editedData, position);
	refreshLibraryView();
	emit ui->libraryListView->clicked(ui->libraryListView->currentIndex());
}
