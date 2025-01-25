#ifndef ADMINPAGEMANAGER_H
#define ADMINPAGEMANAGER_H

#include <QWidget>
#include <QStackedWidget>

class QueueSystem;
class Home;
class barWorkerQueue;
class barWorkerScan;

class adminPageManager : public QWidget {
    Q_OBJECT

public:
    explicit adminPageManager(QueueSystem *system, QWidget *parent = nullptr);

private:
    QStackedWidget *stackedWidget;
    QueueSystem *queueSystem;
};

#endif // ADMINPAGEMANAGER_H
