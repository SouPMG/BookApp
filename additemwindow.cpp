#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddItemWindow) {
	ui->setupUi(this);

	// Setup window
	setWindowTitle("Add a new item to your library");
	setModal(true);
	QDialog::reject(); // Esc closes the window

	// Setup form elements
	setupAddItemForm();

	// Optimize window size
	adjustSize();
}

AddItemWindow::~AddItemWindow() {
	delete ui;
}

void AddItemWindow::setupAddItemForm() {
	// base info form components
	radioButtonBook = new QRadioButton("Book", this);
	radioButtonEBook = new QRadioButton("E-Book", this);
	radioButtonBook->setChecked(true);

	isbnTextField = new QLineEdit(this);
	titleTextField = new QLineEdit(this);
	publisherTextField = new QLineEdit(this);
	coverImageTextField = new QLineEdit(this);

	yearPublishedField = new QComboBox(this);
	for (int i = 1900; i < 2020; i++) {
		yearPublishedField->addItem(QString::number(i));
	}
	yearPublishedField->setCurrentText("2000");

	ratingOneStarField = new QRadioButton("1 star", this);
	ratingTwoStarField = new QRadioButton("2 stars", this);
	ratingThreeStarField = new QRadioButton("3 stars", this);
	ratingFourStarField = new QRadioButton("4 stars", this);
	ratingFiveStarField = new QRadioButton("5 stars", this);

	// create Ok Cancel buttons
	QPushButton *buttonOk = new QPushButton("Ok");
	QPushButton *buttonCancel = new QPushButton("Cancel");

	// create DialogButtonBox with previously declared buttons
	QDialogButtonBox *formResponse = new QDialogButtonBox(Qt::Horizontal, this);
	formResponse->addButton(buttonOk, QDialogButtonBox::ActionRole);
	formResponse->addButton(buttonCancel, QDialogButtonBox::ActionRole);

	// create vertical layout for the item type radio buttons
	QVBoxLayout *itemTypeLayout = new QVBoxLayout();
	itemTypeLayout->addWidget(radioButtonBook);
	itemTypeLayout->addWidget(radioButtonEBook);
	QGroupBox *itemTypeGroup = new QGroupBox("Select item type", this);
	itemTypeGroup->setLayout(itemTypeLayout);

	// create horizontal layout for the rating radio buttons
	QHBoxLayout *ratingLayout = new QHBoxLayout();
	ratingLayout->addWidget(ratingOneStarField);
	ratingLayout->addWidget(ratingTwoStarField);
	ratingLayout->addWidget(ratingThreeStarField);
	ratingLayout->addWidget(ratingFourStarField);
	ratingLayout->addWidget(ratingFiveStarField);

	// create form layout for the form members
	QFormLayout *basicInfoForm = new QFormLayout();
	basicInfoForm->addRow("ISBN:", isbnTextField);
	basicInfoForm->addRow("Title:", titleTextField);
	basicInfoForm->addRow("Publisher:", publisherTextField);
	basicInfoForm->addRow("Cover image:", coverImageTextField);
	basicInfoForm->addRow("Publication year:", yearPublishedField);
	basicInfoForm->addRow("Rating:", ratingLayout);

	QGroupBox *basicFormGroup = new QGroupBox("Basic informations", this);
	basicFormGroup->setLayout(basicInfoForm);

	// COMPONENTS SHOWN ONLY IF SELECTED //

	// utility data structures
	QStringList genres;
	genres << "Drama" << "Classic" << "Comic" << "Crime" << "Fable" << "Fairy tale" << "Fanfiction" << "Fantasy"
		   << "Folklore" << "Hisorical Fiction" << "Horror" << "Humor" << "Legend" << "Magical realism" << "Metafiction"
		   << "Mistery" << "Mithology" << "Realistic fiction" << "Science fiction" << "Short story" << "Thriller"
		   << "Tall tale" << "Western";

	// create book info form components
	bookAuthorTextField = new QLineEdit(this);

	bookGenreField = new QComboBox(this);
	foreach (QString genre, genres) {
		bookGenreField->addItem(genre);
	}

	bookPagesField = new QSpinBox(this);
	bookPagesField->setMinimum(0);
	bookPagesField->setMaximum(10000);
	bookPagesField->setValue(bookPagesField->minimum());

	bookReleaseField = new QComboBox(this);
	bookReleaseField->addItem("First");
	bookReleaseField->addItem("Second");
	bookReleaseField->addItem("Third");
	bookReleaseField->addItem("Fourth");
	bookReleaseField->addItem("Fifth");

	QFormLayout *bookInfoForm = new QFormLayout();
	bookInfoForm->addRow("Author:", bookAuthorTextField);
	bookInfoForm->addRow("Genre:", bookGenreField);
	bookInfoForm->addRow("Pages:", bookPagesField);
	bookInfoForm->addRow("Release:", bookReleaseField);

	bookFormGroup = new QGroupBox("Book informations", this);
	bookFormGroup->setLayout(bookInfoForm);

	// create e-book info form components
	eBookAuthorTextField = new QLineEdit(this);

	eBookGenreField = new QComboBox(this);
	foreach (QString genre, genres) {
		eBookGenreField->addItem(genre);
	}

	fileFormatField = new QComboBox(this);
	fileFormatField->addItem(".acsm");
	fileFormatField->addItem(".mobi");
	fileFormatField->addItem(".epub");
	fileFormatField->addItem(".pdf");

	fileSizeField = new QSpinBox(this);
	fileSizeField->setMinimum(0);
	fileSizeField->setMaximum(10000);
	fileSizeField->setValue(fileSizeField->minimum());

	eBookPagesField = new QSpinBox(this);
	eBookPagesField->setMinimum(0);
	eBookPagesField->setMaximum(10000);
	eBookPagesField->setValue(eBookPagesField->minimum());

	QFormLayout *eBookInfoForm = new QFormLayout();
	eBookInfoForm->addRow("Author:", eBookAuthorTextField);
	eBookInfoForm->addRow("Genre:", eBookGenreField);
	eBookInfoForm->addRow("File format:", fileFormatField);
	eBookInfoForm->addRow("File size (MB):", fileSizeField);
	eBookInfoForm->addRow("Pages:", eBookPagesField);

	eBookFormGroup = new QGroupBox("E-Book informations", this);
	eBookFormGroup->setLayout(eBookInfoForm);

	// setup widgets for the window main layout
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(itemTypeGroup);
	mainLayout->addWidget(basicFormGroup);
	mainLayout->addWidget(bookFormGroup);
	mainLayout->addWidget(eBookFormGroup);
	mainLayout->addWidget(formResponse);

	// hide e-book form until selected
	eBookFormGroup->hide();

	setLayout(mainLayout);

	// connect components
	connect(buttonOk, SIGNAL(clicked()), this, SLOT(newItemSubmitted()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));

	connect(radioButtonBook, SIGNAL(clicked()), this, SLOT(showBookForm()));
	connect(radioButtonEBook, SIGNAL(clicked()), this, SLOT(showEBookForm()));
}

