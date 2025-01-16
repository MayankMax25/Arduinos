#define LED D4
#define button D6 
int temp=0;// temporary variable to check whether button is pressed or not 
const int buzzerPin=13;
const int buzzer=4;
void setup()
{
  pinMode(buzzerPin,OUTPUT);
  pinMode(buzzer,INPUT);
}

void loop()
{
  temp=digitalRead(buzzer);
  if (temp==HIGH)
  {
   digitalWrite(buzzerPin,HIGH);
   delay(10);
  }
  else
  {
    digitalWrite(buzzerPin,LOW);
    delay(10);
}
}