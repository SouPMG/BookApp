#include "mainwindow.h"
#include "additemwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow configuration
	resize(800, 600);

	// setup mainwindow welcome text
	ui->mainTextLabel->setText("<h1>Welcome to BookApp!</h1>"
							   "<p>From here you can add or remove books from your library or edit them from the list.</p>");
	ui->mainTextLabel->adjustSize();

	// setup library text
	ui->libraryLabel->setText("Your library:");

	connectActions();
	connect(ui->libraryListView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));

	// setup library variables
	library = Library();

	/**/Book *tempBook = new Book("12345", "Trial Book", "Myself", "/etc/opt/fuck", 1993, 5);
	/**/library.addItem(tempBook);

	model = new QStringListModel(this);

	/**/QStringList tempList;
	/**/tempList << tempBook->getTitle();
	/**/model->setStringList(tempList);

	ui->libraryListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
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
		QLineEdit *bookAuthorData = new QLineEdit(selectedItemBook->getAuthor());
		QLineEdit *bookGenreData = new QLineEdit(selectedItemBook->getGenre());
		QLineEdit *bookPagesData = new QLineEdit(QString::number(selectedItemBook->numberOfPages()));
		QLineEdit *bookReleaseData = new QLineEdit(QString::number(selectedItemBook->getReleaseNumber()));

		QLabel *bookInfoLabel = new QLabel("Book specific informations");
		ui->dataFormLayout->addWidget(bookInfoLabel);

		ui->dataFormLayout->addRow("Author:", bookAuthorData);
		ui->dataFormLayout->addRow("Genre:", bookGenreData);
		ui->dataFormLayout->addRow("Pages:", bookPagesData);
		ui->dataFormLayout->addRow("Release:", bookReleaseData);
	}
	eBook *selectedItemEBook = dynamic_cast<eBook*>(selectedItemGeneric);
	if (selectedItemEBook) {
		// we have an e-book so we add additional e-book info
		QLineEdit *eBookAuthorData = new QLineEdit(selectedItemEBook->getAuthor());
		QLineEdit *eBookGenreData = new QLineEdit(selectedItemEBook->getGenre());
		QLineEdit *eBookFormatData = new QLineEdit(selectedItemEBook->getFormat());
		QLineEdit *eBookSizeData = new QLineEdit(QString::number(selectedItemEBook->getFileSize()));
		QLineEdit *eBookPagesData = new QLineEdit(QString::number(selectedItemEBook->numberOfPages()));

		QLabel *eBookInfoLabel = new QLabel("e-Book specific informations");
		ui->dataFormLayout->addWidget(eBookInfoLabel);

		ui->dataFormLayout->addRow("Author:", eBookAuthorData);
		ui->dataFormLayout->addRow("Genre:", eBookGenreData);
		ui->dataFormLayout->addRow("File format:", eBookFormatData);
		ui->dataFormLayout->addRow("File size (MB):", eBookSizeData);
		ui->dataFormLayout->addRow("Pages:", eBookPagesData);
	}

	// switch to stack widget item data view side
	ui->mainContent->setCurrentIndex(1);
}
