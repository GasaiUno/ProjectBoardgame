#include <FastLED.h>
#define LED 53
#define NUM_LEDS 40

CRGB leds[NUM_LEDS];

int pole1[9][5];
int pole2[9][5];
int pole1Sum;
int pole2Sum;
int UID;
int UnitInit[4][6]={
                      {0,1,0,0,0,0},
                      {1,2,1,3,2,2},
                      {2,3,1,2,2,2},
                      {3,4,0,0,0,0}
                   };
/* 
    | 0 |1 |2 |3 |4 |5 |
   0|UID|ID|HP|DP|AP|AR|
*/
int UnitC[8][7];
/*
       |0 |1|2|3 |4 |5 |6 |
      0|ID|X|Y|HP|DP|AP|AR|
 */

int LEDs[9][5]={
                  {1,3,5,7,0},
                  {0,2,4,6,8},
                  {15,13,11,9,0},
                  {16,14,12,10,24},
                  {17,19,21,23,0},
                  {33,18,20,22,25},
                  {32,30,28,26,0},
                  {34,31,29,27,39},
                  {35,36,37,38,0}

               };

int Sensors[9][5]={
                  {6,15,24,33,0},
                  {2,11,20,29,38},
                  {7,16,25,34,0},
                  {3,12,21,30,39},
                  {8,17,26,35,0},
                  {4,13,22,31,40},
                  {9,18,27,36,0},
                  {5,14,23,32,41},
                  {10,19,28,37,0}

               };

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  for (int i=2;i<=41;i++)
  {
     pinMode(i,INPUT);
  }
  for(int i=0;i<9;i++)
  {
     for(int j=0;j<5;j++)
     {
        if ((i%2==0 || i==0) && j==4)
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

 //Инициализация 
 for (int w=0;w<8;w++)
 {
 UID=1;
 //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<5;j++)
     {
         if ((i%2==0 || i==0) && j==4)
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop

        for(int i=0;i<9;i++)
      {
     for(int j=0;j<5;j++)
         {
           Serial.print(pole1[i][j]);
         }
        Serial.println();
      }
        Serial.println("---------------------------");
        
 for (int i=0;i<4;i++)
 {
    if (UID==UnitInit[i][0])
    {
       UnitC[w][0]=UnitInit[i][1];
       UnitC[w][3]=UnitInit[i][2];
       UnitC[w][4]=UnitInit[i][3];
       UnitC[w][5]=UnitInit[i][4];
       UnitC[w][6]=UnitInit[i][5];
  for (int x=0;x<9;x++)
  {
     for(int y=0;y<5;y++)
     {
         if ((x%2==0 ||x==0) && y==4)
           continue;
         else
         {
           if (pole1[x][y]==0)
           {
            UnitC[w][1]=y;
            UnitC[w][2]=x;
           }         
         }
     }
  }//end of the loop
    }  
 
 }
  for(int i=0;i<8;i++)
      {
     for(int j=0;j<7;j++)
         {
           Serial.print(UnitC[i][j]);
         }
        Serial.println();
      }
        Serial.println("--------------------");
delay(3000);
}
delay(1000000);
}


void loop()
  {
 
  //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<5;j++)
     {
         if ((i%2==0 || i==0) && j==4)
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
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
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<5;j++)
     {
         if ((i%2==0 ||i==0) && j==4)
           continue;
         else
           if (pole1[i][j]==0)
             leds[LEDs[i][j]]=CRGB (255,28,0);//Green Red Blue
           else
             leds[LEDs[i][j]]=CRGB (0,0,0);
     }
     FastLED.show();
  }//end of the loop
  
    /*//loop for checking sensors and filling a matrix
   for (int i=0;i<5;i++)
  {
     for(int j=0;j<=4;j++)
     {
         if ((j%2==0 || j==0) && i==4)
          {
           continue;
          }
         else
           pole2[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop/

  //loop for sum up array
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
      for(int i=0;i<9;i++)
      {
     for(int j=0;j<5;j++)
         {
           Serial.print(pole1[i][j]);
         }
        Serial.println();
      }
        Serial.println("---------------------------");
}//end of the programm 
