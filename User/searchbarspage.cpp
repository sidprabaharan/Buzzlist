#include "searchbarspage.h"
#include "clickablewidget.h"
#include <QHBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>

#include <QScrollArea>
#include <QVBoxLayout>


SearchBarsPage::SearchBarsPage(QWidget *parent)
    : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Top bar layout
    QHBoxLayout *topBarLayout = new QHBoxLayout();
    backButton = new QPushButton("← Back"); // Initialize back button
    backButton->setStyleSheet("font-size: 16px; font-weight: bold; color: white; background-color: #800080; border: none; border-radius: 5px; padding: 5px 10px;");
    backButton->setFixedSize(100, 30);

    connect(backButton, &QPushButton::clicked, this, &SearchBarsPage::backButtonClicked); // Emit signal on click

    topBarLayout->addWidget(backButton);
    topBarLayout->addStretch();

    mainLayout->addLayout(topBarLayout);

    QLabel *title = new QLabel("Search Bars");
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFD700;");
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    scrollArea = new QScrollArea(this);
    QWidget *scrollContent = new QWidget(scrollArea);
    barListLayout = new QVBoxLayout(scrollContent);
    barListLayout->setContentsMargins(0, 0, 0, 0);
    barListLayout->setSpacing(10);

    scrollContent->setLayout(barListLayout);
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // Example bars
    createBarWidget("Trinity Social", "Open Tonight", "424 Princess St, Kingston, ON\nPop • $ • 42min Wait • $10 Entry", "Events: Dollar Beers", ":/images/trinity_social.jpg");
    createBarWidget("Stages Nightclub", "Open Tonight", "390 Princess St, Kingston, ON\nEDM • $$ • 21min Wait • $20 Entry", "Events: Loud Luxury", ":/images/stages_nightclub.jpg");

    setLayout(mainLayout);
}


void SearchBarsPage::createBarWidget(const QString &name, const QString &status, const QString &details, const QString &events, const QString &imagePath) {
    // Create the container widget (using ClickableWidget)
    ClickableWidget *barWidget = new ClickableWidget(this); // Initialize barWidget here
    barWidget->setStyleSheet("background-color: white; border: 3px solid #800080; border-radius: 10px; padding: 10px;");
    barWidget->setFixedSize(400, 220);

    // Layout and style logic
    QVBoxLayout *barLayout = new QVBoxLayout(barWidget);

    // Top Section: Image and Name
    QHBoxLayout *topLayout = new QHBoxLayout();
    QLabel *imageLabel = new QLabel(this);
    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("Image not available");
    }
    imageLabel->setFixedSize(120, 120);
    imageLabel->setStyleSheet("border-radius: 10px;");
    topLayout->addWidget(imageLabel);

    QVBoxLayout *nameStatusLayout = new QVBoxLayout();
    QLabel *nameLabel = new QLabel(name);
    QLabel *statusLabel = new QLabel(status);

    nameLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #FFA500;");
    statusLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: green;");
    nameStatusLayout->addWidget(nameLabel);
    nameStatusLayout->addWidget(statusLabel);
    topLayout->addLayout(nameStatusLayout);

    barLayout->addLayout(topLayout);

    // Details Section
    QLabel *detailsLabel = new QLabel(details);
    detailsLabel->setStyleSheet("font-size: 12px; color: black;");
    detailsLabel->setAlignment(Qt::AlignLeft);
    detailsLabel->setWordWrap(true);
    barLayout->addWidget(detailsLabel);

    // Events Section
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QLabel *eventsLabel = new QLabel(events);
    eventsLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #800080;");
    bottomLayout->addWidget(eventsLabel);

    barLayout->addLayout(bottomLayout);

    // Add the bar widget to the main layout
    barListLayout->addWidget(barWidget);

    // Add clickable functionality
    connect(barWidget, &ClickableWidget::clicked, this, [this, name, status, details, events, imagePath]() {
        emit barClicked(name, status, details, events, imagePath);
    });
}


