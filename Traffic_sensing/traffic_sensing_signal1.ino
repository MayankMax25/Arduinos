// C++ code

int temp1=0;
int temp2=0;
int led3=13;
int led2=12;
int led1=8;
int switch1=4;
int switch2=2;

void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(switch1,INPUT);
  pinMode(switch2,INPUT);
}

void loop()
{temp1=digitalRead(switch1);
 temp2=digitalRead(switch2);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  if (temp1==HIGH && temp2==HIGH){
    delay(2000);}
  else{
    delay(500);}
  digitalWrite(led2, HIGH);
  digitalWrite(led1, LOW);
  digitalWrite(led3, LOW);
  delay(500);
  digitalWrite(led3, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led1, LOW);
  delay(500);
} 