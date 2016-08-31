#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "additemwindow.h"
#include "edititemwindow.h"
#include "readingtimerwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

	// setup mainwindow configuration
	setWindowTitle("BookApp");
	ui->mainToolBar->setMovable(false);
	resize(800, 650);

	ui->mainContent->setCurrentIndex(0);

	// connect menu actions
	connectActions();

	// connect item display functionalities
	connect(ui->libraryListView, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetails(QModelIndex)));
	connect(ui->libraryListView, SIGNAL(activated(QModelIndex)), this, SLOT(showDetails(QModelIndex)));

	// connect edit button clicked signal to mainwindow slot that will re-emit custom clicked signal with proper parameters and trigger the edit
	connect(ui->editItemButton, SIGNAL(clicked()), this, SLOT(emitEditButtonClicked()));
    connect(this, SIGNAL(editButtonClicked(LibraryItem*)), this, SLOT(editItemTriggered(LibraryItem*)));

	// start reading!
	connect(ui->startReadingButton, SIGNAL(clicked()), this, SLOT(startReading()));

	// load items from local xml database if there are any
	loadLibrary();
	model = new QStringListModel(this);
	refreshLibraryView();

	ui->libraryListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->libraryListView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->libraryListView->setModel(model);
}

MainWindow::~MainWindow() {
	delete ui;
}

// utility methods
void MainWindow::connectActions() const {
	connect(ui->addItemAction,     SIGNAL(triggered()), this, SLOT(addItemActionTriggered()));
	connect(ui->removeItemAction,  SIGNAL(triggered()), this, SLOT(removeItemActionTriggered()));
	connect(ui->editItemAction,    SIGNAL(triggered()), this, SLOT(emitEditButtonClicked()));
	connect(ui->aboutAction,       SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));
	connect(ui->resetTimerAction,  SIGNAL(triggered()), this, SLOT(resetTimeRead()));
	connect(ui->saveLibraryAction, SIGNAL(triggered()), this, SLOT(saveLibrary()));
	connect(ui->exitAction,        SIGNAL(triggered()), this, SLOT(close()));
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
	ui->ratingData->setText(QString::number(selectedItemGeneric->getRating()) + "★");

	ui->timeRead->setDigitCount(8);
	ui->timeRead->display(QDateTime::fromTime_t(selectedItemGeneric->getTimeRead()).toUTC().toString("hh:mm:ss"));

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
		ui->eBookSizeData->setText(QString::number(selectedItemEBook->getFileSize()) + " MB");
        ui->eBookPagesData->setText(QString::number(selectedItemEBook->numberOfPages()));

        ui->bookInfoGroup->hide();
        ui->eBookInfoGroup->show();
	}

	// switch to stack widget item data view side
	ui->mainContent->setCurrentIndex(1);
}

// edit button slots
void MainWindow::emitEditButtonClicked() {
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
	QModelIndex index = ui->libraryListView->currentIndex();
	int position = index.row();
	library.editItemAt(editedData, position);
	refreshLibraryView();
	emit ui->libraryListView->clicked(index);
}

// start reading!
void MainWindow::startReading() {
	ReadingTimerWindow *timerWindow = new ReadingTimerWindow();
	connect(timerWindow, SIGNAL(quitSession(int)), this, SLOT(updateTimeRead(int)));
	timerWindow->show();
}

void MainWindow::updateTimeRead(int timeToAdd) {
	QModelIndex index = ui->libraryListView->currentIndex();
	int position = index.row();
	library.at(position)->addTimeRead(timeToAdd);
	emit ui->libraryListView->clicked(index);
}

void MainWindow::resetTimeRead() {
	QModelIndex index = ui->libraryListView->currentIndex();
	int position = index.row();
	QMessageBox::StandardButton reply;

	if (position >= 0) {
		reply = QMessageBox::question(this, "Reset timer", "Are you sure you want to reset the timer? This action can not be undone.", QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes) {
			library.at(position)->resetTimer();
			emit ui->libraryListView->clicked(index);
		}
	}
}

