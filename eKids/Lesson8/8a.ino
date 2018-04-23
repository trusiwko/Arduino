int v;

void setup()
{
  pinMode(A0, INPUT);
  pinMode( 9, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  v = analogRead(A0);
  if (v < 900) {
  	digitalWrite(9, HIGH);
  } else {
  	digitalWrite(9, LOW);
  }
  Serial.println(v);
  delay(300);
}
