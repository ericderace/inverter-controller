#include <Arduino.h>

const int Vin_pin32 = 32;
int ADC_Vin = 0;
float Vin = 0;

const int OnOff_pin = 33;
int ADC_OnOff = 0;
float OnOff = 0;

// Function prototypes
// *******************

/* Takes ADC input, returns voltage (float) by looking up calibration table
 example: voltage = adc_to_v(2755); */
float adc_to_v(uint16_t);

// Function definitions
// ********************

// ref https://stackoverflow.com/questions/7091294/how-to-build-a-lookup-table-in-c-sdcc-compiler-with-linear-interpolation
float adc_to_v(uint16_t x)
{
  /* NOTE: xs MUST be sorted */
  static const double xs[] = {0, 2470, 2624, 2775, 2940, 3124, 3328, 3665, 3840};
  static const double ys[] = {0, 9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5};

  /* number of elements in the array */
  static const int count = sizeof(xs) / sizeof(xs[0]);

  int i;
  double dx, dy;

  if (x < xs[0])
  {
    /* x is less than the minimum element
         * handle error here if you want */
    return ys[0]; /* return minimum element */
  }

  if (x > xs[count - 1])
  {
    return ys[count - 1]; /* return maximum */
  }

  /* find i, such that xs[i] <= x < xs[i+1] */
  for (i = 0; i < count - 1; i++)
  {
    if (xs[i + 1] > x)
    {
      break;
    }
  }

  /* interpolate */
  dx = xs[i + 1] - xs[i];
  dy = ys[i + 1] - ys[i];
  return ys[i] + (x - xs[i]) * dy / dx;
};

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
