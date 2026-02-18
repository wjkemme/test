#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;

class Calculator : public QWidget {
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);

private slots:
    void onButtonClicked();
    void onClear();
    void onEquals();

private:
    QLineEdit *display;
    void appendToDisplay(const QString &text);
};
