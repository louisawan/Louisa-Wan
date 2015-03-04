int redPin = 9;
int greenPin = 10;
int bluePin = 11;
int toySwitch = A0;
int dogSwitch = 3;
int sensorValue = 0;
int toyValue = 0;
int fadeValue = 250;
int previousState;
int currentState;
bool stopTimer = true;
int timeStamp;
int getSeconds;
int state;
int secondMarker;
int isHungry;
//long timeStamp;
void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // pinMode(piezo, OUTPUT);
  pinMode(dogSwitch, INPUT);
  pinMode(toySwitch, INPUT);
  Serial.begin(9600);
  analogWrite(greenPin, 250);
  digitalWrite(bluePin, LOW);
  digitalWrite(redPin, LOW);
  state = 0;
  fadeValue = 250;
  isHungry = false;
}

int noSwitch = true;
void loop() {  // Check input
  sensorValue = digitalRead(dogSwitch);
  toyValue = analogRead(toySwitch);
  int s = seconds(millis());
  Serial.println(sensorValue);
  if (state == 0)
  {
    if (sensorValue)
    {
      SingleBlinker(10, 100, 5);
    }
    for (fadeValue = 250; fadeValue >= 0; fadeValue -= 10)
    {
      int food = analogRead(toySwitch);
      if (food)
      {
        SingleBlinker(11, 100, 5);
      }
      analogWrite(greenPin, fadeValue);
      delay(500);
      if (fadeValue <= 0)
      {
        state = 1;
        timeStamp = getTimeStamp();
        stopTimer = false;
        isHungry = true;
      }

    }
  }

  if (state == 1); // Hungry State
  {
    digitalWrite(redPin, HIGH);
    if (sensorValue)
    { state = 0;
      digitalWrite(redPin, LOW);
      secondMarker = 0;
    }
    int hungerDuration = timer(timeStamp, 30);
    // Serial.println(hungerDuration);
    // Blink slowly after ten seconds
    if (hungerDuration == 9) // +1 = 10 seconds
    {
      secondMarker = 9;
    }
    if (hungerDuration == 29)
    {
      secondMarker = 29;
    }

    if ( secondMarker == 9)
    {
      SingleBlinker(9, 500, 1);
    }
    if (secondMarker == 29)
    {
      SingleBlinker(9, 100, 1);
    }
    // Blink faster after ten seconds, timer starts at 29
  }

}

////////////////////////////////////

// Convert millisecond to seconds
int seconds(long mSecond)
{
  return mSecond / 1000;
}

bool isGet;
long getTimeStamp()
{
  long timeStamp = millis() / 1000;
  return timeStamp;
}

int timer(int tStamp, int countdown)
{
  if (!stopTimer)
  {
    long timerSeconds = seconds(millis()) - tStamp;
    if (timerSeconds == countdown)
      stopTimer = true;
    else
      return timerSeconds;
  }
}

void Fader(int pinNumber, int fadeValue, int decrement)
{
  if (fadeValue >= 0)
  {
    for (fadeValue; fadeValue >= 0; fadeValue -= decrement)
    {
      analogWrite(pinNumber, fadeValue);
      delay(100);
    }
  }
}

void SingleBlinker(int pinNumber, int interval, int blinkTimes)
{
  for (int i = 0; i < blinkTimes; i++)
  {
    digitalWrite(pinNumber, HIGH);
    delay(interval);
    digitalWrite(pinNumber, LOW);
    delay(interval);
  }
}
void Blinker(int pinNumber1, int pinNumber2, int interval)
{
  for (int i = 0; i < 5 ; i++)
  {
    digitalWrite(pinNumber1, HIGH);
    digitalWrite(pinNumber2, HIGH);
    delay(interval);
    digitalWrite(pinNumber1, LOW);
    digitalWrite(pinNumber2, LOW);
    delay(interval);
  }
}

//bool isTen (int seconds)
//{
//  if (seconds % 10 == 0)
//    return true;
//  else
//    return false;
//}


