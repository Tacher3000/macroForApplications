// settingsfragment.cpp
#include "settingsfragment.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "screens.h"

SettingsFragment::SettingsFragment(QWidget *parent)
    : BaseFragment(parent)
{
}

void SettingsFragment::init()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QPushButton *backButton = new QPushButton("Назад", this);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, [this]() {
        emit navigateTo(screens::MAIN_TAG);
    });

    setLayout(layout);
}
