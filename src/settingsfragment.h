#ifndef SETTINGSFRAGMENT_H
#define SETTINGSFRAGMENT_H

#include "basefragment.h"

class SettingsFragment : public BaseFragment
{
    Q_OBJECT
public:
    explicit SettingsFragment(QWidget *parent = nullptr);
    void init() override;
};

#endif // SETTINGSFRAGMENT_H