// save/load functionalities
void MainWindow::loadLibrary() {
	// file related variables
	QString filename = "library.xml";
	QFile file(filename);

	// library related variables
	library = Library();
	Book *book;
	eBook *ebook;

	if (file.open(QIODevice::ReadOnly)) {
		QXmlStreamReader stream(&file);

		// skip tokens
		//stream.readNext(); // doctype
		//stream.readNext(); // root

		while (!stream.atEnd()) {
			if (stream.isStartElement()) {
				if (stream.name().toString() == "book") {
					book = new Book("");

					stream.readNextStartElement();
					stream.readNext();
					book->setIsbn(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setTitle(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setPublisher(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setPublicationYear(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->rate(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setAuthor(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setGenre(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setPages(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setReleaseNumber(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					book->setTimeRead(stream.text().toInt());
					stream.readNext();

					library.addItem(book);
				}
				if (stream.name().toString() == "ebook") {
					ebook = new eBook("");

					stream.readNextStartElement();
					stream.readNext();
					ebook->setIsbn(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setTitle(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setPublisher(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setPublicationYear(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->rate(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setAuthor(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setGenre(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setFormat(stream.text().toString());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setFileSize(stream.text().toFloat());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setPages(stream.text().toInt());
					stream.readNext();

					stream.readNextStartElement();
					stream.readNext();
					ebook->setTimeRead(stream.text().toInt());
					stream.readNext();

					library.addItem(ebook);
				}
			}
			stream.readNext();
		}
		if (stream.hasError()) {
			QMessageBox::warning(this, "Load library", stream.errorString());
		}
	} else {
		QMessageBox::warning(this, "Load library", "There was an error while opening the file to load the library.");
	}
}

void MainWindow::saveLibrary() {
	// file related variables
	QString filename = "library.xml";
	QFile file(filename);

	if (file.open(QIODevice::WriteOnly)) {
		QXmlStreamWriter stream(&file);
		stream.setAutoFormatting(true);

		stream.writeStartDocument();
		stream.writeStartElement("library"); // root element

		// to prevent the library being saved in a reverse order we start saving from the last element
		for (int i = library.size(); i >= 0; i--) {
			LibraryItem *item = library.at(i);

			Book *itemBook = dynamic_cast<Book*>(item);
			if (itemBook) {
				stream.writeStartElement("book");
				stream.writeTextElement("isbn",      itemBook->getIsbn());
				stream.writeTextElement("title",     itemBook->getTitle());
				stream.writeTextElement("publisher", itemBook->getPublisher());
				stream.writeTextElement("year",      QString::number(itemBook->getYearPublished()));
				stream.writeTextElement("rating",    QString::number(itemBook->getRating()));
				stream.writeTextElement("author",    itemBook->getAuthor());
				stream.writeTextElement("genre",     itemBook->getGenre());
				stream.writeTextElement("pages",     QString::number(itemBook->numberOfPages()));
				stream.writeTextElement("release",   QString::number(itemBook->getReleaseNumber()));
				stream.writeTextElement("time",      QString::number(itemBook->getTimeRead()));
				stream.writeEndElement();
			}

			eBook *itemEBook = dynamic_cast<eBook*>(item);
			if (itemEBook) {
				stream.writeStartElement("ebook");
				stream.writeTextElement("isbn",      itemEBook->getIsbn());
				stream.writeTextElement("title",     itemEBook->getTitle());
				stream.writeTextElement("publisher", itemEBook->getPublisher());
				stream.writeTextElement("year",      QString::number(itemEBook->getYearPublished()));
				stream.writeTextElement("rating",    QString::number(itemEBook->getRating()));
				stream.writeTextElement("author",    itemEBook->getAuthor());
				stream.writeTextElement("genre",     itemEBook->getGenre());
				stream.writeTextElement("format",    itemEBook->getFormat());
				stream.writeTextElement("size",      QString::number(itemEBook->getFileSize()));
				stream.writeTextElement("pages",     QString::number(itemEBook->numberOfPages()));
				stream.writeTextElement("time",      QString::number(itemEBook->getTimeRead()));
				stream.writeEndElement();
			}
		}

		stream.writeEndElement(); // /root element
		stream.writeEndDocument();

		file.close();

		QMessageBox::information(this, "Save library", "Library has been successfully saved!");
	} else {
		QMessageBox::warning(this, "Save library", "There was an error while opening the file to save the library.");
	}
}
