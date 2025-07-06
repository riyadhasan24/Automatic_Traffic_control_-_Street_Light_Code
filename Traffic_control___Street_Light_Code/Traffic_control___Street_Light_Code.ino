/* The source Code from : https://github.com/riyadhasan24
 * By Md. Riyad Hasan
 */
 
#define EW_Green 7
#define EW_Yellow 6
#define EW_Red 5

#define NS_Green 8
#define NS_Yellow 9
#define NS_Red 10

#define Extra_Street_Light 12
#define LDR_Pin A0

const int LDR_Threshold = 500;

void setup() {
  pinMode(EW_Green, OUTPUT);
  pinMode(EW_Yellow, OUTPUT);
  pinMode(EW_Red, OUTPUT);

  pinMode(NS_Green, OUTPUT);
  pinMode(NS_Yellow, OUTPUT);
  pinMode(NS_Red, OUTPUT);

  pinMode(Extra_Street_Light, OUTPUT);

  digitalWrite(EW_Green, HIGH);
  digitalWrite(EW_Yellow, LOW);
  digitalWrite(EW_Red, LOW);

  digitalWrite(NS_Green, LOW);
  digitalWrite(NS_Yellow, LOW);
  digitalWrite(NS_Red, HIGH);
}

void loop() 
{
  int LDR_Value = analogRead(LDR_Pin);

  if (LDR_Value < LDR_Threshold) 
  {
    digitalWrite(Extra_Street_Light, LOW);
  } 
  
  else 
  {
    digitalWrite(Extra_Street_Light, HIGH);
  }

  trafficLightControl();
}

void trafficLightControl() {
  static unsigned long previousMillis = 0;
  static int state = 0;

  unsigned long currentMillis = millis();

  switch (state) 
  {
    case 0:
      if (currentMillis - previousMillis >= 5000) 
      {
        previousMillis = currentMillis;
        digitalWrite(EW_Green, LOW);
        digitalWrite(EW_Yellow, HIGH);
        state = 1;
      } 
      
      else 
      {
        digitalWrite(EW_Green, HIGH);
        digitalWrite(EW_Yellow, LOW);
        digitalWrite(EW_Red, LOW);

        digitalWrite(NS_Green, LOW);
        digitalWrite(NS_Yellow, LOW);
        digitalWrite(NS_Red, HIGH);
      }
      break;

    case 1:
      if (currentMillis - previousMillis >= 2000) 
      {
        previousMillis = currentMillis;
        digitalWrite(EW_Yellow, LOW);
        digitalWrite(EW_Red, HIGH);

        digitalWrite(NS_Red, LOW);
        digitalWrite(NS_Green, HIGH);
        state = 2;
      }
      break;

    case 2:
      if (currentMillis - previousMillis >= 5000) 
      {
        previousMillis = currentMillis;
        digitalWrite(NS_Green, LOW);
        digitalWrite(NS_Yellow, HIGH);
        state = 3;
      }
      break;

    case 3:
      if (currentMillis - previousMillis >= 2000) 
      {
        previousMillis = currentMillis;
        digitalWrite(NS_Yellow, LOW);
        digitalWrite(NS_Red, HIGH);

        digitalWrite(EW_Green, HIGH);
        digitalWrite(EW_Yellow, LOW);
        digitalWrite(EW_Red, LOW);
        state = 0;
      }
      break;
  }
}
