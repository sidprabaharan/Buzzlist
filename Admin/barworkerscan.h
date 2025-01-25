#ifndef BARWORKERSCAN_H
#define BARWORKERSCAN_H

#include <QWidget>
#include "QueueSystem.h" // Include QueueSystem header

class barWorkerScan : public QWidget {
    Q_OBJECT

private:
    QueueSystem *queueSystem; // Pointer to the QueueSystem
    QString currentPin;       // Current pin for verification

public:
    explicit barWorkerScan(QWidget *parent = nullptr);

    void setQueueSystem(QueueSystem *system); // Method to set the QueueSystem

signals:
    void switchToHomePage();
};

#endif // BARWORKERSCAN_H
