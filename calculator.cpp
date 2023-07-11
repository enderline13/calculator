#include "calculator.h"

const QRegularExpression& getRegex()
{
    static const QRegularExpression regex("[0-9]");
    return regex;
}

Calculator::Calculator(QWidget* pwgt) : QWidget(pwgt)
{
    m_plcd = new QLCDNumber(12);
    m_plcd->setSegmentStyle(QLCDNumber::Flat);
    m_plcd->setMinimumSize(150, 50);
    m_plcd->setMaximumHeight(50);
    QString aButtons[5][4] = { { "1/x", "x^2", "root", "/"},
                             { "7", "8", "9", "*"},
                             { "4", "5", "6", "-"},
                             { "1", "2", "3", "+"},
                             { "-x", "0", ".", "="} };
//Layout setup
    QGridLayout* ptopLayout = new QGridLayout;
    ptopLayout->setSpacing(0);
    ptopLayout->addWidget(m_plcd, 0, 0, 1, 4);
    ptopLayout->addWidget(createButton("CE"), 1, 1);
    ptopLayout->addWidget(createButton("%"), 1, 0);
    ptopLayout->addWidget(createButton("C"), 1, 2);
    ptopLayout->addWidget(createButton("Back"), 1, 3);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j)
        ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
        setLayout(ptopLayout);
    }
   //  QPalette pal = this->palette();
   //  pal.setBrush(QPalette::Button, QBrush(Qt::black));
   // this->setPalette(pal);
}

QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, &QPushButton::clicked, this, &Calculator::slotButtonClicked);
    return pcmd;
}

void Calculator::calculate()
{
    qreal fOperand2 = m_stk.pop().toFloat();
    QString strOperation = m_stk.pop();
    qreal fOperandl = m_stk.pop().toFloat();
    qreal fResult = 0;
    if (strOperation == "+") {
        fResult = fOperandl + fOperand2;
    }
    else if (strOperation == "-") {
        fResult = fOperandl - fOperand2;
    }
    else if (strOperation == "/") {
        fResult = fOperandl / fOperand2;
        }
    else {
        fResult = fOperandl * fOperand2;
    }
    m_plcd->display(fResult);
}

void Calculator::slotButtonClicked() {
    QString str = ((QPushButton*)sender())->text();

    if (str == "C") {
        m_stk.clear();
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if (str == "CE") {
        m_strDisplay = "";
        m_plcd->display("0");
        return;
    }
    if (str == "1/x") {
        double real = 1 / (m_plcd->value());
        m_strDisplay = QString::number(real);
        m_plcd->display(m_strDisplay);
        return;
    }
    if (str == "x^2") {
        double real = pow(m_plcd->value(), 2);
        m_strDisplay = QString::number(real);
        m_plcd->display(m_strDisplay);
        return;
    }
    if (str == "Back") {
        m_strDisplay.removeLast();
        m_plcd->display(m_strDisplay);
        return;
    }
    if (str == "root") {
        double real = sqrt(m_plcd->value());
        m_strDisplay = QString::number(real);
        m_plcd->display(m_strDisplay);
        return;
    }
    if (str == "-x") {
        double temp = -m_plcd->value();
        m_strDisplay = QString::number(temp);
        m_plcd->display(m_strDisplay);
        return;
    }
    if (str.contains(getRegex())) {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
    else if (str == ".") {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay);
    }
    else {
        if (m_stk.count() >= 2) {
            m_stk.push(QString().setNum(m_plcd->value()));
            calculate();
            m_stk.clear();
            m_strDisplay = "";
            m_stk.push(QString().setNum(m_plcd->value()));
            if (str != "=") {
                m_stk.push(str);
            }
        }
        else {
            m_stk.push(QString().setNum(m_plcd->value()));
            m_stk.push(str);
            m_strDisplay = "";
        }
    }
}

void Calculator::keyPressEvent(QKeyEvent* pe) {
    QString str = pe->text();
    if(str.contains(getRegex())) {
        m_strDisplay += str;
        m_plcd->display(m_strDisplay.toDouble());
    }
}
