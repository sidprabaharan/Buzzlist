#include "userPageManager.h"
#include "backend.h"
#include "setcrewsizepage.h"
#include <QMessageBox>
#include <QDateTime>
#include "waitingpage.h"

userPageManager::userPageManager(QueueSystem *system, QWidget *parent)
    : QMainWindow(parent), queueSystem(system) {

    // Create the stacked widget to switch between pages
    stackedWidget = new QStackedWidget(this);

    // Initialize and set up all pages
    setupLoginPage();
    setupProfilePage();
    setupSetCrewSizePage();
    setupSearchBarsPage();
    setupWaitingPage();

    // Set the stacked widget as the central widget of the main window
    setCentralWidget(stackedWidget);

    // Start on the login page
    stackedWidget->setCurrentIndex(0);

    // Connect QueueSystem to WaitingPage for PIN updates
    connect(queueSystem, &QueueSystem::userServed, this, [this](int, const QString &, const QString &pin) {
        this->waitingPage->updatePin(pin);
    });
}

userPageManager::~userPageManager() {
    // No need to manually delete child widgets as Qt handles it automatically
}

void userPageManager::setupLoginPage() {
    // Create the login page layout
    QWidget *loginPage = new QWidget;
    QVBoxLayout *loginLayout = new QVBoxLayout(loginPage);

    // Logo and time label
    QLabel *buzzListLogo = new QLabel("BuzzList", this);
    buzzListLogo->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFD700;");
    QLabel *timeLabel = new QLabel(QDateTime::currentDateTime().toString("dddd, MMMM d\nhh:mm AP"), this);
    timeLabel->setStyleSheet("font-size: 18px; color: white;");

    loginLayout->addWidget(buzzListLogo, 0, Qt::AlignCenter);
    loginLayout->addWidget(timeLabel, 0, Qt::AlignCenter);

    // Role selection buttons
    QPushButton *staffButton = new QPushButton("Bar Staff/Admin", this);
    QPushButton *partyGoerButton = new QPushButton("Party-goer", this);
    staffButton->setStyleSheet("background-color: #8E24AA; color: white; font-weight: bold; border-radius: 10px; padding: 10px;");
    partyGoerButton->setStyleSheet("background-color: #8E24AA; color: white; font-weight: bold; border-radius: 10px; padding: 10px;");

    loginLayout->addWidget(staffButton);
    loginLayout->addWidget(partyGoerButton);

    // Email and password input fields
    emailInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);
    emailInput->setPlaceholderText("Email");
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    emailInput->setStyleSheet("background-color: #333333; color: white; border-radius: 10px; padding: 5px;");
    passwordInput->setStyleSheet("background-color: #333333; color: white; border-radius: 10px; padding: 5px;");

    loginLayout->addWidget(emailInput);
    loginLayout->addWidget(passwordInput);

    // Forgot password label
    QLabel *forgotPasswordLabel = new QLabel("<a href=\"#\">Forgot your password?</a>", this);
    forgotPasswordLabel->setStyleSheet("color: #B0BEC5; text-decoration: underline;");
    forgotPasswordLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    forgotPasswordLabel->setOpenExternalLinks(true);
    loginLayout->addWidget(forgotPasswordLabel, 0, Qt::AlignCenter);

    // Register and login buttons
    registerButton = new QPushButton("Register as New User", this);
    getBuzzedButton = new QPushButton("Get Buzzed", this);
    registerButton->setStyleSheet("background-color: #5C6BC0; color: white; font-weight: bold; border-radius: 10px; padding: 10px;");
    getBuzzedButton->setStyleSheet("background-color: #FFD700; color: #333333; font-weight: bold; border-radius: 10px; padding: 10px;");

    loginLayout->addWidget(registerButton);
    loginLayout->addWidget(getBuzzedButton);

    // Connect buttons to slots
    connect(getBuzzedButton, &QPushButton::clicked, this, &userPageManager::on_getBuzzedButton_clicked);
    connect(registerButton, &QPushButton::clicked, this, &userPageManager::on_registerButton_clicked);

    // Add the login page to the stacked widget
    stackedWidget->addWidget(loginPage);
}

