#include <TinyGPS++.h> //Libary TinyGPS
#include <SoftwareSerial.h> //Libarary bawaan

// Choose two Arduino pins to use for software serial
int RXPin = 2; //Connect ke TX GPS
int TXPin = 3; //Connect ke RX GPS

int GPSBaud = 9600; //Biarin default

// Membuat objek TinyGPS++
TinyGPSPlus gps;

// Mmebuat koneksi serial dengan nama "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  //Memulai koneksi serial pada baudrate 9600
  Serial.begin(9600);

  //Memulai koneksi serial dengan sensor
  gpsSerial.begin(GPSBaud);
}

void loop()
{
  //Membuat tampilan data ketika terdapat koneksi
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // Jika dalam 5 detik tidak ada koneksi, maka akan muncul error "No GPS detected"
  // Periksa sambungan dan reset arduino
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}
