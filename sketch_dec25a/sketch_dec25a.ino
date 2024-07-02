#include "arduinoFFT.h"
 #include<Wire.h>
//#define SAMPLES 128     
#define SAMPLES 64//SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
//#define SAMPLING_FREQUENCY 2048 //Ts = Based on Nyquist, must be 2 times the highest expected frequency.
#define SAMPLING_FREQUENCY 6000
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values
double Pdump = 0;
void setup() 
{
    //Serial.begin(115200); //Baud rate for the Serial Monitor
    Serial.begin(230400);
    //Serial.begin(9600);
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
    Wire.begin();
}
 
void loop() 
{  
              for(int j=0; j<150; j++)
                      {/*Sample SAMPLES times*/
                      for(int i=0; i<SAMPLES; i++)
                      {
                          microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
                       
                          vReal[i] = analogRead(0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
                          vImag[i] = 0; //Makes imaginary term 0 always
                  
                          /*remaining wait time between samples if necessary*/
                          while(micros() < (microSeconds + samplingPeriod))
                          {
                            //do nothing
                          }
                      }
                   
                      /*Perform FFT on samples*/
                      FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
                      FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
                      FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
                     
                      /*Find peak frequency and print peak*/
                      double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
                      //Serial.println(peak);     //Print out the most dominant frequency.
                      //while (1); //do one time
                     double c;
                     if (peak<2841)
                         {  c = 0; }
                         else
                         { c = peak; }
                      Pdump=Pdump+c;
                      }                 
                 Serial.print("             ");
                 double z = ((Pdump/150));
                 Serial.println(z);
                  Serial.print("                               ");
                  double a = ((3.5)*(2)*(3.14)*(0.09));
                  Serial.print(" speed is  ");
                  Serial.println((z-1634));
               // Wire.beginTransmission(9);//9 here is the address of the slave board 
                //Wire.write((Pdump));//Transfers the value of potentiometer to the slave board            
                //Wire.endTransmission(); 
                 Pdump=0;     
}
