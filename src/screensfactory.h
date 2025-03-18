#ifndef SCREENSFACTORY_H
#define SCREENSFACTORY_H

#include "basescreensfactory.h"
#include "mainfragment.h"
#include "addcombinationfragment.h"
#include "settingsfragment.h"
#include "screens.h"

class ScreensFactory : public BaseScreensFactory
{
    Q_OBJECT
public:
    explicit ScreensFactory(QObject *parent = nullptr) : BaseScreensFactory(parent) {}
    ~ScreensFactory() override = default;

    BaseFragment* createFragment(const QString& tag) override
    {
        if (tag == screens::MAIN_TAG) {
            return new MainFragment();
        } else if (tag == screens::ADD_COMBINATION_TAG) {
            return new AddCombinationFragment();
        } else if (tag == screens::SETTINGS_TAG) {
            return new SettingsFragment();
        }
        return nullptr;
    }
};

#endif // SCREENSFACTORY_H
