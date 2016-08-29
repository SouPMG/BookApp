#include "edititemwindow.h"
#include "ui_edititemwindow.h"

EditItemWindow::EditItemWindow(LibraryItem *item, QWidget *parent) : QDialog(parent), ui(new Ui::EditItemWindow) {
    ui->setupUi(this);
    setModal(true);

	setWindowTitle("Edit item");

    setUpEditForm(item);
}

EditItemWindow::~EditItemWindow() {
    delete ui;
}

void EditItemWindow::setUpEditForm(LibraryItem *item) {
	// setup the form based on the already existing item fields

	// create Ok Cancel buttons
	QPushButton *buttonOk = new QPushButton("Ok");
	QPushButton *buttonCancel = new QPushButton("Cancel");

	// create DialogButtonBox with previously declared buttons
	QDialogButtonBox *formResponse = new QDialogButtonBox(Qt::Horizontal, this);
	formResponse->addButton(buttonOk, QDialogButtonBox::ActionRole);
	formResponse->addButton(buttonCancel, QDialogButtonBox::ActionRole);

	// setup the main layout

	// we start with the generic libraryitem informations
	QVBoxLayout *editMainLayout = new QVBoxLayout();
	editMainLayout->addWidget(addBasicInfo(item));

	// now we identify the type of library item to fill in additional info
	// add a new conditional branch when adding new types of item
	Book *bookItem = dynamic_cast<Book*>(item);
	if (bookItem) {
		itemType = "book";
		editMainLayout->addWidget(addBookInfo(bookItem));
	}
	eBook *eBookItem = dynamic_cast<eBook*>(item);
	if (eBookItem) {
		itemType = "ebook";
		editMainLayout->addWidget(addEBookInfo(eBookItem));
	}

	editMainLayout->addWidget(formResponse);

	setLayout(editMainLayout);
	adjustSize();

	connect(buttonOk, SIGNAL(clicked()), this, SLOT(editDataSubmitted()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

QGroupBox *EditItemWindow::addBasicInfo(LibraryItem *item) {
	isbnTextField = new QLineEdit(item->getIsbn());
	titleTextField = new QLineEdit(item->getTitle());
	publisherTextField = new QLineEdit(item->getPublisher());
	//QLineEdit *coverData = new QLineEdit(item->getCoverImage());

	yearPublishedField = new QComboBox();
	for (int i = 1900; i < 2020; i++) {
		yearPublishedField->addItem(QString::number(i));
	}
	yearPublishedField->setCurrentText(QString::number(item->getYearPublished()));

	ratingOneStarField = new QRadioButton("1 star", this);
	ratingTwoStarField = new QRadioButton("2 stars", this);
	ratingThreeStarField = new QRadioButton("3 stars", this);
	ratingFourStarField = new QRadioButton("4 stars", this);
	ratingFiveStarField = new QRadioButton("5 stars", this);

	unsigned int currentRating = item->getRating();
	if (currentRating == 1) {
		ratingOneStarField->setChecked(true);
	} else if (currentRating == 2) {
		ratingTwoStarField->setChecked(true);
	} else if (currentRating == 3) {
		ratingThreeStarField->setChecked(true);
	} else if (currentRating == 4) {
		ratingFourStarField->setChecked(true);
	} else if (currentRating == 5) {
		ratingFiveStarField->setChecked(true);
	}

	// create horizontal layout for the rating radio buttons
	QHBoxLayout *ratingLayout = new QHBoxLayout();
	ratingLayout->addWidget(ratingOneStarField);
	ratingLayout->addWidget(ratingTwoStarField);
	ratingLayout->addWidget(ratingThreeStarField);
	ratingLayout->addWidget(ratingFourStarField);
	ratingLayout->addWidget(ratingFiveStarField);

	// create form layout for the generic info
	QFormLayout *generalInfoFormLayout = new QFormLayout();
	generalInfoFormLayout->addRow("ISBN:", isbnTextField);
	generalInfoFormLayout->addRow("Title:", titleTextField);
	generalInfoFormLayout->addRow("Publisher:", publisherTextField);
	generalInfoFormLayout->addRow("Year Published:", yearPublishedField);
	generalInfoFormLayout->addRow("Rating:", ratingLayout);

	QGroupBox *generalInfoGroup = new QGroupBox("Generic informations", this);
	generalInfoGroup->setLayout(generalInfoFormLayout);

	return generalInfoGroup;
}

QGroupBox *EditItemWindow::addBookInfo(Book *bookItem) {
	// building utility variables
	QStringList genres;
	genres << "Drama" << "Classic" << "Comic" << "Crime" << "Fable" << "Fairy tale" << "Fanfiction" << "Fantasy"
		   << "Folklore" << "Hisorical Fiction" << "Horror" << "Humor" << "Legend" << "Magical realism" << "Metafiction"
		   << "Mistery" << "Mithology" << "Realistic fiction" << "Science fiction" << "Short story" << "Thriller"
		   << "Tall tale" << "Western";

	// book author
	bookAuthorTextField = new QLineEdit(bookItem->getAuthor());
	// book genre
	bookGenreField = new QComboBox();
	foreach(QString genre, genres) {
		bookGenreField->addItem(genre);
	}
	bookGenreField->setCurrentText(bookItem->getGenre());
	// book pages
	bookPagesField = new QSpinBox();
	bookPagesField->setMinimum(0);
	bookPagesField->setMaximum(10000);
	bookPagesField->setValue(bookItem->numberOfPages());
	// book release number
	bookReleaseField = new QComboBox();
	bookReleaseField->addItem("First");
	bookReleaseField->addItem("Second");
	bookReleaseField->addItem("Third");
	bookReleaseField->addItem("Fourth");
	bookReleaseField->addItem("Fifth");
	unsigned int currentRelease = bookItem->getReleaseNumber();
	if (currentRelease == 1) {
		bookReleaseField->setCurrentText("First");
	} else if (currentRelease == 2) {
		bookReleaseField->setCurrentText("Second");
	} else if (currentRelease == 3) {
		bookReleaseField->setCurrentText("Third");
	} else if (currentRelease == 4) {
		bookReleaseField->setCurrentText("Fourth");
	} else if (currentRelease == 5) {
		bookReleaseField->setCurrentText("Fifth");
	}

	QFormLayout *bookInfoFormLayout = new QFormLayout();
	bookInfoFormLayout->addRow("Author:", bookAuthorTextField);
	bookInfoFormLayout->addRow("Genre:", bookGenreField);
	bookInfoFormLayout->addRow("Pages:", bookPagesField);
	bookInfoFormLayout->addRow("Release:", bookReleaseField);

	QGroupBox *bookInfoGroup = new QGroupBox("Book informations");
	bookInfoGroup->setLayout(bookInfoFormLayout);

	return bookInfoGroup;
}

QGroupBox *EditItemWindow::addEBookInfo(eBook *eBookItem) {
	// building utility variables
	QStringList genres;
	genres << "Drama" << "Classic" << "Comic" << "Crime" << "Fable" << "Fairy tale" << "Fanfiction" << "Fantasy"
		   << "Folklore" << "Hisorical Fiction" << "Horror" << "Humor" << "Legend" << "Magical realism" << "Metafiction"
		   << "Mistery" << "Mithology" << "Realistic fiction" << "Science fiction" << "Short story" << "Thriller"
		   << "Tall tale" << "Western";

	// eBook author
	eBookAuthorTextField = new QLineEdit(eBookItem->getAuthor());
	// eBook genre
	eBookGenreField = new QComboBox();
	foreach(QString genre, genres) {
		eBookGenreField->addItem(genre);
	}
	eBookGenreField->setCurrentText(eBookItem->getGenre());
	// eBook format
	fileFormatField = new QComboBox();
	fileFormatField->addItem(".acsm");
	fileFormatField->addItem(".mobi");
	fileFormatField->addItem(".epub");
	fileFormatField->addItem(".pdf");
	fileFormatField->setCurrentText(eBookItem->getFormat());
	// eBook file size
	fileSizeField = new QSpinBox();
	fileSizeField->setMinimum(0);
	fileSizeField->setMaximum(10000);
	fileSizeField->setValue(eBookItem->getFileSize());
	// eBook pages
	eBookPagesField = new QSpinBox();
	eBookPagesField->setMinimum(0);
	eBookPagesField->setMaximum(10000);
	eBookPagesField->setValue(eBookItem->numberOfPages());

	QFormLayout *eBookInfoFormLayout = new QFormLayout();
	eBookInfoFormLayout->addRow("Author:", eBookAuthorTextField);
	eBookInfoFormLayout->addRow("Genre:", eBookGenreField);
	eBookInfoFormLayout->addRow("File format:", fileFormatField);
	eBookInfoFormLayout->addRow("File size(MB):", fileSizeField);
	eBookInfoFormLayout->addRow("Pages:", eBookPagesField);

	QGroupBox *eBookInfoGroup = new QGroupBox();
	eBookInfoGroup->setLayout(eBookInfoFormLayout);

	return eBookInfoGroup;
}

unsigned int EditItemWindow::getCurrentRating() const {
	if (ratingOneStarField->isChecked()) {
		return 1;
	}
	if (ratingTwoStarField->isChecked()) {
		return 2;
	}
	if (ratingThreeStarField->isChecked()) {
		return 3;
	}
	if (ratingFourStarField->isChecked()) {
		return 4;
	}
	if (ratingFiveStarField->isChecked()) {
		return 5;
	}
	return 0; // TODO: implement exception
}

unsigned int EditItemWindow::getCurrentRelease() const {
	if (bookReleaseField->currentText() == "First") {
		return 1;
	}
	if (bookReleaseField->currentText() == "Second") {
		return 2;
	}
	if (bookReleaseField->currentText() == "Third") {
		return 3;
	}
	if (bookReleaseField->currentText() == "Fourth") {
		return 4;
	}
	if (bookReleaseField->currentText() == "Fifth") {
		return 5;
	}
	return 0; // TODO: implement exception
}

// slots
void EditItemWindow::editDataSubmitted() {
	LibraryItem *newItem;

	QString itemISBN = isbnTextField->text();
	QString itemTitle = titleTextField->text();
	QString itemPublisher = publisherTextField->text();
	//QString itemCoverImage = coverImageTextField->text();
	unsigned int itemYearPublished = yearPublishedField->currentText().toInt();
	unsigned int itemRating = getCurrentRating();

	if (itemType == "book") {
		QString itemAuthor = bookAuthorTextField->text();
		QString itemGenre = bookGenreField->currentText();
		unsigned int itemPages = bookPagesField->value();
		unsigned int itemRelease = getCurrentRelease();

		newItem = new Book(itemISBN, itemTitle, itemPublisher, "itemCoverImage", itemYearPublished, itemRating, 0, itemAuthor, itemGenre, itemPages, itemRelease);
	} else if (itemType == "ebook") {
		QString itemAuthor = eBookAuthorTextField->text();
		QString itemGenre = eBookGenreField->currentText();
		QString itemFormat = fileFormatField->currentText();
		float itemSize = fileSizeField->value();
		unsigned int itemPages = eBookPagesField->value();

		newItem = new eBook(itemISBN, itemTitle, itemPublisher, "itemCoverImage", itemYearPublished, itemRating, 0, itemAuthor, itemGenre, itemFormat, itemSize, itemPages);
	} else {
		// if everything fails build a default book with given mandatory ISBN
		newItem = new Book(itemISBN);
	}
	emit itemEdited(newItem);
	close();
}
