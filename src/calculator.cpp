#include "calculator.h"

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegularExpression>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMinimumHeight(40);

    QGridLayout *grid = new QGridLayout;
    QString buttons[4][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"}};

    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            QPushButton *b = new QPushButton(buttons[r][c], this);
            b->setMinimumSize(40, 40);

            // Style regular buttons with light blue
            if (buttons[r][c] != "=")
            {
                b->setStyleSheet("QPushButton { background-color: #ADD8E6; border: 1px solid #888; border-radius: 4px; font-weight: bold; }");
            }

            grid->addWidget(b, r, c);
            if (buttons[r][c] == "=")
            {
                b->setStyleSheet("QPushButton { background-color: black; color: white; border: 1px solid #888; border-radius: 4px; font-weight: bold; }");
                connect(b, &QPushButton::clicked, this, &Calculator::onEquals);
            }
            else
            {
                connect(b, &QPushButton::clicked, this, &Calculator::onButtonClicked);
            }
        }
    }

    QPushButton *clear = new QPushButton("C", this);
    clear->setStyleSheet("QPushButton { background-color: red; color: white; border: 1px solid #888; border-radius: 4px; font-weight: bold; }");
    connect(clear, &QPushButton::clicked, this, &Calculator::onClear);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(display);
    mainLayout->addLayout(grid);
    mainLayout->addWidget(clear);

    setLayout(mainLayout);
    setWindowTitle("Calculator");
    setFixedSize(240, 300);
}

void Calculator::appendToDisplay(const QString &text)
{
    display->setText(display->text() + text);
}

void Calculator::onButtonClicked()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    if (!b)
        return;
    appendToDisplay(b->text());
}

void Calculator::onClear()
{
    display->clear();
}

void Calculator::onEquals()
{
    QString expr = display->text();
    QRegularExpression re("^\\s*([0-9.+-/*\\s]+)\\s*$");
    if (!re.match(expr).hasMatch())
    {
        display->setText("Error");
        return;
    }

    QString s = expr;
    s.remove(' ');
    QList<QString> tokens;
    int i = 0;
    while (i < s.length())
    {
        QChar ch = s[i];
        if (ch.isDigit() || ch == '.')
        {
            int j = i;
            while (j < s.length() && (s[j].isDigit() || s[j] == '.'))
                ++j;
            tokens.append(s.mid(i, j - i));
            i = j;
        }
        else
        {
            tokens.append(QString(ch));
            ++i;
        }
    }

    QList<QString> pass1;
    for (int k = 0; k < tokens.size(); ++k)
    {
        QString t = tokens[k];
        if (t == "*" || t == "/")
        {
            double a = pass1.takeLast().toDouble();
            double b = tokens[++k].toDouble();
            double res = (t == "*") ? (a * b) : (a / b);
            pass1.append(QString::number(res, 'g', 12));
        }
        else
        {
            pass1.append(t);
        }
    }

    double result = pass1[0].toDouble();
    for (int k = 1; k < pass1.size(); k += 2)
    {
        QString op = pass1[k];
        double val = pass1[k + 1].toDouble();
        if (op == "+")
            result += val;
        else if (op == "-")
            result -= val;
        else
        {
            display->setText("Error");
            return;
        }
    }

    display->setText(QString::number(result, 'g', 12));
}
