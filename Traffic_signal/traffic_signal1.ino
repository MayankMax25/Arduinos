// C++ code
//
int led1=13;
int led2=12;
int led3=8;
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}

void loop()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  delay(1000);
  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  delay(1000);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led1, LOW);
  delay(1000);
} 