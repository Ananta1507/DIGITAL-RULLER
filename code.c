// LCD 16 x 2 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 18;
const int echoPin = 5;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

/*Sebagai referensi, dalam kondisi standar pada suhu kamar, 
kecepatan suara di udara kering sekitar 343 meter per detik atau 
sekitar 0.343 meter per milidetik (343 m/s atau 0.343 mm/ms).

Referensi kalibrasi yang diberikan (0.393701) konversi dari 
sentimeter (cm) ke inci (inchi). Ini digunakan dalam perhitungan 
konversi antara dua sistem pengukuran yang berbeda.

Contoh:
Untuk mengonversi 10 sentimeter ke inci: 10 cm * 0.393701 = 3.93701 inci.
Untuk mengonversi 5 inci ke sentimeter: 5 inchi / 0.393701 = 12.7 sentimeter.
*/


long duration;
float distanceCm;
float distanceInch;

//


void setup() {
  Serial.begin(115200); // Starts the serial communication
  lcd.init();
  lcd.clear(); 
  lcd.backlight();
  lcd.setCursor(0,0);   
  lcd.print("Deteksi Sensor : ");
  lcd.setCursor(0,1);   
  lcd.print("HC-SR04");
  delay(5000);
  lcd.clear();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  lcd.clear();
  lcd.setCursor(0,0);   
  lcd.print("Jarak:"+String(distanceCm));
  lcd.print(" ");
  lcd.print("Cm");
  
  if(distanceCm < 20){
    Serial.println("Jarak Sangat Dekat" );
    lcd.setCursor(0,1);   
    lcd.print("Jarak < 20 cm");
  }
  if(distanceCm >= 21 && distanceCm <=30){
    Serial.println("Jarak Semakin Dekat");
    lcd.setCursor(0,1);   
    lcd.print("Jarak 21-30 Cm");
  }
  if(distanceCm > 30){
    Serial.println("Jarak Cukup Jauh" );
    lcd.setCursor(0,1);   
    lcd.print("Jarak > 30 cm");
  }  
  delay(2000);
 }
