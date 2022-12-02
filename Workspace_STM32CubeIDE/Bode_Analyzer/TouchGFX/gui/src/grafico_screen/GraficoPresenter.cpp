#include <gui/grafico_screen/GraficoView.hpp>
#include <gui/grafico_screen/GraficoPresenter.hpp>

GraficoPresenter::GraficoPresenter(GraficoView& v)
    : view(v)
{

}

void GraficoPresenter::activate()
{

}

void GraficoPresenter::deactivate()
{

}
void GraficoPresenter::write(float* freq,float*mag,float*phase,unsigned int num_points)
{
	view.DataDisplay(freq,mag,phase,num_points);
}
