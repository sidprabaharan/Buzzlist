#ifndef SEARCHBARSPAGE_H
#define SEARCHBARSPAGE_H

#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QString>
#include <qpushbutton.h>

// Forward declaration of ClickableWidget
class ClickableWidget;

class SearchBarsPage : public QWidget {
    Q_OBJECT

public:
    explicit SearchBarsPage(QWidget *parent = nullptr);

signals:
    void barClicked(const QString &name, const QString &status, const QString &details, const QString &events, const QString &imagePath);
    void backButtonClicked(); // Declare the signal here

private:
    QScrollArea *scrollArea;
    QVBoxLayout *barListLayout;
    QPushButton *backButton; // Add the back button here

    void createBarWidget(const QString &name, const QString &status, const QString &details, const QString &events, const QString &imagePath);
};

#endif // SEARCHBARSPAGE_H
