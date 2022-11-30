#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
extern float freq[2001];
extern float mag[2001];
extern float phase[2001];
extern unsigned int num_points;


Model::Model() : modelListener(0)
{

}

void Model::tick()
{
	if(1)
	{
		modelListener->write(freq,mag,phase,num_points);
	}



}
