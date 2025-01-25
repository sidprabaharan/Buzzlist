#ifndef CODEGENERATIONPAGE_H
#define CODEGENERATIONPAGE_H

#include <QWidget>

class CodeGenerationPage : public QWidget {
    Q_OBJECT

public:
    explicit CodeGenerationPage(const QString &pin, QWidget *parent = nullptr); // Constructor accepts pin
    ~CodeGenerationPage() = default;

signals:
    void switchToHomePage(); // Signal to navigate back to the home page
};

#endif // CODEGENERATIONPAGE_H
