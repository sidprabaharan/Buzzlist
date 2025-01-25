#include "waitingpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QTime>

WaitingPage::WaitingPage(QWidget *parent)
    : QWidget(parent), remainingMinutes(2) {

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top Bar with "Leave" Text and Time
    QHBoxLayout *topBar = new QHBoxLayout;
    QLabel *leaveLabel = new QLabel("← Leave");
    timeLabel = new QLabel();
    leaveLabel->setAlignment(Qt::AlignLeft);
    timeLabel->setAlignment(Qt::AlignRight);
    topBar->addWidget(leaveLabel);
    topBar->addStretch();
    topBar->addWidget(timeLabel);

    leaveLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: black;");
    timeLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: black;");
    mainLayout->addLayout(topBar);

    // Status Box
    QLabel *statusLabel = new QLabel("You're on the <i>BuzzList</i>");
    statusLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #F39C12; border: 2px solid #800080; padding: 5px; border-radius: 15px; background-color: #F2F2F2; margin: 10px;");
    statusLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(statusLabel);

    QLabel *pplRemaining = new QLabel("There are 24 BeeHives ahead of you...");
    pplRemaining->setStyleSheet("font-size: 16px; color: black; margin: 15px auto;");
    pplRemaining->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(pplRemaining);

    // Countdown Timer
    timeRemaining = new QLabel();
    timeRemaining->setAlignment(Qt::AlignCenter);
    timeRemaining->setStyleSheet(
        "font-size: 36px; font-weight: bold; color: white;"
        "background: qradialgradient(cx:0.5, cy:0.5, radius: 0.5, fx:0.5, fy:0.5, "
        "stop:0 #FF5733, stop:1 #900C3F);"
        "border: 3px solid black; border-radius: 50px; padding: 10px; margin: 20px auto;"
        );
    mainLayout->addWidget(timeRemaining);

    // Party Info
    partyLabel = new QLabel("You are in line with a group of 4");
    partyLabel->setStyleSheet("font-size: 20px; color: black; font-weight: bold; margin: 10px auto");
    partyLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(partyLabel);

    setLayout(mainLayout);

    // Initialize timers and countdown
    eta = QTime::currentTime().addSecs(remainingMinutes * 60);
    updateCountdown();
    updateTimeLabel();

    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &WaitingPage::updateCountdown);
    countdownTimer->start(60000); // 60 seconds

    timeUpdateTimer = new QTimer(this);
    connect(timeUpdateTimer, &QTimer::timeout, this, &WaitingPage::updateTimeLabel);
    timeUpdateTimer->start(1000); // 1 second
}

void WaitingPage::updateCountdown() {
    if (remainingMinutes > 0) {
        remainingMinutes--;
        QTime updatedEta = QTime::currentTime().addSecs(remainingMinutes * 60);
        timeRemaining->setText(QString("%1 Minutes\nETA %2")
                                   .arg(remainingMinutes)
                                   .arg(updatedEta.toString("hh:mm AP")));
    } else {
        timeRemaining->setText("Arrived!");
    }
}

void WaitingPage::updateTimeLabel() {
    timeLabel->setText(QTime::currentTime().toString("hh:mm AP"));
}

void WaitingPage::updatePin(const QString &pin) {
    timeRemaining->setText(QString("Your Pin: %1").arg(pin));
}
