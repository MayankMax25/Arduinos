// C++ code
//
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500); // Wait for 500 millisecond(s)
  digitalWrite(LED_BUILTIN, LOW);
  delay(500); // Wait for 500 millisecond(s)
}