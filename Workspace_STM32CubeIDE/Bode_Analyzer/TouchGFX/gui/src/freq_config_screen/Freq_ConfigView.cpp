#include <gui/freq_config_screen/Freq_ConfigView.hpp>
#include <cmath>
#include <string>
#include <cstring>
unsigned long range_min;
unsigned long range_max;

Freq_ConfigView::Freq_ConfigView()
{

}

void Freq_ConfigView::setupScreen()
{
    Freq_ConfigViewBase::setupScreen();
}

void Freq_ConfigView::tearDownScreen()
{
    Freq_ConfigViewBase::tearDownScreen();
}

void Freq_ConfigView::SliderSet_Freq_Min(int value)
{
	char aux_string[6];

	freq_min = pow(10, (float)value/100.0);

	if(freq_min >= 1000000)
		sprintf(aux_string, "%d M", (int)(freq_min/1000000));

	else if(freq_min >= 1000)
		sprintf(aux_string, "%d K", (int)freq_min/1000);

	else
		sprintf(aux_string, "%d", (int)freq_min);

	memset(FminBuffer,0,sizeof(FminBuffer));
	Unicode::strncpy(FminBuffer, aux_string,Unicode::strlen(aux_string));
	Fmin.invalidate();
}

void Freq_ConfigView::SliderSet_Freq_Max(int value)
{
	char aux_string[6];

	freq_max = pow(10, (float)value/100.0);

	if(freq_max >= 1000000)
		sprintf(aux_string, "%d M", (int)(freq_max/1000000));

	else if(freq_max >= 1000)
		sprintf(aux_string, "%d K", (int)freq_max/1000);

	else
		sprintf(aux_string, "%d", (int)freq_max);

	memset(FmaxBuffer,0,sizeof(FmaxBuffer));
	Unicode::strncpy(FmaxBuffer, aux_string,Unicode::strlen(aux_string));
	Fmax.invalidate();


}

void Freq_ConfigView::SliderSet_PointsDecade(int value)
{
	char aux_string[6];

	points_decade = (unsigned int) value;

	sprintf(aux_string, "%d", points_decade);

	memset(PointsBuffer,0,sizeof(PointsBuffer));
	Unicode::strncpy(PointsBuffer, aux_string,Unicode::strlen(aux_string));
	Points.invalidate();
}

void Freq_ConfigView::Enter_Freq()
{

	//encontramos la decada maxima
	if(freq_max > 100000) //Graficamos hasta 1 millon
		range_max = 1000000;

	else if(freq_max > 10000) //Graficamos hasta 100k
		range_max = 100000;

	else if(freq_max > 1000) //Graficamos hasta 10k
		range_max = 10000;

	else if(freq_max > 100) //Graficamos hasta 1k
		range_max = 1000;

	else if(freq_max > 10) //Graficamos hasta 100
		range_max = 100;

	else if(freq_max > 1) //Graficamos hasta 10
		range_max = 10;

	//encontramos la decada maxima
	if(freq_min < 10) //Graficamos desde 1
		range_min = 1;

	else if (freq_min < 100) //Graficamos desde 10
		range_min = 10;

	else if  (freq_min < 1000) //Graficamos desde 100
		range_min = 100;

	else if  (freq_min < 10000) //Graficamos desde 1k
		range_min = 1000;

	else if  (freq_min < 100000) //Graficamos desde 10k
		range_min = 10000;

	else if (freq_min < 1000000) //Graficamos desde 100k
		range_min = 100000;


	presenter->Freq_Config_Presenter(freq_min, freq_max, points_decade);

}
