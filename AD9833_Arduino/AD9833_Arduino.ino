// Basic MD_AD9833 test file
//
// Initialises the device to default conditions
// 
// Connect a pot to A0 to change the frequency by turning the pot
//
#include <MD_AD9833.h>
#include <SPI.h>

#define FSYNC 53	///< SPI Load pin number (FSYNC in AD9833 usage) (10 en arduino uno)
#define boton 44

MD_AD9833	AD(FSYNC);  // Hardware SPI
/*
 * DATA 51
 * CLK 52
 * FSYNC (SS) 53
 */

// MD_AD9833	AD(DATA, CLK, FSYNC); // Arbitrary SPI pins

void setup(void)
{

	AD.begin();
  pinMode(boton,INPUT_PULLUP);
  AD.setFrequency(MD_AD9833::CHAN_0, 1);
}
float i = 1;
void loop(void)
{
  if (digitalRead(boton) == LOW)
  {
    if (i == 1000000) i=1;
    else if(i >= 100000)
      i = i+100000;
    else i = i*10;
      
    AD.setFrequency(MD_AD9833::CHAN_0, i);
    delay(500);
  }
}
