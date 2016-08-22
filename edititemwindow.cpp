#include "edititemwindow.h"
#include "ui_edititemwindow.h"

EditItemWindow::EditItemWindow(LibraryItem *item, QWidget *parent) : QDialog(parent), ui(new Ui::EditItemWindow) {
    ui->setupUi(this);
    setModal(true);

    setUpEditForm(item);
}

EditItemWindow::~EditItemWindow() {
    delete ui;
}

void EditItemWindow::setUpEditForm(LibraryItem *item) {
    QLineEdit *isbnEditData = new QLineEdit(item->getIsbn());
    QLineEdit *titleEditData = new QLineEdit(item->getTitle());
    QLineEdit *publisherData = new QLineEdit(item->getPublisher());
    //QLineEdit *coverData = new QLineEdit(item->getCoverImage());
    QComboBox *yearData = new QComboBox();
    for (int i = 1900; i < 2020; i++) {
        yearData->addItem(QString::number(i));
    }
    yearData->setCurrentText(QString::number(item->getYearPublished()));

    QRadioButton *ratingOneStarData = new QRadioButton("1 star", this);
    QRadioButton *ratingTwoStarData = new QRadioButton("2 stars", this);
    QRadioButton *ratingThreeStarData = new QRadioButton("3 stars", this);
    QRadioButton *ratingFourStarData = new QRadioButton("4 stars", this);
    QRadioButton *ratingFiveStarData = new QRadioButton("5 stars", this);

    unsigned int currentRating = item->getRating();
    if (currentRating == 1) {
        ratingOneStarData->setChecked(true);
    } else if (currentRating == 2) {
        ratingTwoStarData->setChecked(true);
    } else if (currentRating == 3) {
        ratingThreeStarData->setChecked(true);
    } else if (currentRating == 4) {
        ratingFourStarData->setChecked(true);
    } else if (currentRating == 5) {
        ratingFiveStarData->setChecked(true);
    }

    // create horizontal layout for the rating radio buttons
    QHBoxLayout *ratingLayout = new QHBoxLayout();
    ratingLayout->addWidget(ratingOneStarData);
    ratingLayout->addWidget(ratingTwoStarData);
    ratingLayout->addWidget(ratingThreeStarData);
    ratingLayout->addWidget(ratingFourStarData);
    ratingLayout->addWidget(ratingFiveStarData);

    QFormLayout *editFormLayout = new QFormLayout();
    editFormLayout->addRow("ISBN:", isbnEditData);
    editFormLayout->addRow("Title:", titleEditData);
    editFormLayout->addRow("Publisher:", publisherData);
    editFormLayout->addRow("Year Published:", yearData);

    setLayout(editFormLayout);
}