void userPageManager::setupProfilePage() {
    // Create the profile page layout
    QWidget *profilePage = new QWidget;
    QVBoxLayout *profileLayout = new QVBoxLayout(profilePage);

    // Welcome label with user name
    profileWelcomeLabel = new QLabel("Welcome Back, [Username]", this);
    profileWelcomeLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: white;");
    profileWelcomeLabel->setAlignment(Qt::AlignCenter);
    profileLayout->addWidget(profileWelcomeLabel);

    // Sub-header label
    QLabel *waitlistLabel = new QLabel("You are currently in 1 waitlist", this);
    waitlistLabel->setStyleSheet("font-size: 14px; color: white;");
    waitlistLabel->setAlignment(Qt::AlignCenter);
    profileLayout->addWidget(waitlistLabel);

    // Profile action buttons
    QPushButton *viewProfileButton = new QPushButton("View/Edit Profile", this);
    searchBarsButton = new QPushButton("Search Bars", this);
    QPushButton *checkWaitButton = new QPushButton("Check the Wait", this);
    QPushButton *killBuzzButton = new QPushButton("Kill the Buzz", this);

    QString buttonStyle = "background-color: #8E24AA; color: white; font-weight: bold; border-radius: 10px; padding: 12px;";
    viewProfileButton->setStyleSheet(buttonStyle);
    searchBarsButton->setStyleSheet(buttonStyle);
    checkWaitButton->setStyleSheet(buttonStyle);
    killBuzzButton->setStyleSheet("background-color: #FF5252; color: white; font-weight: bold; border-radius: 10px; padding: 12px;");

    profileLayout->addSpacing(20);
    profileLayout->addWidget(viewProfileButton);
    profileLayout->addWidget(searchBarsButton);
    profileLayout->addWidget(checkWaitButton);
    profileLayout->addWidget(killBuzzButton);
    profileLayout->addSpacing(20);

    // Connect the logout function to "Kill the Buzz" button
    connect(killBuzzButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0); // Return to login page
        emailInput->clear();
        passwordInput->clear();
    });

    // Connect Search Bars button
    connect(searchBarsButton, &QPushButton::clicked, this, &userPageManager::onSearchBarsButtonClicked);

    // Add the profile page to the stacked widget
    stackedWidget->addWidget(profilePage);
}

void userPageManager::on_getBuzzedButton_clicked() {
    QString email = emailInput->text();
    QString password = passwordInput->text();

    if (userExists(email.toStdString(), password.toStdString())) {
        switchToProfilePage(email);
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials. Please try again.");
    }
}

void userPageManager::on_registerButton_clicked() {
    QString email = emailInput->text();
    QString password = passwordInput->text();

    if (registerUser(email.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Registration Successful", "User registered successfully!");
    } else {
        QMessageBox::warning(this, "Registration Failed", "User already exists.");
    }
}

void userPageManager::switchToProfilePage(const QString &username) {
    profileWelcomeLabel->setText("Welcome Back, " + username);
    stackedWidget->setCurrentIndex(1);
}

void userPageManager::onSearchBarsButtonClicked() {
    stackedWidget->setCurrentWidget(searchBarsPage);
}

void userPageManager::setupSetCrewSizePage() {
    setCrewSizePage = new SetCrewSizePage(queueSystem, this); // Pass QueueSystem
    stackedWidget->addWidget(setCrewSizePage);

    connect(setCrewSizePage, &SetCrewSizePage::joinBuzzClicked, this, &userPageManager::navigateToWaitingPage);
    connect(setCrewSizePage, &SetCrewSizePage::backButtonClicked, this, [this]() {
        stackedWidget->setCurrentWidget(searchBarsPage); // Navigate to SearchBarsPage
    });
}

void userPageManager::setupSearchBarsPage() {
    searchBarsPage = new SearchBarsPage(this);
    stackedWidget->addWidget(searchBarsPage);

    connect(searchBarsPage, &SearchBarsPage::barClicked, this, [this](const QString &name, const QString &status, const QString &details, const QString &events, const QString &imagePath) {
        setCrewSizePage->updateBarDetails(name, status, details, events, imagePath);
        stackedWidget->setCurrentWidget(setCrewSizePage);
    });

    connect(searchBarsPage, &SearchBarsPage::backButtonClicked, this, [this]() {
        stackedWidget->setCurrentIndex(1); // Navigate to Profile Page
    });
}

void userPageManager::setupWaitingPage() {
    waitingPage = new WaitingPage(this); // Initialize waitingPage
    stackedWidget->addWidget(waitingPage); // Add it to the stack
}

void userPageManager::navigateToWaitingPage() {
    stackedWidget->setCurrentWidget(waitingPage); // Switch to Waiting Page
}

QStackedWidget* userPageManager::getStackedWidget() const {
    return stackedWidget;
}
