#include "model.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

Model::Model() {
    loadPatients();
}

QList<Patient> Model::getPatients() const {
    return patients;
}

void Model::addPatient(const Patient &patient) {
    patients.append(patient);
    savePatients();
}

void Model::removePatient(const QString &name) {
    for (int i = 0; i < patients.size(); ++i) {
        if (patients[i].name == name) {
            patients.removeAt(i);
            savePatients();
            return;
        }
    }
}

Patient Model::searchPatient(const QString &name) const {
    for (const auto &patient : patients) {
        if (patient.name == name) {
            return patient;
        }
    }
    return Patient{};
}

void Model::loadPatients() {
    QFile file("patients.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        return;
    }
    QJsonArray jsonArray = doc.array();
    for (const QJsonValue &value : jsonArray) {
        if (value.isObject()) {
            patients.append(Patient::fromJson(value.toObject()));
        }
    }
}

void Model::savePatients() const {
    QJsonArray jsonArray;
    for (const auto &patient : patients) {
        jsonArray.append(patient.toJson());
    }

    QJsonDocument doc(jsonArray);
    QFile file("patients.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    file.write(doc.toJson());
    file.close();
}
