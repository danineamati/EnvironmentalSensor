#define aref_voltage 3.3

int TMP36_temp_pin = 1; // Analog pin 1
int TMP36_temp_val = 0;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Read temp value
  TMP36_temp_val = analogRead(TMP36_temp_pin); // Raw analog out (0 - 1023)
  Serial.println(TMP36_temp_val);
  // Convert to voltage
  float volts = TMP36_temp_val * 3.3 / 1024.0;
  Serial.print(volts);
  Serial.println(" V");

  // Convert to Celcius (10 mV / DEG C where 500 mV = 0C)
  float tempC = (volts * 100) - 50;
  // COnvert Celcius to Fahrenheit
  float tempF = (tempC * 9.0 / 5.0) + 32.0;
 

  // Print value to serial
  Serial.print(tempC);
  Serial.print(" oC = ");
  Serial.print(tempF); 
  Serial.println(" oF");

  delay(1000);
}
