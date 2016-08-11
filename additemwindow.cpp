#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddItemWindow) {
	ui->setupUi(this);

	// Setup window
	setWindowTitle("Add a new item to your library");
	setModal(true);
	QDialog::reject(); // Esc closes the window

	setupAddItemForm();

	adjustSize();
}

AddItemWindow::~AddItemWindow() {
	delete ui;
}

void AddItemWindow::setupAddItemForm() {
	// create base info form components
	QRadioButton *radioButtonBook = new QRadioButton("Book", this);
	QRadioButton *radioButtonEBook = new QRadioButton("E-Book", this);
	radioButtonBook->setChecked(true);

	QLabel *isbnLabel = new QLabel("ISBN: ", this);
	QLineEdit *isbnTextField = new QLineEdit(this);

	QLabel *titleLabel = new QLabel("Name: ", this);
	QLineEdit *titleTextField = new QLineEdit(this);

	QLabel *publisherLabel = new QLabel("Publisher: ", this);
	QLineEdit *publisherTextField = new QLineEdit(this);

	QLabel *coverImageLabel = new QLabel("Cover image: ", this);
	QLineEdit *coverImageTextField = new QLineEdit(this);

	QLabel *yearPublishedLabel = new QLabel("Year published: ", this);
	QComboBox *yearPublishedField = new QComboBox(this);
	for (int i = 1900; i < 2020; i++) {
		yearPublishedField->addItem(QString::number(i));
	}
	yearPublishedField->setCurrentText("2000");

	QLabel *ratingLabel = new QLabel("Rating: ", this);
	QRadioButton *ratingOneStarField = new QRadioButton("1 star", this);
	QRadioButton *ratingTwoStarField = new QRadioButton("2 stars", this);
	QRadioButton *ratingThreeStarField = new QRadioButton("3 stars", this);
	QRadioButton *ratingFourStarField = new QRadioButton("4 stars", this);
	QRadioButton *ratingFiveStarField = new QRadioButton("5 stars", this);

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
	basicInfoForm->addRow(isbnLabel, isbnTextField);
	basicInfoForm->addRow(titleLabel, titleTextField);
	basicInfoForm->addRow(publisherLabel, publisherTextField);
	basicInfoForm->addRow(coverImageLabel, coverImageTextField);
	basicInfoForm->addRow(yearPublishedLabel, yearPublishedField);
	basicInfoForm->addRow(ratingLabel, ratingLayout);
	QGroupBox *basicFormGroup = new QGroupBox("Basic informations", this);
	basicFormGroup->setLayout(basicInfoForm);

	// COMPONENTS SHOWN ONLY IF SELECTED //

	// create book info form components
	QLabel *bookAuthorLabel = new QLabel("Author: ", this);
	QLineEdit *bookAuthorTextField = new QLineEdit(this);

	QLabel *bookGenreLabel = new QLabel("Genre: ", this);
	QComboBox *bookGenreField = new QComboBox(this);
	bookGenreField->addItem("Drama");
	bookGenreField->addItem("Classic");
	bookGenreField->addItem("Comic");
	bookGenreField->addItem("Crime");
	bookGenreField->addItem("Fable");
	bookGenreField->addItem("Fairy tale");
	bookGenreField->addItem("Fanfiction");
	bookGenreField->addItem("Fantasy");
	bookGenreField->addItem("Folklore");
	bookGenreField->addItem("Hisorical Fiction");
	bookGenreField->addItem("Horror");
	bookGenreField->addItem("Humor");
	bookGenreField->addItem("Legend");
	bookGenreField->addItem("Magical realism");
	bookGenreField->addItem("Metafiction");
	bookGenreField->addItem("Mistery");
	bookGenreField->addItem("Mithology");
	bookGenreField->addItem("Realistic fiction");
	bookGenreField->addItem("Science fiction");
	bookGenreField->addItem("Short story");
	bookGenreField->addItem("Thriller");
	bookGenreField->addItem("Tall tale");
	bookGenreField->addItem("Western");

	QLabel *bookPagesLabel = new QLabel("Number of pages: ", this);
	QSpinBox *bookPagesField = new QSpinBox(this);
	bookPagesField->setMinimum(0);
	bookPagesField->setMaximum(10000);
	bookPagesField->setValue(bookPagesField->minimum());

	QLabel *bookReleaseLabel = new QLabel("Release: ", this);
	QComboBox *bookReleaseField = new QComboBox(this);
	bookReleaseField->addItem("First");
	bookReleaseField->addItem("Second");
	bookReleaseField->addItem("Third");
	bookReleaseField->addItem("Fourth");
	bookReleaseField->addItem("Fifth");

	QFormLayout *bookInfoForm = new QFormLayout();
	bookInfoForm->addRow(bookAuthorLabel, bookAuthorTextField);
	bookInfoForm->addRow(bookGenreLabel, bookGenreField);
	bookInfoForm->addRow(bookPagesLabel, bookPagesField);
	bookInfoForm->addRow(bookReleaseLabel, bookReleaseField);

	bookFormGroup = new QGroupBox("Book informations", this);
	bookFormGroup->setLayout(bookInfoForm);

	// create e-book info form components
	QLabel *eBookAuthorLabel = new QLabel("Author: ", this);
	QLineEdit *eBookAuthorTextField = new QLineEdit(this);

	QLabel *eBookGenreLabel = new QLabel("Genre: ", this);
	QComboBox *eBookGenreField = new QComboBox(this);
	eBookGenreField->addItem("Drama");
	eBookGenreField->addItem("Classic");
	eBookGenreField->addItem("Comic");
	eBookGenreField->addItem("Crime");
	eBookGenreField->addItem("Fable");
	eBookGenreField->addItem("Fairy tale");
	eBookGenreField->addItem("Fanfiction");
	eBookGenreField->addItem("Fantasy");
	eBookGenreField->addItem("Folklore");
	eBookGenreField->addItem("Hisorical Fiction");
	eBookGenreField->addItem("Horror");
	eBookGenreField->addItem("Humor");
	eBookGenreField->addItem("Legend");
	eBookGenreField->addItem("Magical realism");
	eBookGenreField->addItem("Metafiction");
	eBookGenreField->addItem("Mistery");
	eBookGenreField->addItem("Mithology");
	eBookGenreField->addItem("Realistic fiction");
	eBookGenreField->addItem("Science fiction");
	eBookGenreField->addItem("Short story");
	eBookGenreField->addItem("Thriller");
	eBookGenreField->addItem("Tall tale");
	eBookGenreField->addItem("Western");

	QLabel *fileFormatLabel = new QLabel("File format: ", this);
	QComboBox *fileFormatField = new QComboBox(this);
	fileFormatField->addItem(".acsm");
	fileFormatField->addItem(".mobi");
	fileFormatField->addItem(".epub");
	fileFormatField->addItem(".pdf");

	QLabel *fileSizeLabel = new QLabel("File size (MB): ", this);
	QSpinBox *fileSizeField = new QSpinBox(this);
	fileSizeField->setMinimum(0);
	fileSizeField->setMaximum(10000);
	fileSizeField->setValue(fileSizeField->minimum());

	QLabel *eBookPagesLabel = new QLabel("Number of pages: ", this);
	QSpinBox *eBookPagesField = new QSpinBox(this);
	eBookPagesField->setMinimum(0);
	eBookPagesField->setMaximum(10000);
	eBookPagesField->setValue(eBookPagesField->minimum());

	QFormLayout *eBookInfoForm = new QFormLayout();
	eBookInfoForm->addRow(eBookAuthorLabel, eBookAuthorTextField);
	eBookInfoForm->addRow(eBookGenreLabel, eBookGenreField);
	eBookInfoForm->addRow(fileFormatLabel, fileFormatField);
	eBookInfoForm->addRow(fileSizeLabel, fileSizeField);
	eBookInfoForm->addRow(eBookPagesLabel, eBookPagesField);

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

void AddItemWindow::newItemSubmitted() {
	//QMessageBox::information(this, "Aggiunto", "Oggetto di libreria");
	
	close();
}
