#include "keylineedit.h"

KeyLineEdit::KeyLineEdit(QWidget *parent) : QLineEdit(parent) {
    setReadOnly(true);
}

void KeyLineEdit::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        _pressedKeys.append(event->key());
        updateDisplay();
    }
}

void KeyLineEdit::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        _pressedKeys.removeAll(event->key());
        if (_pressedKeys.isEmpty()) {
        }
    }
}

void KeyLineEdit::resetCombo() { _currentCombo.clear(); }

void KeyLineEdit::updateDisplay() {
    QString combo;
    for (int key : _pressedKeys) {
        combo += QKeySequence(key).toString() + "+";
    }
    combo.chop(1);
    if (!combo.isEmpty() && combo != _currentCombo) {
        _currentCombo = combo;
        setText(_currentCombo);
    }
}
