#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <QTimer>
#include <QMutex>
#include <QString>

struct Node {
    int id;
    QString name;
    int groupSize;

    Node(int id, const QString &name, int groupSize) : id(id), name(name), groupSize(groupSize) {}
};

class QueueSystem : public QObject {
    Q_OBJECT

public:
    explicit QueueSystem(QObject *parent = nullptr);

    void joinQueue(int userId, const QString &userName, int groupSize);
    void removeUser(int userId);

signals:
    void userJoined(int userId, const QString &userName, int groupSize);
    void userRemoved(int userId);
    void userServed(int userId, const QString &userName, const QString &pin);

private slots:
    void serveNext();

private:
    QVector<QSharedPointer<Node>> queue;
    QTimer serveTimer;
    QMutex mutex;
    QString currentPin;

    QString generateRandomPin();
};

#endif // QUEUESYSTEM_H
