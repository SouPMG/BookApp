#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) : QDialog(parent), ui(new Ui::AddItemWindow) {
	ui->setupUi(this);

	// Setup window
	setWindowTitle("Add a new item to your library");
	setModal(true);
	QDialog::reject(); // Esc closes the window

	setupAddItemForm();
}

AddItemWindow::~AddItemWindow() {
	delete ui;
}

void AddItemWindow::setupAddItemForm() {
	// create labels and input widgets
	QLabel *itemTypeLabel = new QLabel("Tipo di oggetto: ", this);
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
	QLineEdit *yearPublishedTextField = new QLineEdit(this);

	QLabel *ratingLabel = new QLabel("Rating: ", this);
	QLineEdit *ratingTextField = new QLineEdit(this);

	// create Ok Cancel buttons
	QPushButton *buttonOk = new QPushButton("Ok");
	QPushButton *buttonCancel = new QPushButton("Cancel");

	// create DialogButtonBox with previously declared buttons
	QDialogButtonBox *formResponse = new QDialogButtonBox(Qt::Horizontal, this);
	formResponse->addButton(buttonOk, QDialogButtonBox::ActionRole);
	formResponse->addButton(buttonCancel, QDialogButtonBox::ActionRole);

	// create vertical layout for radio buttons
	QVBoxLayout *typeSelectionLayout = new QVBoxLayout();
	typeSelectionLayout->addWidget(radioButtonBook);
	typeSelectionLayout->addWidget(radioButtonEBook);

	// create form layout for form members
	QFormLayout *addItemForm = new QFormLayout();
	addItemForm->addRow(itemTypeLabel, typeSelectionLayout);
	addItemForm->addRow(isbnLabel, isbnTextField);
	addItemForm->addRow(titleLabel, titleTextField);
	addItemForm->addRow(publisherLabel, publisherTextField);
	addItemForm->addRow(coverImageLabel, coverImageTextField);
	addItemForm->addRow(yearPublishedLabel, yearPublishedTextField);
	addItemForm->addRow(ratingLabel, ratingTextField);

	// create vertical layout for the dialog window
	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(addItemForm);
	mainLayout->addWidget(formResponse);

	setLayout(mainLayout);

	// connect components
	connect(buttonOk, SIGNAL(clicked()), this, SLOT(newItemSubmitted()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
}

void AddItemWindow::newItemSubmitted() {
	QMessageBox::information(this, "Aggiunto", "Oggetto di libreria");
	close();
}
