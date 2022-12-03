#include <gui/freq_config_screen/Freq_ConfigView.hpp>
#include <cmath>
#include <string>
#include <cstring>

#define ROUND_TO_INT(x) ((unsigned int)((x)+0.5))

unsigned long range_min;
unsigned long range_max;

unsigned int value_sliderFmin = 200;
unsigned int value_sliderFmax = 400;
unsigned int value_sliderPoints = 20;

Freq_ConfigView::Freq_ConfigView()
{
	sliderFreq_Min.setValue(value_sliderFmin);
	SliderSet_Freq_Min(value_sliderFmin);

	sliderFreq_Max.setValue(value_sliderFmax);
	SliderSet_Freq_Max(value_sliderFmax);

	sliderPoints_Decade.setValue(value_sliderPoints);
	SliderSet_PointsDecade(value_sliderPoints);
}

void Freq_ConfigView::setupScreen()
{
    Freq_ConfigViewBase::setupScreen();
}

void Freq_ConfigView::tearDownScreen()
{
    Freq_ConfigViewBase::tearDownScreen();
}

void Freq_ConfigView::Check_Frequencies()
{
	if(value_sliderFmin >= value_sliderFmax)	//Mensaje de error y desabilito boton
	{
		if(textErrorFreq.isVisible()==false)
		{
			textErrorFreq.setVisible(true);
			textErrorFreq.invalidate();

			buttonEnter_Freq.setTouchable(false);

			boxGreyButton.setVisible(true);
			boxGreyButton.invalidate();
		}
	}

	else if(textErrorFreq.isVisible())	//Si no hay problema y esta el mensaje de error lo saco y habilito el boton
	{
		textErrorFreq.setVisible(false);
		textErrorFreq.invalidate();

		buttonEnter_Freq.setTouchable(true);

		boxGreyButton.setVisible(false);
		boxGreyButton.invalidate();
	}
}

void Freq_ConfigView::SliderSet_Freq_Min(int value)
{
	char aux_string[6];

	value_sliderFmin = value;

	Check_Frequencies();

	freq_min = pow(10, (float)value_sliderFmin/100.0);

	if(freq_min >= 1000000)
		sprintf(aux_string, "%d M", ROUND_TO_INT(freq_min/1000000.0));

	else if(freq_min >= 1000)
		sprintf(aux_string, "%d K", ROUND_TO_INT(freq_min/1000.0));

	else
		sprintf(aux_string, "%d", ROUND_TO_INT(freq_min));

	memset(labelFminBuffer,0,sizeof(labelFminBuffer));
	Unicode::strncpy(labelFminBuffer, aux_string,Unicode::strlen(aux_string));
	labelFmin.invalidate();
}

void Freq_ConfigView::SliderSet_Freq_Max(int value)
{
	char aux_string[6];

	value_sliderFmax = value;

	Check_Frequencies();

	freq_max = pow(10, (float)value_sliderFmax/100.0);

	if(freq_max >= 1000000)
		sprintf(aux_string, "%d M", ROUND_TO_INT(freq_max/1000000.0));

	else if(freq_max >= 1000)
		sprintf(aux_string, "%d K", ROUND_TO_INT(freq_max/1000.0));

	else
		sprintf(aux_string, "%d", ROUND_TO_INT(freq_max));

	memset(labelFmaxBuffer,0,sizeof(labelFmaxBuffer));
	Unicode::strncpy(labelFmaxBuffer, aux_string,Unicode::strlen(aux_string));
	labelFmax.invalidate();

}

void Freq_ConfigView::SliderSet_PointsDecade(int value)
{
	char aux_string[6];

	value_sliderPoints = value;

	sprintf(aux_string, "%d", value_sliderPoints);

	memset(labelPointsBuffer,0,sizeof(labelPointsBuffer));
	Unicode::strncpy(labelPointsBuffer, aux_string,Unicode::strlen(aux_string));
	labelPoints.invalidate();
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


	presenter->Freq_Config_Presenter(freq_min, freq_max, value_sliderPoints);

}
