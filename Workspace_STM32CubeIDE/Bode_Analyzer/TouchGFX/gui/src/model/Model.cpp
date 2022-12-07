#include <gui/model/Model.hpp>
#include <cmath>
#include <gui/model/ModelListener.hpp>
#include "cmsis_os.h"
#include "main.h"

extern float freq[MAX_FREQ_POINTS];
extern float mag[MAX_FREQ_POINTS];
extern float phase[MAX_FREQ_POINTS];
extern unsigned char data_ready;
extern unsigned int total_points;

extern SemaphoreHandle_t sem_measure;

Model::Model() : modelListener(0)
{

}
void Model::Freq_Config(float freq_min, float freq_max, unsigned int points_decade)
{
	unsigned int i = 1;	//indice para recorrer freq[]

	/*Se verifica que la cantidad de puntos totales que se
	querrían computar no supere el tamaño máximo reservado para
	el vector de frecuencia*/
	if(log10(freq_max/freq_min) * points_decade > MAX_FREQ_POINTS)
		points_decade = int(MAX_FREQ_POINTS/log10(freq_max/freq_min));

	float step = pow(10,1.0/points_decade);

	freq[0] = freq_min;

	while(freq[i-1] < freq_max)
	{
		freq[i] = freq[i-1] * step ;
		i++;
	}
	total_points = i;

	xSemaphoreGive(sem_measure);	//Desbloqueo tarea de medición
}

void Model::tick()
{

	if(data_ready)
	{
		modelListener->write(freq,mag,phase,total_points);

		data_ready = 0;
	}

}
