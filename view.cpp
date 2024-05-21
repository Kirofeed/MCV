#include "view.h"

View::View(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout;

    searchInput = new QLineEdit(this);
    searchButton = new QPushButton("Search", this);
    connect(searchButton, &QPushButton::clicked, [this]() {
        emit searchRequested(searchInput->text());
    });

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchInput);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    patientDetails = new QLabel(this);
    mainLayout->addWidget(patientDetails);

    table = new QTableWidget(0, 4, this); // 4 columns: Name, Diagnosis, Room, Remove Button
    table->setHorizontalHeaderLabels({"Name", "Diagnosis", "Room", ""});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(table);

    addButton = new QPushButton("Add Patient", this);
    connect(addButton, &QPushButton::clicked, [this]() {
        emit addPatientRequested();
    });
    mainLayout->addWidget(addButton);

    this->setMinimumSize(500, 350);

    setLayout(mainLayout);
}

void View::setPatientDetails(const QString &name, const QString &diagnosis, int room) {
    patientDetails->setText("Name: " + name + "\nDiagnosis: " + diagnosis + "\nRoom: " + QString::number(room));
}

void View::addPatientToTable(const QString &name, const QString &diagnosis, int room) {
    int row = table->rowCount();
    table->insertRow(row);
    table->setItem(row, 0, new QTableWidgetItem(name));
    table->setItem(row, 1, new QTableWidgetItem(diagnosis));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(room)));
    createRemoveButton(row);
}

QString View::getSearchQuery() const {
    return searchInput->text();
}

void View::clearSearchInput() {
    searchInput->clear();
}

void View::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    QFont font = searchInput->font();
    int newSize = qMax(10, qMin(24, event->size().height() / 50));  // Ограничение размера шрифта от 10 до 24 пунктов
    font.setPointSize(newSize);

    searchInput->setFont(font);
    searchButton->setFont(font);
    patientDetails->setFont(font);
    addButton->setFont(font);

    for (int i = 0; i < table->rowCount(); ++i) {
        for (int j = 0; j < table->columnCount(); ++j) {
            QTableWidgetItem *item = table->item(i, j);
            if (item) {
                item->setFont(font);
            }
        }
        QWidget *widget = table->cellWidget(i, 3);
        if (widget) {
            widget->setFont(font);
        }
    }
}

void View::createRemoveButton(int row) {
    QPushButton *removeButton = new QPushButton("-");
    table->setCellWidget(row, 3, removeButton);
    connect(removeButton, &QPushButton::clicked, this, &View::handleRemoveButtonClicked);
}

void View::handleRemoveButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    int row = table->indexAt(button->pos()).row();
    QString name = table->item(row, 0)->text();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Remove Patient", "Are you sure you want to remove " + name + "?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        emit removePatientRequested(name);
    }
}

void View::removePatientFromTable(int row) {
    table->removeRow(row);
}


QString View::getPatientNameAtRow(int row) const {
    QTableWidgetItem *item = table->item(row, 0);
    return item ? item->text() : QString();
}

int View::getRowCount() const {
    return table->rowCount();
}
