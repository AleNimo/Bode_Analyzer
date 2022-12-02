#include <gui/grafico_screen/GraficoView.hpp>
#include <cmath>
#include <string>
#include <cstring>
#include <touchgfx/widgets/canvas/Line.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

using namespace std;

bool first_time = true;

extern unsigned long range_min;
extern unsigned long range_max;

GraficoView::GraficoView()
{

}

void GraficoView::setupScreen()
{
    GraficoViewBase::setupScreen();
}

void GraficoView::tearDownScreen()
{
    GraficoViewBase::tearDownScreen();
}


void GraficoView::Toggle_Mag_Phase()
{
	Unicode::UnicodeChar string_aux[3];

	static uint8_t type_plot = MAG;
	if(type_plot == MAG)
	{
		string_aux[0]='|';
		string_aux[1]='T';
		string_aux[2]='|';

		Unicode::strncpy(buttonMAG_PHBuffer, string_aux, 3);
		buttonMAG_PH.setWildcardTextBuffer(buttonMAG_PHBuffer);
		buttonMAG_PH.invalidate();

		graphMAG.setVisible(false);
		graphMAG.invalidate();

		graphPH.setVisible(true);
		graphPH.invalidate();
		//graphMAG.clear();

		type_plot = PHASE;

	}
	else
	{
		memset(buttonMAG_PHBuffer,0,sizeof(buttonMAG_PHBuffer));
		string_aux[0]=0x03D5; //ϕ
		Unicode::strncpy(buttonMAG_PHBuffer, string_aux, 1);
		buttonMAG_PH.invalidate();

		graphMAG.setVisible(true);
		graphMAG.invalidate();

		graphPH.setVisible(false);
		graphPH.invalidate();
		//graphMAGLine1.invalidate();

		//graphMAG.clear();
		type_plot = MAG;
	}

	//plot = true;

}
void GraficoView::DataDisplay(float* freq,float*mag,float*phase,unsigned int num_points)
{

	static uint8_t i = 0;
	//static bool plot = true;

	//static float xmin = graphMAG.getGraphRangeXMinAsFloat();
	//static float xmax = graphMAG.getGraphRangeXMaxAsFloat();
	static float ymin_mag;
	static float ymax_mag;

	static float ymin_phase;
	static float ymax_phase;

	static float decades = log10((double)range_max/range_min);

	uint8_t divs_vertical = 10;

	static TextAreaWithOneWildcard* freq_label[6]
	{
		&decade_0,
		&decade_1,
		&decade_2,
		&decade_3,
		&decade_4,
		&decade_5,

	};
	static Unicode::UnicodeChar* freq_label_buffer[6]
	{
		decade_0Buffer,
		decade_1Buffer,
		decade_2Buffer,
		decade_3Buffer,
		decade_4Buffer,
		decade_5Buffer,

	};
	static Line* lines[60]
   {
		&line_0,
		&line_1,
		&line_2,
		&line_3,
		&line_4,
		&line_5,
		&line_6,
		&line_7,
		&line_8,
		&line_9,
		&line_10,
		&line_11,
		&line_12,
		&line_13,
		&line_14,
		&line_15,
		&line_16,
		&line_17,
		&line_18,
		&line_19,
		&line_20,
		&line_21,
		&line_22,
		&line_23,
		&line_24,
		&line_25,
		&line_26,
		&line_27,
		&line_28,
		&line_29,
		&line_30,
		&line_31,
		&line_32,
		&line_33,
		&line_34,
		&line_35,
		&line_36,
		&line_37,
		&line_38,
		&line_39,
		&line_40,
		&line_41,
		&line_42,
		&line_43,
		&line_44,
		&line_45,
		&line_46,
		&line_47,
		&line_48,
		&line_49,
		&line_50,
		&line_51,
		&line_52,
		&line_53,
		&line_54,
		&line_55,
		&line_56,
		&line_57,
		&line_58,
		&line_59
   };

	for(i = 0;i<decades;i++)
	{
		//LOGARITHMIC MADNESS

		lines[1+i*10]->setX((320-30)/decades*(i+log10(2))+30);
		lines[2+i*10]->setX((320-30)/decades*(i+log10(3))+30);
		lines[3+i*10]->setX((320-30)/decades*(i+log10(4))+30);
		lines[4+i*10]->setX((320-30)/decades*(i+log10(5))+30);
		lines[5+i*10]->setX((320-30)/decades*(i+log10(6))+30);
		lines[6+i*10]->setX((320-30)/decades*(i+log10(7))+30);
		lines[7+i*10]->setX((320-30)/decades*(i+log10(8))+30);
		lines[8+i*10]->setX((320-30)/decades*(i+log10(9))+30);
		lines[9+i*10]->setX((320-30)/decades*(i+log10(10))+30);


		lines[1+i*10]->setVisible(true);
		lines[2+i*10]->setVisible(true);
		lines[3+i*10]->setVisible(true);
		lines[4+i*10]->setVisible(true);
		lines[5+i*10]->setVisible(true);
		lines[6+i*10]->setVisible(true);
		lines[7+i*10]->setVisible(true);
		lines[8+i*10]->setVisible(true);
		lines[9+i*10]->setVisible(true);


		lines[1+i*10]->invalidate();
		lines[2+i*10]->invalidate();
		lines[3+i*10]->invalidate();
		lines[4+i*10]->invalidate();
		lines[5+i*10]->invalidate();
		lines[6+i*10]->invalidate();
		lines[7+i*10]->invalidate();
		lines[8+i*10]->invalidate();
		lines[9+i*10]->invalidate();

		char freq_string[6];

		if(range_min*pow(10,i)>100)
		{
			sprintf(freq_string, "%d K", (int)(range_min*pow(10,i)/1000));
		}else
			sprintf(freq_string, "%d", (int)(range_min*pow(10,i)));

		Unicode::strncpy(freq_label_buffer[i], freq_string, Unicode::strlen(freq_string));
		//textArea1.resizeToCurrentText();
		freq_label[i]->setX((320-30)/decades*(i)+30-15);
		freq_label[i]->setVisible(true);
		freq_label[i]->invalidate();



	}

	graphMAG.setGraphRangeX((float)log10((double)range_min),(float)log10((double)range_max));
	graphPH.setGraphRangeX((float)log10((double)range_min),(float)log10((double)range_max));

	for(unsigned int j = 0;j<num_points;j++)
	{

		float f = log10((double) freq[j]);
		graphMAG.addDataPoint((float)f, (float)mag[j]);
		graphPH.addDataPoint((float)f, (float)phase[j]);
	}

	graphMAG.setGraphRangeYAuto(false,0);
	graphPH.setGraphRangeYAuto(false,0);

	ymin_mag = graphMAG.getGraphRangeYMinAsFloat();
	ymax_mag = graphMAG.getGraphRangeYMaxAsFloat();

	ymin_phase = graphPH.getGraphRangeYMinAsFloat();
	ymax_phase = graphPH.getGraphRangeYMaxAsFloat();

	float tick_vertical_mag = (ymax_mag-ymin_mag)/divs_vertical;
	float tick_vertical_phase = (ymax_phase-ymin_phase)/divs_vertical;

	graphMAGMajorYAxisLabel.setInterval((float)tick_vertical_mag);
	graphMAGMajorYAxisGrid.setInterval((float)tick_vertical_mag);

	graphMAGMajorYAxisLabel.invalidate();
	graphMAGMajorYAxisGrid.invalidate();
	graphMAGLine1.invalidate();

	graphPHMajorYAxisLabel.setInterval((float)tick_vertical_phase);
	graphPHMajorYAxisGrid.setInterval((float)tick_vertical_phase);

	graphMAG.invalidate();
	graphPH.invalidate();
}
