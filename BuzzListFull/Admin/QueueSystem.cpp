#include "QueueSystem.h"
#include <QRandomGenerator>

QueueSystem::QueueSystem(QObject *parent) : QObject(parent) {
    connect(&serveTimer, &QTimer::timeout, this, &QueueSystem::serveNext);
    serveTimer.start(15000); // Automatically serve every 15 seconds
}

void QueueSystem::joinQueue(int userId, const QString &userName, int groupSize) {
    QMutexLocker locker(&mutex);
    auto newUser = QSharedPointer<Node>::create(userId, userName, groupSize);
    queue.append(newUser); // Append the QSharedPointer to the queue
    emit userJoined(userId, userName, groupSize);
}

void QueueSystem::removeUser(int userId) {
    QMutexLocker locker(&mutex);
    for (int i = 0; i < queue.size(); ++i) {
        if (queue[i]->id == userId) {
            queue.removeAt(i);
            emit userRemoved(userId);
            return;
        }
    }
}

void QueueSystem::serveNext() {
    QMutexLocker locker(&mutex);
    if (!queue.isEmpty()) {
        auto servedUser = queue.takeFirst();
        currentPin = generateRandomPin(); // Generate a new pin for the user
        emit userServed(servedUser->id, servedUser->name, currentPin);
    } else {
        currentPin.clear(); // Clear the pin when the queue is empty
    }
}

QString QueueSystem::generateRandomPin() {
    int randomCode = QRandomGenerator::global()->bounded(1000, 10000); // Generate a 4-digit random number
    return QString::number(randomCode);
}
