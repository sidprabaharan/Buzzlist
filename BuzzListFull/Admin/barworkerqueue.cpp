#include "barworkerqueue.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QFont>
#include <QPalette>
#include <QLinearGradient>

barWorkerQueue::barWorkerQueue(QWidget *parent)
    : QWidget(parent), queueSystem(nullptr) {
    // Set gradient background
    QPalette palette;
    QLinearGradient gradient(0, 0, 0, height());
    gradient.setColorAt(0, QColor(50, 50, 50));  // Dark Grey (top)
    gradient.setColorAt(1, QColor(30, 30, 30));  // Darker Grey (bottom)
    palette.setBrush(QPalette::Window, QBrush(gradient));
    setAutoFillBackground(true);
    setPalette(palette);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Header Section
    QHBoxLayout *headerLayout = new QHBoxLayout();
    QPushButton *backButton = new QPushButton("← Back");
    backButton->setStyleSheet("font-size: 16px; font-weight: bold; color: #FFFFFF; background: none; border: none;");
    headerLayout->addWidget(backButton);
    headerLayout->addStretch();

    QLabel *titleLabel = new QLabel("Manage The BuzzList");
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #FFD700;");
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    mainLayout->addLayout(headerLayout);

    // Queue Display Section
    queueLabel = new QLabel("Now Serving: None");
    queueLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: white;");
    mainLayout->addWidget(queueLabel);

    pinLabel = new QLabel("Pin: N/A");
    pinLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #FFD700;");
    mainLayout->addWidget(pinLabel);

    queueList = new QListWidget();
    queueList->setStyleSheet(
        "QListWidget {"
        "   background: #333333; border: 2px solid #FFD700; border-radius: 10px; padding: 10px;"
        "   font-size: 16px; color: white; }"
        "QListWidget::item { margin: 10px; padding: 10px; border: 1px solid #FFD700; border-radius: 5px;"
        "   background-color: #444444; color: white; }"
        "QListWidget::item:selected { background-color: #666666; color: white; }");
    mainLayout->addWidget(queueList);

    // Add User Section
    QLabel *addUserLabel = new QLabel("Add User:");
    addUserLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    mainLayout->addWidget(addUserLabel);

    QHBoxLayout *addUserLayout = new QHBoxLayout();
    QLineEdit *userIdInput = new QLineEdit();
    userIdInput->setPlaceholderText("User ID");
    userIdInput->setStyleSheet("background-color: white; color: black; padding: 5px; border-radius: 5px;");

    QLineEdit *userNameInput = new QLineEdit();
    userNameInput->setPlaceholderText("User Name");
    userNameInput->setStyleSheet("background-color: white; color: black; padding: 5px; border-radius: 5px;");

    QLineEdit *groupSizeInput = new QLineEdit();
    groupSizeInput->setPlaceholderText("Group Size");
    groupSizeInput->setStyleSheet("background-color: white; color: black; padding: 5px; border-radius: 5px;");

    QPushButton *addUserButton = new QPushButton("Add User");
    addUserButton->setStyleSheet(
        "background-color: #4CAF50; color: white; font-size: 16px; font-weight: bold; padding: 8px 12px; border-radius: 5px;");
    addUserLayout->addWidget(userIdInput);
    addUserLayout->addWidget(userNameInput);
    addUserLayout->addWidget(groupSizeInput);
    addUserLayout->addWidget(addUserButton);
    mainLayout->addLayout(addUserLayout);

    // Remove User Section
    QLabel *removeUserLabel = new QLabel("Remove User:");
    removeUserLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: white;");
    mainLayout->addWidget(removeUserLabel);

    QHBoxLayout *removeUserLayout = new QHBoxLayout();
    QLineEdit *removeUserIdInput = new QLineEdit();
    removeUserIdInput->setPlaceholderText("User ID");
    removeUserIdInput->setStyleSheet("background-color: white; color: black; padding: 5px; border-radius: 5px;");

    QPushButton *removeUserButton = new QPushButton("Remove User");
    removeUserButton->setStyleSheet(
        "background-color: #FF4500; color: white; font-size: 16px; font-weight: bold; padding: 8px 12px; border-radius: 5px;");
    removeUserLayout->addWidget(removeUserIdInput);
    removeUserLayout->addWidget(removeUserButton);
    mainLayout->addLayout(removeUserLayout);

    setLayout(mainLayout);

    // Connect signals and slots
    connect(backButton, &QPushButton::clicked, this, &barWorkerQueue::switchToHomePage);

    connect(addUserButton, &QPushButton::clicked, [=]() {
        if (queueSystem) {
            bool idOk, groupOk;
            int userId = userIdInput->text().toInt(&idOk);
            QString userName = userNameInput->text();
            int groupSize = groupSizeInput->text().toInt(&groupOk);

            if (idOk && !userName.isEmpty() && groupOk && groupSize > 0) {
                queueSystem->joinQueue(userId, userName, groupSize);
                userIdInput->clear();
                userNameInput->clear();
                groupSizeInput->clear();
            }
        }
    });

    connect(removeUserButton, &QPushButton::clicked, [=]() {
        if (queueSystem) {
            bool idOk;
            int userId = removeUserIdInput->text().toInt(&idOk);

            if (idOk) {
                queueSystem->removeUser(userId);
                removeUserIdInput->clear();
            }
        }
    });
}

void barWorkerQueue::setQueueSystem(QueueSystem *system) {
    queueSystem = system;

    // Connect QueueSystem signals to slots
    connect(queueSystem, &QueueSystem::userJoined, this, &barWorkerQueue::onUserJoined);
    connect(queueSystem, &QueueSystem::userServed, this, &barWorkerQueue::onUserServed);
    connect(queueSystem, &QueueSystem::userRemoved, this, &barWorkerQueue::onUserRemoved);
}

void barWorkerQueue::onUserJoined(int userId, const QString &userName, int groupSize) {
    QListWidgetItem *item = new QListWidgetItem(queueList);
    item->setText(QString("ID: %1 | Name: %2 | Group Size: %3").arg(userId).arg(userName).arg(groupSize));
    item->setFont(QFont("Arial", 14, QFont::Bold));
}

void barWorkerQueue::onUserServed(int userId, const QString &userName, const QString &pin) {
    queueLabel->setText(QString("Now Serving: %1").arg(userName.isEmpty() ? "None" : userName));
    pinLabel->setText(QString("Pin: %1").arg(pin));
    if (queueList->count() > 0) {
        delete queueList->takeItem(0);
    } else {
        pinLabel->setText("Pin: N/A");
    }
}

void barWorkerQueue::onUserRemoved(int userId) {
    for (int i = 0; i < queueList->count(); ++i) {
        if (queueList->item(i)->text().contains(QString("ID: %1").arg(userId))) {
            delete queueList->takeItem(i);
            break;
        }
    }
}
