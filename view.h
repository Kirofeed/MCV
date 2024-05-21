#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QResizeEvent>
#include <QHeaderView>
#include <QMessageBox>

class View : public QWidget {
    Q_OBJECT
public:
    View(QWidget *parent = nullptr);
    void setPatientDetails(const QString &name, const QString &diagnosis, int room);
    void addPatientToTable(const QString &name, const QString &diagnosis, int room);
    QString getSearchQuery() const;
    void clearSearchInput();
    void removePatientFromTable(int row);
    QString getPatientNameAtRow(int row) const;
    int getRowCount() const;

signals:
    void searchRequested(const QString &name);
    void addPatientRequested();
    void removePatientRequested(const QString &name);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void handleRemoveButtonClicked();

private:
    QLineEdit *searchInput;
    QPushButton *searchButton;
    QTableWidget *table;
    QLabel *patientDetails;
    QPushButton *addButton;

    void createRemoveButton(int row);
};

#endif // VIEW_H
