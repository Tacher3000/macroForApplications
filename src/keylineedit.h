#ifndef KEYLINEEDIT_H
#define KEYLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>
// #include <QWidget>

class KeyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    KeyLineEdit(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void resetCombo();

private:
    void updateDisplay();

    QList<int> _pressedKeys;
    QString _currentCombo;
};

#endif // KEYLINEEDIT_H
