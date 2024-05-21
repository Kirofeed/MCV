#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include <QList>
#include <QJsonObject>

struct Patient {
    QString name;
    QString diagnosis;
    int room;

    QJsonObject toJson() const {
        QJsonObject jsonObj;
        jsonObj["name"] = name;
        jsonObj["diagnosis"] = diagnosis;
        jsonObj["room"] = room;
        return jsonObj;
    }

    static Patient fromJson(const QJsonObject &jsonObj) {
        Patient patient;
        patient.name = jsonObj["name"].toString();
        patient.diagnosis = jsonObj["diagnosis"].toString();
        patient.room = jsonObj["room"].toInt();
        return patient;
    }
};

class Model {
public:
    Model();
    QList<Patient> getPatients() const;
    void addPatient(const Patient &patient);
    void removePatient(const QString &name);
    Patient searchPatient(const QString &name) const;

private:
    QList<Patient> patients;
    void loadPatients();
    void savePatients() const;
};

#endif // MODEL_H
