
void setup()
{
	Serial.begin(9600);
	Serial.println("Hello.");
	analogReference(INTERNAL);
	pinMode(8,OUTPUT);
}

int get_current()
{
  return (int) ((1100.0*(double) analogRead(A0))/(1023.0*75.0));
}


int pwm = 140;
void loop()
{
int current;
	
	if (digitalRead(8))
	   digitalWrite(8,0);
	else
	   digitalWrite(8,1);
	   
	analogWrite(3, pwm);
	current = get_current();
	if (current > 10) pwm = pwm - 1;
	if (current < 10) pwm = pwm + 1;
	Serial.print(pwm);
	Serial.print(" =>  ");
	Serial.print(current);
	Serial.println("mA");
	delay(1000);
}
