const int Vin_pin32 = 32;
int ADC_Vin = 0;
float Vin = 0;

const int OnOff_pin = 33;
int ADC_OnOff = 0;
float OnOff = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
void loop()
{

  ADC_Vin = analogRead(Vin_pin32);
  ADC_OnOff = analogRead(OnOff_pin);

  Serial.print("ADC Vin =");
  Serial.println(ADC_Vin);
  Serial.print("ADC OnOff = ");
  Serial.println(ADC_OnOff);
  Vin = (ADC_Vin * 0.0031343);
  Serial.print("Vin = ");
  Serial.print(Vin, 1);
  Serial.println("v");
  // inverter status
  if (ADC_OnOff == 0.0)
  {
    Serial.println("Inverter On");
  }
  else
  {
    Serial.println("Inverter Off");
  }

  // to close
  if (ADC_Vin < 2855.0 && ADC_OnOff < 1600.0)
  {
    delay(1000);
    if (ADC_Vin < 2855.0 && ADC_OnOff < 1600.0)
    {
      Serial.println("Turning OFF");
      digitalWrite(13, HIGH);
      delay(500);
      digitalWrite(13, LOW);
    }
  }

  // to awake
  if (ADC_Vin > 3220.0 && ADC_OnOff >= 1600.0)
  {
    delay(1000);
    if (ADC_Vin > 3220.0 && ADC_OnOff >= 1600.0)
    {
      Serial.println("Turning ON");
      digitalWrite(13, HIGH);
      delay(550);
      digitalWrite(13, LOW);
    }
  }
  delay(500);
  ADC_Vin = analogRead(Vin_pin32);
  ADC_OnOff = analogRead(OnOff_pin);

  Serial.print("ADC Vin =");
  Serial.println(ADC_Vin);
  Serial.print("ADC OnOff = ");
  Serial.println(ADC_OnOff);
  Vin = (ADC_Vin * 0.0031343);
  Serial.print("Vin = ");
  Serial.print(Vin, 1);
  Serial.println("v");

  // inverter status
  if (ADC_OnOff == 0.0)
  {
    Serial.println("Inverter On");
  }
  else
  {
    Serial.println("Inverter Off");
  }
  Serial.println("Fuck Ya!");
  Serial.println(".");

  delay(1000);
}

//   >   <
