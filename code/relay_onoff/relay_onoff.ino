#include <DHT.h>

#define DHTPIN 2  // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11  // DHT 11

#define RELAY_PIN 3  // Digital pin connected to the relay

DHT dht(DHTPIN, DHTTYPE);

float temperatureThreshold = 24.0; // Threshold temperature
bool relayState = false; // Flag to store relay state

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  dht.begin();
}

void loop() {
  // Reading temperature
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temperature);

  // Check if temperature is above threshold
  if (temperature > temperatureThreshold && !relayState) {
    digitalWrite(RELAY_PIN, HIGH); // Turn on the relay
    relayState = true; // Update relay state flag
    Serial.println("Relay is ON");
  } else if (temperature <= temperatureThreshold && relayState) {
    digitalWrite(RELAY_PIN, LOW); // Turn off the relay
    relayState = false; // Update relay state flag
    Serial.println("Relay is OFF");
  }

  // Delay between readings
  delay(2000);
}