void AddItemWindow::showBookForm() {
	eBookFormGroup->hide();
	bookFormGroup->show();

	adjustSize();
}

void AddItemWindow::showEBookForm() {
	bookFormGroup->hide();
	eBookFormGroup->show();

	adjustSize();
}

unsigned int AddItemWindow::getCurrentRating() const {
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

unsigned int AddItemWindow::getCurrentRelease() const {
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

void AddItemWindow::newItemSubmitted() {
	LibraryItem *newItem;

	QString itemISBN = isbnTextField->text();
	QString itemTitle = titleTextField->text();
	QString itemPublisher = publisherTextField->text();
	QString itemCoverImage = coverImageTextField->text();
	unsigned int itemYearPublished = yearPublishedField->currentText().toInt();
	unsigned int itemRating = getCurrentRating();

	if (radioButtonBook->isChecked()) {
		QString itemAuthor = bookAuthorTextField->text();
		QString itemGenre = bookGenreField->currentText();
		unsigned int itemPages = bookPagesField->value();
		unsigned int itemRelease = getCurrentRelease();

		newItem = new Book(itemISBN, itemTitle, itemPublisher, itemCoverImage, itemYearPublished, itemRating, itemAuthor, itemGenre, itemPages, itemRelease);
	} else if (radioButtonEBook->isChecked()) {
		QString itemAuthor = eBookAuthorTextField->text();
		QString itemGenre = eBookGenreField->currentText();
		QString itemFormat = fileFormatField->currentText();
		float itemSize = fileSizeField->value();
		unsigned int itemPages = eBookPagesField->value();

		newItem = new eBook(itemISBN, itemTitle, itemPublisher, itemCoverImage, itemYearPublished, itemRating, itemAuthor, itemGenre, itemFormat, itemSize, itemPages);
	} else {
		// if everything fails build a default book with given mandatory ISBN
		newItem = new Book(itemISBN);
	}
	emit itemAdded(newItem);
	close();
}
