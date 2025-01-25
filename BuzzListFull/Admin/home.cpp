#include "home.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QLinearGradient>
#include <QSpacerItem>


// Constructor
Home::Home(QWidget *parent)
    : QWidget(parent)
{
    // Set gradient background to dark grey
    QPalette palette;
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(50, 50, 50));  // Top: Dark Grey
    gradient.setColorAt(1, QColor(30, 30, 30));  // Bottom: Darker Grey
    palette.setBrush(QPalette::Window, QBrush(gradient));
    setAutoFillBackground(true);
    setPalette(palette);


    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    // Header
    QLabel *titleLabel = new QLabel("BuzzList");
    QFont titleFont("Arial", 24, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #FFD700;"); // Gold color for title
    mainLayout->addWidget(titleLabel);


    QLabel *welcomeLabel = new QLabel("Welcome Back Becca");
    welcomeLabel->setStyleSheet("font-size: 16px; font-weight: normal; color: #B0B0B0;"); // Light grey for welcome text
    welcomeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(welcomeLabel);


    QLabel *roleLabel = new QLabel("Stages Nightclub Bouncer");
    roleLabel->setStyleSheet("font-size: 16px; font-weight: normal; color: #B0B0B0;"); // Light grey for role text
    roleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(roleLabel);


    // Spacer above buttons
    mainLayout->addStretch();


    // Centered buttons
    QVBoxLayout *buttonLayout = new QVBoxLayout();


    QStringList buttonLabels = {"View/Edit the Queue", "Verify Codes"};
    for (const QString &text : buttonLabels) {
        QPushButton *button = new QPushButton(text);
        button->setStyleSheet(
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #6A1B9A, stop:1 #8E44AD);"
            "color: white; font-size: 16px; font-weight: bold; padding: 10px; border-radius: 8px;"
            ); // Purple gradient for buttons
        buttonLayout->addWidget(button);

        if (text == "Verify Codes") {
            connect(button, &QPushButton::clicked, this, &Home::switchTobarWorkerScan);
        }
        if (text == "View/Edit the Queue") {
            connect(button, &QPushButton::clicked, this, &Home::switchTobarWorkerQueue);
        }

    }


    // Add the buttons layout to the main layout
    mainLayout->addLayout(buttonLayout);


    // Logout label and button
    QLabel *logoutLabel = new QLabel("Want to log out?");
    logoutLabel->setStyleSheet("font-size: 14px; font-weight: normal; color: #B0B0B0;"); // Light grey for logout text
    logoutLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(logoutLabel);


    QPushButton *logoutButton = new QPushButton("Kill the Buzz");
    logoutButton->setStyleSheet(
        "background-color: #E74C3C; color: white; font-size: 16px; font-weight: bold; padding: 10px; border-radius: 8px;"
        ); // Red for logout button
    mainLayout->addWidget(logoutButton);


    // Spacer below buttons
    mainLayout->addStretch();


    setLayout(mainLayout);
}
