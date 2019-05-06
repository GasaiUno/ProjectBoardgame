#include <FastLED.h>
#include <SPI.h>
#include <MFRC522.h>
#define LED 42
#define NUM_LEDS 40
#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);   // создаем экземпляр MFRC522 instance.

CRGB leds[NUM_LEDS];

int pole1[9][9];
int pole2[9][9];
int pole1Sum;
int pole2Sum;
int UID;
String content;
int UnitInit[4][6]={
                      {127,1,0,0,0,0},
                      {102,2,1,3,2,2},
                      {125,3,1,2,2,2},
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

int LEDs[9][9]={
                  {0,1,0,3,0,5,0,7,0},
                  {0,0,2,0,4,0,6,0,8},
                  {0,15,0,13,0,11,0,9,0},
                  {16,0,14,0,12,0,10,0,24},
                  {0,17,0,19,0,21,0,23,0},
                  {33,0,18,0,20,0,22,0,25},
                  {0,32,0,30,0,28,0,26,0},
                  {34,0,31,0,29,0,27,0,39},
                  {0,35,0,36,0,37,0,38,0}

               };

int Sensors[9][9]={
                  {0,6,0,15,0,24,0,33,0},
                  {2,0,11,0,20,0,29,0,38},
                  {0,7,0,16,0,25,0,34,0},
                  {3,0,12,0,21,0,30,0,39},
                  {0,8,0,17,0,26,0,35,0},
                  {4,0,13,0,22,0,31,0,40},
                  {0,9,0,18,0,27,0,36,0},
                  {5,0,14,0,23,0,32,0,41},
                  {0,10,0,19,0,28,0,37,0}

               };

void setup() {
  Serial.begin(9600);   // запускаем последовательную коммуникацию
  SPI.begin();          // инициализируем шину SPI
  mfrc522.PCD_Init();   // инициализируем MFRC522
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  for (int i=2;i<=41;i++)
  {
     pinMode(i,INPUT);
  }
  for(int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
        if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0)))
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
  while (digitalRead(2)==1)
  {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    Serial.println("AAAAAAAAAAAAAA!!!");
    continue;
  }
  // выбираем одну из карт:
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    Serial.println("<<<<<<<<>>>>>>>>!!!");
    continue;
  }
  else
    Serial.println("GGGGGGGGGGGGGg");
 content.concat(String(mfrc522.uid.uidByte[2], DEC));
 UID=content.toInt();
 Serial.println(UID);
  }
 //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 || i!=0) && (j%2!=0 || j!=0)))
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop
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
     for(int y=0;y<9;y++)
     {
         if (((x==0 || x%2==0)&&(y==0 || y%2==0))||((x%2!=0 || x!=0) && (y%2!=0 || y!=0)))
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
delay(10000);
}


void loop()
  {
 
  //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0)))
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
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 || i!=0) && (j%2!=0 || j!=0)))
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
     for(int j=0;j<9;j++)
         {
           Serial.print(pole1[i][j]);
         }
        Serial.println();
      }
        Serial.println("---------------------------");
}//end of the programm 
