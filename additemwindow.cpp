#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddItemWindow) {
	ui->setupUi(this);

	// Setup window
	setWindowTitle("Add a new item to your library");
	setModal(true);
	QDialog::reject(); // Esc closes the window

	mainLayout = new QVBoxLayout();
	setupAddItemForm();
}

AddItemWindow::~AddItemWindow() {
	delete ui;
}

void AddItemWindow::setupAddItemForm() {
	// create labels and input widgets
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

	// setup widgets for the window main layout
	mainLayout->addWidget(itemTypeGroup);
	mainLayout->addWidget(basicFormGroup);
	mainLayout->addWidget(formResponse);

	setLayout(mainLayout);

	// connect components
	connect(buttonOk, SIGNAL(clicked()), this, SLOT(newItemSubmitted()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(radioButtonBook, SIGNAL(clicked()), this, SLOT(addBookForm()));
	connect(radioButtonEBook, SIGNAL(clicked()), this, SLOT(addEBookForm()));
}

void AddItemWindow::addBookForm() {
	QLabel *authorLabel = new QLabel("Author: ", this);
	QLineEdit *authorTextField = new QLineEdit(this);

	QLabel *genreLabel = new QLabel("Genre: ", this);
	QLineEdit *genreTextField = new QLineEdit(this);

	QFormLayout *bookInfoForm = new QFormLayout();
	bookInfoForm->addRow(authorLabel, authorTextField);
	bookInfoForm->addRow(genreLabel, genreTextField);

	QGroupBox *bookFormGroup = new QGroupBox("Book informations", this);
	bookFormGroup->setLayout(bookInfoForm);

	mainLayout->addWidget(bookFormGroup);
}

void AddItemWindow::addEBookForm() {}

void AddItemWindow::newItemSubmitted() {
	QMessageBox::information(this, "Aggiunto", "Oggetto di libreria");
	close();
}
