#include <WiFi.h>
#include <FirebaseESP32.h>
#include <LiquidCrystal_I2C.h>

// Firebase database credentials
#define FIREBASE_HOST "db-url"
#define FIREBASE_AUTH "database-secret"

// WiFi credentials
#define WIFI_SSID "poco"
#define WIFI_PASSWORD "123456789"

// Firebase database object
FirebaseData firebaseData;

// LCD object
LiquidCrystal_I2C lcd(0x3F,16,2);

void setup() {
  Serial.begin(9600);

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Set float values to Firebase database
  Firebase.setFloat(firebaseData, "/data/cpu", 0.00);
  Firebase.setFloat(firebaseData, "/data/ram", 0.00);
  Firebase.setFloat(firebaseData, "/data/ram2", 0.00);

  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  // Read float values from Firebase database
//  float cpu = Firebase.getFloat(firebaseData, "/data/cpu");
//  float ram = Firebase.getFloat(firebaseData, "/data/ram");
//  float used_ram = Firebase.getFloat(firebaseData, "/data/ram2");

  String cpu = (Firebase.getFloat(firebaseData, F("/data/cpu")) ? String(firebaseData.to<float>()).c_str() : firebaseData.errorReason().c_str());
  String ram = (Firebase.getFloat(firebaseData, F("/data/ram")) ? String(firebaseData.to<float>()).c_str() : firebaseData.errorReason().c_str());
  String used_ram = (Firebase.getFloat(firebaseData, F("/data/ram2")) ? String(firebaseData.to<float>()).c_str() : firebaseData.errorReason().c_str());
  

  // Print float values
  Serial.print("CPU usage : ");
  Serial.println(cpu);
  Serial.print("RAM usage : ");
  Serial.println(ram);
  Serial.print("Used RAM (GB) : ");
  Serial.println(used_ram);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CPU");
  lcd.setCursor(6,0);
  lcd.print("RAM");
  lcd.setCursor(12,0);
  lcd.print("USE");
  lcd.setCursor(0,1);
  lcd.print(cpu);
  lcd.setCursor(6,1);
  lcd.print(ram);
  lcd.setCursor(12,1);
  lcd.print(used_ram);

  delay(1);
}
