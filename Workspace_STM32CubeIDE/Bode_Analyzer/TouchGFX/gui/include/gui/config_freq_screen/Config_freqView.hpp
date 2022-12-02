#ifndef CONFIG_FREQVIEW_HPP
#define CONFIG_FREQVIEW_HPP

#include <gui_generated/config_freq_screen/Config_freqViewBase.hpp>
#include <gui/config_freq_screen/Config_freqPresenter.hpp>

class Config_freqView : public Config_freqViewBase
{
public:
    Config_freqView();
    virtual ~Config_freqView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CONFIG_FREQVIEW_HPP
