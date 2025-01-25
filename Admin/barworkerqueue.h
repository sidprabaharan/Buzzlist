#ifndef BARWORKERQUEUE_H
#define BARWORKERQUEUE_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include "QueueSystem.h"

class barWorkerQueue : public QWidget {
    Q_OBJECT

private:
    QueueSystem *queueSystem;
    QLabel *queueLabel;
    QLabel *pinLabel; // Label to display the pin
    QListWidget *queueList;

public:
    explicit barWorkerQueue(QWidget *parent = nullptr);

    void setQueueSystem(QueueSystem *system); // Setter for QueueSystem instance


signals:
    void switchToHomePage();

private slots:
    void onUserJoined(int userId, const QString &userName, int groupSize);
    void onUserServed(int userId, const QString &userName, const QString &pin); // Updated to include pin
    void onUserRemoved(int userId);
};

#endif // BARWORKERQUEUE_H
