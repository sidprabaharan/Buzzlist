#include "codegenerationpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QLinearGradient>

// Constructor
CodeGenerationPage::CodeGenerationPage(const QString &pin, QWidget *parent)
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

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Header with back button
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QPushButton *backButton = new QPushButton("← Home");
    backButton->setStyleSheet("font-size: 20px; font-weight: bold; color: #FFFFFF; background: none; border: none;");
    headerLayout->addWidget(backButton);

    layout->addLayout(headerLayout);

    // Title
    QLabel *titleLabel = new QLabel("Your Code to Enter");
    QFont titleFont("Arial", 24, QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #FFD700;"); // Gold color for the title
    layout->addWidget(titleLabel);

    // Display the provided pin
    QLabel *codeLabel = new QLabel(pin);
    QFont codeFont("Arial", 48, QFont::Bold);
    codeLabel->setFont(codeFont);
    codeLabel->setAlignment(Qt::AlignCenter);
    codeLabel->setStyleSheet(
        "color: #FFFFFF; border: 3px solid #FFD700; border-radius: 10px; "
        "background-color: #2C2C2C; padding: 20px; margin: 20px;");
    layout->addWidget(codeLabel);

    // Instructions
    QLabel *instructionLabel = new QLabel("Show this code to the bouncer for verification.");
    instructionLabel->setStyleSheet("font-size: 16px; font-weight: normal; color: #B0B0B0;"); // Light grey for instructions
    instructionLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(instructionLabel);

    // Back button functionality
    connect(backButton, &QPushButton::clicked, this, &CodeGenerationPage::switchToHomePage);

    setLayout(layout);
}
