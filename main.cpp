#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "model.h"
#include "view.h"
#include "controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Model model;
    View view;
    Controller controller(&model, &view);

    QList<Patient> patients = model.getPatients();
    for (const auto &patient : patients) {
        view.addPatientToTable(patient.name, patient.diagnosis, patient.room);
    }

    view.show();
    return app.exec();
}
