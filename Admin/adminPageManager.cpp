#include "adminPageManager.h"
#include "barworkerqueue.h"
#include "barworkerscan.h"
#include "home.h"
#include "QueueSystem.h"
#include <QtWidgets/QVBoxLayout>

adminPageManager::adminPageManager(QueueSystem *system, QWidget *parent)
    : QWidget(parent), queueSystem(system) {

    // Create the stacked widget
    stackedWidget = new QStackedWidget(this);

    // Create pages
    Home *homePage = new Home();
    barWorkerQueue *queuePage = new barWorkerQueue();
    barWorkerScan *scanPage = new barWorkerScan();

    // Pass QueueSystem to pages
    queuePage->setQueueSystem(queueSystem);
    scanPage->setQueueSystem(queueSystem);

    // Add pages to the stacked widget
    stackedWidget->addWidget(homePage);
    stackedWidget->addWidget(queuePage);
    stackedWidget->addWidget(scanPage);

    // Set initial page
    stackedWidget->setCurrentWidget(homePage);

    // Connect signals for navigation
    connect(homePage, &Home::switchTobarWorkerScan, [this, scanPage]() {
        stackedWidget->setCurrentWidget(scanPage);
    });
    connect(scanPage, &barWorkerScan::switchToHomePage, [this, homePage]() {
        stackedWidget->setCurrentWidget(homePage);
    });
    connect(homePage, &Home::switchTobarWorkerQueue, [this, queuePage]() {
        stackedWidget->setCurrentWidget(queuePage);
    });
    connect(queuePage, &barWorkerQueue::switchToHomePage, [this, homePage]() {
        stackedWidget->setCurrentWidget(homePage);
    });

    // Set layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(stackedWidget);
    setLayout(layout);
}
