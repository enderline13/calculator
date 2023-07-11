#pragma once

#include <QtWidgets>
#include <QStack>
#include <QRegularExpression>

class Calculator : public QWidget
{
    Q_OBJECT
private:
    QLCDNumber* m_plcd;
    QStack<QString> m_stk;
    QString m_strDisplay;
public:
    Calculator(QWidget* pwgt = 0);
    QPushButton* createButton(const QString& str);
    void calculate();

protected:
    virtual void keyPressEvent(QKeyEvent* pe);

public slots:
    void slotButtonClicked();
};

