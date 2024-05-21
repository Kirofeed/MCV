#include "controller.h"
#include <QInputDialog>

Controller::Controller(Model *model, View *view) : model(model), view(view) {
    connect(view, &View::searchRequested, this, &Controller::handleSearchRequest);
    connect(view, &View::addPatientRequested, this, &Controller::handleAddPatientRequest);
    connect(view, &View::removePatientRequested, this, &Controller::handleRemovePatientRequest);
}

void Controller::handleSearchRequest(const QString &name) {
    Patient patient = model->searchPatient(name);
    if (!patient.name.isEmpty()) {
        view->setPatientDetails(patient.name, patient.diagnosis, patient.room);
    } else {
        view->setPatientDetails("Not Found", "", 0);
    }
}

void Controller::handleAddPatientRequest() {
    showAddPatientDialog();
}

void Controller::handleRemovePatientRequest(const QString &name) {
    for (int row = 0; row < view->getRowCount(); ++row) {
        if (view->getPatientNameAtRow(row) == name) {
            view->removePatientFromTable(row);
            break;
        }
    }
    model->removePatient(name);
}

void Controller::showAddPatientDialog() {
    bool ok;
    QString name = QInputDialog::getText(view, "Add Patient", "Name:", QLineEdit::Normal, "", &ok);
    if (ok && !name.isEmpty()) {
        QString diagnosis = QInputDialog::getText(view, "Add Patient", "Diagnosis:", QLineEdit::Normal, "", &ok);
        if (ok && !diagnosis.isEmpty()) {
            int room = QInputDialog::getInt(view, "Add Patient", "Room:", 0, 0, 9999, 1, &ok);
            if (ok) {
                Patient patient{name, diagnosis, room};
                model->addPatient(patient);
                view->addPatientToTable(name, diagnosis, room);
            }
        }
    }
}
