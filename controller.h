#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

#include <QObject>

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(Model *model, View *view);

private slots:
    void handleSearchRequest(const QString &name);
    void handleAddPatientRequest();
    void handleRemovePatientRequest(const QString &name);

private:
    Model *model;
    View *view;

    void showAddPatientDialog();
};

#endif // CONTROLLER_H
