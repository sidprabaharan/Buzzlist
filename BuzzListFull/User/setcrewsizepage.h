#ifndef SETCREWSIZEPAGE_H
#define SETCREWSIZEPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "Admin/QueueSystem.h"

class SetCrewSizePage : public QWidget {
    Q_OBJECT

public:
    explicit SetCrewSizePage(QueueSystem *queueSystem, QWidget *parent = nullptr);
    void updateBarDetails(const QString &name, const QString &status, const QString &details, const QString &events, const QString &imagePath);

signals:
    void joinBuzzClicked();
    void backButtonClicked();

private:
    QueueSystem *queueSystem;  // Pointer to the queue system
    QLabel *barImageLabel;
    QLabel *barNameLabel;
    QLabel *barStatusLabel;
    QLabel *barDetailsLabel;
    QLabel *barEventsLabel;
    QLabel *crewSizeLabel;
    QPushButton *backButton;
    int crewSize;

    void incrementCrewSize();
    void decrementCrewSize();
};

#endif // SETCREWSIZEPAGE_H
