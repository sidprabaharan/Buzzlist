#include "Admin/adminPageManager.h"
#include "User/userPageManager.h"
#include "Admin/QueueSystem.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Create a shared QueueSystem instance for managing queues
    QueueSystem queueSystem;

    // Create and initialize the admin page manager window
    adminPageManager adminWindow(&queueSystem);
    adminWindow.show();

    // Create and initialize the user page manager window
    userPageManager userWindow(&queueSystem);
    userWindow.show();

    return a.exec();
}
