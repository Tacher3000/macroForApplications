#include "hotkeylineedit.h"
#include <QKeyEvent>

HotKeyLineEdit::HotKeyLineEdit()
{

}

void HotKeyLineEdit::keyPressEvent(QKeyEvent *event){
    // Получаем код клавиши
    int key = event->key();

    // Получаем модификаторы (например, Ctrl, Shift)
    Qt::KeyboardModifiers modifiers = event->modifiers();

    // Преобразуем код клавиши в строку (например, 'A', 'B', 'C', ...)
//    QString keyText = QKeySequence(key).toString();

    // Создаем строку, представляющую комбинацию клавиш с модификаторами
    QString shortcut = QKeySequence(modifiers | key).toString();


    setText(shortcut);

}
