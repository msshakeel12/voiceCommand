#include <Wire.h>
#include <Servo.h>
#include <seeed-kit.h>
#include <math.h>
#include <SoftwareSerial.h>

//function declaration
void voice();
void adjustLight(int b, int a, int d);
int z;

unsigned int  data[4]={1,2,4,2};
unsigned int ta[4]={0,0,0,0};

void playNote(double f, int port);
void playPiano(char notesPlayed,int length);

double castleOfGlass[] = {220, 220, 246.9417, 261.6256, 246.9417, 220, 195.9977, 195.9977, 220, 146.8324, 146.8324, 164.8138};
double castleOfGlassVerse2[] = {220, 220, 195.9977, 220, 220, 195.9977, 220, 220, 195.9977, 220, 220, 195.9977};


char *voiceBuffer[] =
{
  "Turn on the light",
  "Turn off the light",
  "Play music",
  "Pause",
  "Next",
  "Previous",
  "Up",
  "Down",
  "Turn on the TV",
  "Turn off the TV",
  "Increase temperature",
  "Decrease temperature",
  "What's the time",
  "Open the door",
  "Close the door",
  "Left",
  "Right",
  "Stop",
  "Start",
  "Mode 1",
  "Mode 2",
  "Go",
};

int main()
{
  init();
  lcdInit();
  speechInit(7);
  barInit(2);
  barSetLevel(0);
  segmentInit(3);
  rgbLedInit(8, 1);
  lcdBacklightColour(0255, 255, 0255);
  lcdPrint("HELLO");
  delay(1000);
  voice();
  return 0;
}

void voice()
{ int cmd = 0;
  int lv = 0;
  while (1)
  {
    lcdClear();
    lcdPrint("Say Command");
    delay(500);
    speechGetCommand(cmd);

    if (cmd == 1)
    { lcdClear();
    lcdBacklightColour(0,90,100);
      lcdPrint("turning on");
      delay(1000);
      rgbLedHSB(0, 0.5, 0.5, 1);
      cmd=0;
    }


    if (cmd == 2)
      {lcdClear();
      lcdPrint("turing off");
      delay(1000);
      rgbLedHSB(0, 0.5, 0.5, 0);
      cmd=0;}

    if (cmd == 3)
  {
      lcdClear();
      lcdPrint("PLAYING Castle");
      lcdMoveCursor(0,1);
      lcdPrint("Of Glass");
      delay(1000);
      int j = 0;
   while(j<3)
   {
     
     for(int i = 0; i<13; i++)
       {
 
          playNote(castleOfGlass[i],  5);
          delay(5);
       }
       j+=1;
    }

   for(int i = 0; i<13; i++)
     {
        playNote(castleOfGlassVerse2[i],  5);
        delay(5);
     }
      cmd=0;void playNote(double f, int port);
void playPiano(char notesPlayed,int length);

double castleOfGlass[] = {220, 220, 246.9417, 261.6256, 246.9417, 220, 195.9977, 195.9977, 220, 146.8324, 146.8324, 164.8138};
double castleOfGlassVerse2[] = {220, 220, 195.9977, 220, 220, 195.9977, 220, 220, 195.9977, 220, 220, 195.9977};

  }

    if (cmd == 7)
    { lcdClear();
      lcdPrint("one up");
      delay(1000);
      lv++;
      barSetLevel(lv);
      cmd=0;
      }
    if (cmd == 20)
    {
      z = analogRead(A0);
      adjustLight(0, A0, 4);

    }
    if(cmd==13)
    {
      delay(1000);
      segmentDisplayAll(data);
      segmentDisplayAll(data);
      delay(1500);
      segmentDisplayAll(ta);
      cmd=0;
    }

    if (cmd == 8)
    {
      lcdClear();
      lcdPrint("one down");
      delay(1000);
      lv--;
      barSetLevel(lv);
      cmd=0;

    }
    if(cmd==21)
    { for(int i=0;i<25;i++)
    {rgbLedRGB(0, 255, 0, 0);
      delay(70);
     rgbLedRGB(0, 0,255, 0);
     delay(70);
     rgbLedRGB(0,0, 0, 255);
     delay(70);
    }
    rgbLedHSB(0, 0.5, 0.5, 0);
    cmd=0;
    }
   
    if (cmd == 9)
      lcdPrint(lv);
    else
    { lcdClear();
      lcdPrint(voiceBuffer[cmd - 1]);
     
    }
  }
}
void adjustLight(int b, int a, int d)
{

  z = analogRead(A0);
  int br;

  if(z>700)
   br=10;
 else if(z>600)
   br=100;
 else if(z>500)
   br=200;
 else if(z>400)
   br=300;
else if(z>300)
   br=400;
else if(z>200)
   br=500;
else if(z>150)
   br=600;
 else
   br=700;
  rgbLedHSB(0, 188, 68.05, br);

}

void playNote(double  f, int port)
{

  //Convert frequency of note to time period in microseconds
  int time = 1000000.0 / (2*f);

  //Send digital square wave to speaker with the calculated period
  for (int i = 0; i < 100; i++)
  {
    digitalWrite(port, HIGH);
    delayMicroseconds(time);
    digitalWrite(port, LOW);
    delayMicroseconds(time);
  }
}
