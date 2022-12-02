#include <gui/model/Model.hpp>
#include <cmath>
#include <gui/model/ModelListener.hpp>
extern float freq[600];
extern float mag[600];
extern float phase[600];
extern unsigned char data_ready;
extern unsigned int total_points;

unsigned int flag_terminacion = 0;

Model::Model() : modelListener(0)
{

}
void Model::Freq_Config(float freq_min, float freq_max, unsigned int points_decade)
{
	unsigned int i = 1;	//indice para recorrer freq[]

	/*Se verifica que la cantidad de puntos totales que se
	querrían computar no supere el tamaño máximo reservado para
	el vector de frecuencia*/
	if(log10(freq_max/freq_min) * points_decade > 600)
		points_decade = int(600/log10(freq_max/freq_min));

	float step = pow(10,1.0/points_decade);

	freq[0] = freq_min;

	while(freq[i-1] < freq_max)
	{
		freq[i] = freq[i-1] * step ;
		i++;
	}
	total_points = i;
	data_ready=1;
}

void Model::tick()
{

	if(data_ready)
	{
		modelListener->write(freq,mag,phase,total_points);

		data_ready = 0;
	}

}
