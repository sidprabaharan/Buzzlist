#ifndef USERPAGEMANAGER_H
#define USERPAGEMANAGER_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "searchbarspage.h"
#include "setcrewsizepage.h"
#include "waitingpage.h"
#include "Admin/QueueSystem.h"

class userPageManager : public QMainWindow {
    Q_OBJECT

public:
    explicit userPageManager(QueueSystem *system, QWidget *parent = nullptr);
    ~userPageManager();

    QStackedWidget *getStackedWidget() const;

private slots:
    void on_getBuzzedButton_clicked();
    void on_registerButton_clicked();
    void switchToProfilePage(const QString &username);
    void onSearchBarsButtonClicked();

public slots:
    void navigateToWaitingPage();

private:
    // UI Components
    QStackedWidget *stackedWidget;
    QLabel *buzzListLogo;
    QLabel *timeLabel;
    QLineEdit *emailInput;
    QLineEdit *passwordInput;
    QLabel *forgotPasswordLabel;
    QPushButton *registerButton;
    QPushButton *getBuzzedButton;
    QLabel *profileWelcomeLabel;

    QPushButton *staffButton;
    QPushButton *partyGoerButton;

    QPushButton *viewProfileButton;
    QPushButton *searchBarsButton;
    QPushButton *checkWaitButton;
    QPushButton *killBuzzButton;

    // Pages
    SearchBarsPage *searchBarsPage;
    SetCrewSizePage *setCrewSizePage;
    WaitingPage *waitingPage;

    // Helper functions
    void setupLoginPage();
    void setupProfilePage();
    void setupSearchBarsPage();
    void setupSetCrewSizePage();
    void setupWaitingPage();

    // Backend integration
    QueueSystem *queueSystem;  // Shared queue system
};

#endif // USERPAGEMANAGER_H
