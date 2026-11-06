#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ---------------- PIN DEFINITIONS ----------------
#define DHT_PIN     4
#define DHT_TYPE    DHT22

#define PIR_PIN     27
#define LED_PIN     26
#define BUZZER_PIN  25
#define RELAY_PIN   33

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// ---------------- OBJECTS ----------------
DHT dht(DHT_PIN, DHT_TYPE);

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

// ---------------- THRESHOLDS ----------------
const float TEMP_LIMIT = 40.0;
const float HUM_LIMIT  = 80.0;

// ---------------- SETUP ----------------
void setup()
{
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);

  dht.begin();

  if (!display.begin(
        SSD1306_SWITCHCAPVCC,
        0x3C))
  {
    Serial.println("OLED initialization failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(10, 20);
  display.println("HOME SAFETY");
  display.setCursor(10, 35);
  display.println("SYSTEM STARTING");

  display.display();

  delay(2000);
}

// ---------------- LOOP ----------------
void loop()
{
  // Read sensors
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int motion = digitalRead(PIR_PIN);

  // Check DHT22 reading
  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT22 reading failed");
    return;
  }

  // ---------------- SERIAL MONITOR ----------------

  Serial.println("----------------------------");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Motion: ");

  if (motion == HIGH)
    Serial.println("DETECTED");
  else
    Serial.println("NONE");

  // ---------------- SAFETY LOGIC ----------------

  bool highTemperature = temperature > TEMP_LIMIT;
  bool highHumidity = humidity > HUM_LIMIT;
  bool motionDetected = motion == HIGH;

  bool abnormalCondition =
      highTemperature ||
      highHumidity ||
      motionDetected;

  // ---------------- OUTPUT CONTROL ----------------

  if (abnormalCondition)
  {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else
  {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Relay only for environmental danger
  if (highTemperature || highHumidity)
  {
    digitalWrite(RELAY_PIN, HIGH);
  }
  else
  {
    digitalWrite(RELAY_PIN, LOW);
  }

  // ---------------- OLED ----------------

  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("HOME SAFETY MONITOR");

  display.drawLine(
    0, 10,
    127, 10,
    SSD1306_WHITE
  );

  display.setCursor(0, 15);
  display.print("Temp : ");
  display.print(temperature, 1);
  display.println(" C");

  display.setCursor(0, 27);
  display.print("Hum  : ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 39);
  display.print("Motion: ");

  if (motionDetected)
    display.println("DETECTED");
  else
    display.println("NONE");

  display.setCursor(0, 51);

  if (highTemperature)
  {
    display.println("ALERT: HIGH TEMP");
  }
  else if (highHumidity)
  {
    display.println("ALERT: HIGH HUM");
  }
  else if (motionDetected)
  {
    display.println("ALERT: MOTION");
  }
  else
  {
    display.println("STATUS: SAFE");
  }

  display.display();

  delay(1000);
}