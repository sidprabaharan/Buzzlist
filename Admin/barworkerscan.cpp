#include "barworkerscan.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QLinearGradient>

barWorkerScan::barWorkerScan(QWidget *parent)
    : QWidget(parent), queueSystem(nullptr) // Initialize with null
{
    // Set gradient background to dark grey
    QPalette palette;
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(50, 50, 50));  // Top: Dark Grey
    gradient.setColorAt(1, QColor(30, 30, 30));  // Bottom: Darker Grey
    palette.setBrush(QPalette::Window, QBrush(gradient));
    setAutoFillBackground(true);
    setPalette(palette);

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Header with back button
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QPushButton *backButton = new QPushButton("← Home");
    backButton->setStyleSheet("font-size: 20px; font-weight: bold; color: #FFFFFF; background: none; border: none;");
    headerLayout->addWidget(backButton);
    headerLayout->addStretch();

    layout->addLayout(headerLayout);

    QLabel *instructionLabel = new QLabel("Enter a user's code below for verification.");
    instructionLabel->setStyleSheet("font-size: 14px; font-weight: normal; color: #B0B0B0;"); // Light grey for instructions
    instructionLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(instructionLabel);

    // Input field for the code
    QLineEdit *codeInput = new QLineEdit();
    codeInput->setPlaceholderText("Enter code here...");
    codeInput->setStyleSheet(
        "font-size: 16px; padding: 8px; border: 2px solid #FFD700; border-radius: 8px; color: white; "
        "background-color: #2C2C2C;" // Dark grey background
        );
    layout->addWidget(codeInput);

    // Verification button
    QPushButton *verifyButton = new QPushButton("Verify Code");
    verifyButton->setStyleSheet(
        "background-color: #6A1B9A; color: white; font-size: 16px; font-weight: bold; padding: 10px; border-radius: 8px;"
        ); // Purple gradient for button
    layout->addWidget(verifyButton);

    // Result label for verification outcome
    QLabel *resultLabel = new QLabel();
    resultLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: white; margin-top: 10px;");
    resultLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(resultLabel);

    // Signal-slot connection for verification logic
    connect(verifyButton, &QPushButton::clicked, [this, codeInput, resultLabel]() {
        QString inputCode = codeInput->text();

        if (queueSystem && inputCode == currentPin) { // Compare with the actual pin
            resultLabel->setText("Code Verified!");
            resultLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #00FF00;"); // Green for success
        } else {
            resultLabel->setText("Invalid Code.");
            resultLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #FF0000;"); // Red for failure
        }
    });

    // Connect back button to signal for navigating to the home page
    connect(backButton, &QPushButton::clicked, this, &barWorkerScan::switchToHomePage);

    setLayout(layout);
}

// Method to update the pin dynamically
void barWorkerScan::setQueueSystem(QueueSystem *system) {
    queueSystem = system;

    // Connect to the userServed signal to update the currentPin
    connect(queueSystem, &QueueSystem::userServed, this, [this](int userId, const QString &userName, const QString &pin) {
        currentPin = pin; // Update the current pin for verification
    });
}
