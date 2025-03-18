#include "keylineedit.h"
#include <QDebug>

KeyLineEdit::KeyLineEdit(QWidget *parent) : QLineEdit(parent), _modifiers(Qt::NoModifier)
{
    setReadOnly(true);
    resetCombo();
}

void KeyLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }

    _modifiers = event->modifiers();

    int key = event->key();
    if (key != Qt::Key_Control && key != Qt::Key_Shift && key != Qt::Key_Alt && key != Qt::Key_Meta) {
        if (!_pressedKeys.contains(key)) {
            _pressedKeys.append(key);
        }
    }

    updateDisplay();
}

void KeyLineEdit::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        return;
    }

    int key = event->key();
    _pressedKeys.removeAll(key);

    if (_pressedKeys.isEmpty()) {
        _modifiers = Qt::NoModifier;
        resetCombo();
    }

    updateDisplay();
}

void KeyLineEdit::resetCombo()
{
    _currentCombo.clear();
    _pressedKeys.clear();
    _modifiers = Qt::NoModifier;
    setText("");
}

void KeyLineEdit::updateDisplay()
{
    QString combo;

    if (_modifiers & Qt::ControlModifier) {
        combo += "Ctrl+";
    }
    if (_modifiers & Qt::ShiftModifier) {
        combo += "Shift+";
    }
    if (_modifiers & Qt::AltModifier) {
        combo += "Alt+";
    }
    if (_modifiers & Qt::MetaModifier) {
        combo += "Meta+";
    }

    for (int key : _pressedKeys) {
        QString keyString = QKeySequence(key).toString(QKeySequence::NativeText);
        if (!keyString.isEmpty()) {
            combo += keyString + "+";
        } else {
            qDebug() << "Unknown key code:" << key;
            combo += "Unknown+";
        }
    }

    if (!combo.isEmpty() && combo.endsWith("+")) {
        combo.chop(1);
    }

    if (combo != _currentCombo && !combo.isEmpty()) {
        _currentCombo = combo;
        setText(_currentCombo);
    }
}
