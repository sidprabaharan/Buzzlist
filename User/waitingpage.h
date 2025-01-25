#ifndef WAITINGPAGE_H
#define WAITINGPAGE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>

class WaitingPage : public QWidget {
    Q_OBJECT

public:
    explicit WaitingPage(QWidget *parent = nullptr);
    void updatePin(const QString &pin); // Updates pin when ready
    void updatePartySize(const QString &details);

private slots:
    void updateCountdown();
    void updateTimeLabel();

private:
    QLabel *timeLabel;
    QLabel *timeRemaining;
    QLabel *partyLabel;
    QTimer *countdownTimer;
    QTimer *timeUpdateTimer;
    QTime eta;
    int remainingMinutes;
};

#endif // WAITINGPAGE_H
