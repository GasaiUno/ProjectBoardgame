#define LED_PIN1 13
#define LED_PIN2 12
#define LED_PIN3 11
#define LED_PIN4 10
#define LDR_PIN1 A0 
#define LDR_PIN2 2
#define LDR_PIN3 A1
#define LDR_PIN4 A2
int pole[2][2];
int pole2[2][2];
int character[6][2];
int i;
int j;

void setup() {
  pinMode(LED_PIN1,OUTPUT);
  pinMode(LED_PIN2,OUTPUT);
  pinMode(LED_PIN3,OUTPUT);
  pinMode(LED_PIN4,OUTPUT);
  pinMode(LDR_PIN2,INPUT);
  Serial.begin(9600);
  Serial.println("Game begins!");
}

void loop() {
    int lightStart1= analogRead(LDR_PIN1);
    int lightStart2= digitalRead(LDR_PIN2);
    int lightStart3= analogRead(LDR_PIN3);
    int lightStart4= analogRead(LDR_PIN4);
    //Serial.println(light1);
    //Serial.println(light2);
    //Serial.println(light3);
    //Serial.println(light4);
    if (lightStart1<800)
    {
      //digitalWrite(LED_PIN1,HIGH);
      pole[0][0]=1;
      }
     else
     {
      //digitalWrite(LED_PIN1,LOW);
      pole[0][0]=0;
      }
      if (lightStart2==0)
    {
      //digitalWrite(LED_PIN2,HIGH);
      pole[0][1]=1;
      }
     else
     {
      //digitalWrite(LED_PIN2,LOW);
      pole[0][1]=0;
      }
      if (lightStart3<820)
    {
      //digitalWrite(LED_PIN3,HIGH);
      pole[1][0]=1;
      }
     else
     {
      //digitalWrite(LED_PIN3,LOW);
      pole[1][0]=0;
      }
      if (lightStart4<650)
    {
      //digitalWrite(LED_PIN4,HIGH);
      pole[1][1]=1;
      }
     else
     {
      //digitalWrite(LED_PIN4,LOW);
      pole[1][1]=0;
      }
      for(i=0;i<2;i++)
      {
        for(j=0;j<2;j++)
        {
          Serial.print(pole[i][j]);
        }
          Serial.println("");
      }
      int lightFinal1= analogRead(LDR_PIN1);
      int lightFinal2= digitalRead(LDR_PIN2);
      int lightFinal3= analogRead(LDR_PIN3);
      int lightFinal4= analogRead(LDR_PIN4);
      ////////
      if (lightFinal1<800)
    {
      //digitalWrite(LED_PIN1,HIGH);
      pole2[0][0]=1;
      }
     else
     {
      //digitalWrite(LED_PIN1,LOW);
      pole2[0][0]=0;
      }
      if (lightFinal2==0)
    {
      //digitalWrite(LED_PIN2,HIGH);
      pole2[0][1]=1;
      }
     else
     {
      //digitalWrite(LED_PIN2,LOW);
      pole2[0][1]=0;
      }
      if (lightFinal3<820)
    {
      //digitalWrite(LED_PIN3,HIGH);
      pole2[1][0]=1;
      }
     else
     {
      //digitalWrite(LED_PIN3,LOW);
      pole2[1][0]=0;
      }
      if (lightFinal4<650)
    {
      //digitalWrite(LED_PIN4,HIGH);
      pole2[1][1]=1;
      }
     else
     {
      //digitalWrite(LED_PIN4,LOW);
      pole2[1][1]=0;
      }
      ////////
       for(i=0;i<2;i++)
      {
        for(j=0;j<2;j++)
        {
          if (pole2[i][j] == pole[i][j])
           {
              Serial.println("Ok");
           }
 
        }
      }
      
      Serial.println("_______________________________________");
      delay(1000);
  }
