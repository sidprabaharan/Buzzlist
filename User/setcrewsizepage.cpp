#include "setcrewsizepage.h"
#include "userPageManager.h"
#include "Admin/QueueSystem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPixmap>
#include <QTime>
#include <QDebug>
#include <QRandomGenerator>

SetCrewSizePage::SetCrewSizePage(QueueSystem *system, QWidget *parent)
    : QWidget(parent), queueSystem(system), crewSize(4) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top bar with Back button and Time
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    backButton = new QPushButton("Back");
    QLabel *timeLabel = new QLabel(QTime::currentTime().toString("hh:mm AP"));
    timeLabel->setAlignment(Qt::AlignRight);

    topBarLayout->addWidget(backButton);
    topBarLayout->addStretch();
    topBarLayout->addWidget(timeLabel);

    connect(backButton, &QPushButton::clicked, this, &SetCrewSizePage::backButtonClicked);
    mainLayout->addLayout(topBarLayout);

    // Bar widget details
    QVBoxLayout *barDetailsLayout = new QVBoxLayout();
    barImageLabel = new QLabel(this);
    barImageLabel->setPixmap(QPixmap(":/images/placeholder.jpg").scaled(200, 150, Qt::KeepAspectRatio));
    barDetailsLayout->addWidget(barImageLabel);

    barNameLabel = new QLabel("Bar Name");
    barStatusLabel = new QLabel("Status");
    barDetailsLabel = new QLabel("Details");
    barEventsLabel = new QLabel("Events");

    barNameLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFD700;");
    barStatusLabel->setStyleSheet("font-size: 14px; color: green;");
    barDetailsLabel->setStyleSheet("font-size: 12px; color: white;");
    barEventsLabel->setStyleSheet("font-size: 12px; color: #FFD700;");

    barDetailsLayout->setAlignment(Qt::AlignCenter);
    barDetailsLayout->addWidget(barNameLabel);
    barDetailsLayout->addWidget(barStatusLabel);
    barDetailsLayout->addWidget(barDetailsLabel);
    barDetailsLayout->addWidget(barEventsLabel);

    mainLayout->addLayout(barDetailsLayout);

    // Crew size display
    QLabel *questionLabel = new QLabel("How big is your crew?");
    questionLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    questionLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(questionLabel);

    QHBoxLayout *crewSizeLayout = new QHBoxLayout();
    QPushButton *decrementButton = new QPushButton("-");
    crewSizeLabel = new QLabel(QString::number(crewSize));
    QPushButton *incrementButton = new QPushButton("+");

    decrementButton->setStyleSheet("font-size: 24px; font-weight: bold; color: black;");
    incrementButton->setStyleSheet("font-size: 24px; font-weight: bold; color: black;");
    crewSizeLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: purple;");

    decrementButton->setFixedSize(50, 50);
    incrementButton->setFixedSize(50, 50);
    crewSizeLabel->setAlignment(Qt::AlignCenter);

    crewSizeLayout->addWidget(decrementButton);
    crewSizeLayout->addWidget(crewSizeLabel);
    crewSizeLayout->addWidget(incrementButton);
    mainLayout->addLayout(crewSizeLayout);

    // Join the Buzz button
    QPushButton *joinBuzzButton = new QPushButton("Join the Buzz");
    joinBuzzButton->setStyleSheet("font-size: 18px; font-weight: bold; background-color: purple; color: white;");
    mainLayout->addWidget(joinBuzzButton);

    mainLayout->addStretch();

    // Connect button signals
    connect(decrementButton, &QPushButton::clicked, this, &SetCrewSizePage::decrementCrewSize);
    connect(incrementButton, &QPushButton::clicked, this, &SetCrewSizePage::incrementCrewSize);
    connect(joinBuzzButton, &QPushButton::clicked, this, [this]() {
        if (queueSystem) {
            int userId = QRandomGenerator::global()->bounded(1000, 9999);  // Generate random User ID
            QString userName = "User_" + QString::number(userId);          // Generate User Name
            queueSystem->joinQueue(userId, userName, crewSize);           // Add to Queue
        }
        emit joinBuzzClicked();
    });
}

void SetCrewSizePage::updateBarDetails(const QString &name, const QString &status, const QString &details, const QString &events, const QString &imagePath) {
    barNameLabel->setText(name);
    barStatusLabel->setText(status);
    barDetailsLabel->setText(details);
    barEventsLabel->setText(events);

    if (!imagePath.isEmpty()) {
        QPixmap pixmap(imagePath);
        if (!pixmap.isNull()) {
            barImageLabel->setPixmap(pixmap.scaled(200, 150, Qt::KeepAspectRatio));
        }
    }
}

void SetCrewSizePage::incrementCrewSize() {
    crewSize++;
    crewSizeLabel->setText(QString::number(crewSize));
}

void SetCrewSizePage::decrementCrewSize() {
    if (crewSize > 1) {
        crewSize--;
        crewSizeLabel->setText(QString::number(crewSize));
    }
}
