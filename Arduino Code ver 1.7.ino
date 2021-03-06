#include <FastLED.h>
#include <SPI.h>
#include <MFRC522.h>
#define LED 48
#define NUM_LEDS 40
#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);   // создаем экземпляр MFRC522 instance.

CRGB leds[NUM_LEDS];

int pole1[9][9];
int pole2[9][9];
int xy[2][6];
int pole1Sum;
int pole2Sum;
int UID;
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
                  {0,9,0,42,0,27,0,36,0},
                  {5,0,14,0,23,0,32,0,41},
                  {0,10,0,43,0,28,0,37,0}

               };
int Range(int x,int y,int n)
{
   for (int s=1;s<=n;s++)
   {
      switch(s)
      {
        case 1: 
          if (x-2>=0)
          {
             pole1[x-2][y]=3;
             Serial.println("IF 1");
             xy[1][1]=x-2;
             xy[2][1]=y;
          }
          if (x+2<=8)
          {
             pole1[x+2][y]=3;
             Serial.println("IF 2");
             xy[1][2]=x+2;
             xy[2][2]=y;
          }
             
          if ((x+1<=8)&&(y+1<=8))
          {
             pole1[x+1][y+1]=3;
             Serial.println("IF 3");
             xy[1][3]=x+1;
             xy[2][3]=y+1;
          }
          if ((x-1>=0)&&(y-1>=0))
          {
             pole1[x-1][y-1]=3;
             Serial.println("IF 4");
             xy[1][4]=x-1;
             xy[2][4]=y-1;
          }
          if ((x-1>=0)&&(y+1<=8))
          {
             pole1[x-1][y+1]=3;
             Serial.println("IF 5");
             xy[1][5]=x-1;
             xy[2][5]=y+1;
          }
          if ((x+1<=8)&&(y-1>=0))
          {
             pole1[x+1][y-1]=3;
             Serial.println("IF 6");
             xy[1][6]=x+1;
             xy[2][6]=y-1;
          }
         break;
         case 2:
           for (int i=0;i<6;i++)
           {
            x=xy[1][i];
            y=xy[2][i];
             if (x-2>=0)
          {
             pole1[x-2][y]=3;
             Serial.println("IF 1");
          }
          if (x+2<=8)
          {
             pole1[x+2][y]=3;
             Serial.println(pole1[x][y+2]);
             Serial.println("IF 2");
          }
             
          if ((x+1<=8)&&(y+1<=8))
          {
             pole1[x+1][y+1]=3;
             Serial.println("IF 3");
          }
          if ((x-1>=0)&&(y-1>=0))
          {
             pole1[x-1][y-1]=3;
             Serial.println("IF 4");
          }
          if ((x-1>=0)&&(y+1<=8))
          {
             pole1[x-1][y+1]=3;
             Serial.println("IF 5");
          }
          if ((x+1<=8)&&(y-1>=0))
          {
             pole1[x+1][y-1]=3;
             Serial.println("IF 6");
          }
           }
          break;
          case 3:
            for (int i=0;i<9;i++)
           {
             for (int j=0;j<9;j++)
             {
                if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0)))
                  continue;
                else
                {
                   if (pole1[i][j]==3)
                      Range(i,j,1);
                }
             }
           }
           break; 
      }
   }
}

void setup() {
  Serial.begin(9600);   // запускаем последовательную коммуникацию
  SPI.begin();          // инициализируем шину SPI
  mfrc522.PCD_Init();   // инициализируем MFRC522
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(200);
  for (int i=2;i<=17;i++)
  {
     pinMode(i,INPUT);
  }
  for (int i=20;i<=43;i++)
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
 /*for (int w=0;w<2;w++)
 {
  pole1Sum=0;
  pole2Sum=0;
  UID=0;
  while (UID==0)
  {
  if (  mfrc522.PICC_IsNewCardPresent())
  {
    if (  mfrc522.PICC_ReadCardSerial())
  {
      String content= "";
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.println(mfrc522.uid.uidByte[i], DEC) ;
     //content.concat(String(mfrc522.uid.uidByte[2] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[2], DEC));
     int Ident=content.toInt();
     UID=Ident;
     Serial.println(UID);
  }
  }
  }
 //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole1[i][j]==5))
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<=9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole2[i][j]==5))
          {
           continue;
          }
         else
           pole2[i][j]=digitalRead(Sensors[i][j]);
     }
  }

   for(int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
        if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole1[i][j]==5))
          {
           continue;
          }
         else
           {
            pole1Sum+=pole1[i][j];
            pole2Sum+=pole2[i][j];
           }            
     }
  }
  Serial.println(pole1Sum);
  Serial.println(pole2Sum);
 for (int i=0;i<4;i++)
 {
    if (UID==UnitInit[i][0])
    {
       UnitC[w][0]=UnitInit[i][1];
       UnitC[w][3]=UnitInit[i][2];
       UnitC[w][4]=UnitInit[i][3];
       UnitC[w][5]=UnitInit[i][4];
       UnitC[w][6]=UnitInit[i][5];
  while (pole1Sum==pole2Sum)
  {
     Serial.println("Warning!");
     //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole1[i][j]==5))
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop
  delay(500);
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<=9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole2[i][j]==5))
          {
           continue;
          }
         else
           pole2[i][j]=digitalRead(Sensors[i][j]);
     }
  }

    for(int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
        if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole2[i][j]==5))
          {
           continue;
          }
         else
           {
            pole1Sum+=pole1[i][j];
            pole2Sum+=pole2[i][j];
           }            
     }
  }
  }
  for (int x=0;x<9;x++)
  {
     for(int y=0;y<9;y++)
     {
         if (((x==0 || x%2==0)&&(y==0 || y%2==0))||((x%2!=0 && x!=0) && (y%2!=0 && y!=0))||(pole2==5))
           continue;
         else
         {
           if (pole2[x][y]==0)
           {
            UnitC[w][1]=y;
            UnitC[w][2]=x;
            pole1[x][y]=5;
            pole2[x][y]=5;
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
 Range(4,3,2);*/
 //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole1[i][j]==5)||(pole1[i][j]==3))
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop
}


void loop()
  {

  /*loop for sum up array
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
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0)))
           continue;
         else
         {
           switch (pole1[i][j])
           {
              case 0:
                Range(i,j,1);
              break;
              //case 5:
                //leds[LEDs[i][j]]=CRGB (0,0,255);//Green Red Blue
              //break;
              case 3:
                 leds[LEDs[i][j]]=CRGB (0,255,0);//Green Red Blue
               break;
              default:
                leds[LEDs[i][j]]=CRGB (255,0,0);
           } 
         }
     }
     FastLED.show();
  }//end of the loop
       Serial.println("YES");

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
    Serial.println("________");*/
      for(int i=0;i<9;i++)
      {
     for(int j=0;j<9;j++)
         {
           Serial.print(pole1[i][j]);
         }
        Serial.println();
      }
        Serial.println("---------------------------");
      //loop for checking sensors and filling a matrix
  for (int i=0;i<9;i++)
  {
     for(int j=0;j<9;j++)
     {
         if (((i==0 || i%2==0)&&(j==0 || j%2==0))||((i%2!=0 && i!=0) && (j%2!=0 && j!=0))||(pole1[i][j]==5))
          {
           continue;
          }
         else
           pole1[i][j]=digitalRead(Sensors[i][j]);
     }
  }//end of the loop
}//end of the programm 
