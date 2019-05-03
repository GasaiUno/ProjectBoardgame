#include <FastLED.h>
#define LED 53
#define NUM_LEDS 40

CRGB leds[NUM_LEDS];

int pole1[5][9];
int pole2[5][9];
int pole1Sum;
int pole2Sum;
int g;
int LEDs[5][9]={
                  {0,1,2,3,4,5,6,7,8},
                  {16,15,14,13,12,11,10,9,24},
                  {33,17,18,19,20,21,22,23,25},
                  {34,32,31,30,29,28,27,26,39},
                  {0,35,0,36,0,37,0,38,0}

               };

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  for (int i=2;i<=41;i++)
  {
     pinMode(i,INPUT);
  }
  for(int i=0;i<5;i++)
  {
     for(int j=0;j<9;j++)
     {
        if ((j%2==0 || j==0) && i==4)
          {
           pole1[i][j]=8;
           pole2[i][j]=8;
           continue;
          }
         else
         {
            pole1[i][j]=1;
            pole2[i][j]=1;
         }
     }
  }
}

void loop()
  {
 
  //loop for checking sensors and filling a matrix
  g=2;
  for (int j=0;j<9;j++)
  {
     for(int i=0;i<5;i++)
     {
         if ((j%2==0 || j==0) && i==4)
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(g);
         g++;
     }
  }//end of the loop

  /*//loop for sum up array
  for(int i=0;i<5;i++)
  {
     for(int j=0;j<9;j++)
     {
        if ((j%2==0 || j==0) && i==4)
          {
           continue;
          }
         else
            pole1Sum+=pole1[i][j];
     }
  }//end of the loop*/
  //loop for switch on LED strip 
  for (int i=0;i<5;i++)
  {
     for(int j=0;j<9;j++)
     {
         if ((j%2==0 ||j==0) && i==4)
           continue;
         else
           if (pole1[i][j]==0)
             leds[LEDs[i][j]]=CRGB (255,28,0);//Green Red Blue
           else
             leds[LEDs[i][j]]=CRGB (0,0,0);
     }
     FastLED.show();
  }//end of the loop
  
    //loop for checking sensors and filling a matrix
  g=2;
  for (int i=0;i<5;i++)
  {
     for(int j=0;j<=4;j++)
     {
         if ((j%2==0 || j==0) && i==4)
          {
           continue;
          }
         else
           pole2[i][j]=digitalRead(g);
         g++;
     }
  }//end of the loop

  /*//loop for sum up array
  for(int i=0;i<5;i++)
  {
     for(int j=0;j<9;j++)
     {
        if ((j%2==0 || j==0) && i==4)
          {
           continue;
          }
         else
            pole2Sum+=pole2[i][j];
     }
  }*/
    /*Serial.println(pole1Sum);
    Serial.println(pole2Sum);
    Serial.println("________");
     if (pole1Sum != pole2Sum)
     {*/
      for(int i=0;i<5;i++)
      {
     for(int j=0;j<9;j++)
         {
           Serial.print(pole1[i][j]);
         }
        Serial.println();
      }
        Serial.println("---------------------------");
}//end of the programm 
