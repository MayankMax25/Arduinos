#define LED D4
#define button D6 
int temp=0;// temporary variable to check whether button is pressed or not 
int buttonPin=13;
int led=4;
void setup()
{
  pinMode(buttonPin,OUTPUT);
  pinMode(led,INPUT);
}

void loop()
{
  temp=digitalRead(led);
  if (temp==HIGH)
  {
   digitalWrite(buttonPin,HIGH);
   delay(10);
  }
  else
  {
    digitalWrite(buttonPin,LOW);
    delay(10);
}
}