#include <gui/freq_config_screen/Freq_ConfigView.hpp>
#include <gui/freq_config_screen/Freq_ConfigPresenter.hpp>

Freq_ConfigPresenter::Freq_ConfigPresenter(Freq_ConfigView& v)
    : view(v)
{

}

void Freq_ConfigPresenter::activate()
{

}

void Freq_ConfigPresenter::deactivate()
{

}

void Freq_ConfigPresenter::Freq_Config_Presenter(float freq_min, float freq_max, unsigned int points_decade)
{
	model->Freq_Config(freq_min, freq_max, points_decade);

}
