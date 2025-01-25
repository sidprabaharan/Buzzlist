#ifndef HOME_H
#define HOME_H


#include <QWidget>


class Home : public QWidget
{
    Q_OBJECT


public:
    explicit Home(QWidget *parent = nullptr);


signals:
    void switchTobarWorkerScan();
    void switchTobarWorkerQueue();


};


#endif // HOME_H
