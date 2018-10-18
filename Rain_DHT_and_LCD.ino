#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C LCD 객체 선언

#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

int Raindrops_pin = A0; // 빗방울센서 핀을 A0으로 설정 
int Rain_Value;
int Latest_Rain_Value;
float humidity;
float temperature;


byte customChar[] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

DHT dht(DHTPIN , DHTTYPE);

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  //Latest_Rain_Value = Rain_Value;
  lcd.createChar(0, customChar);
}

void loop() {
  Rain_Value = analogRead(A0);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  
  Rain_Update();
  DHT_Update();
  
  /*lcd.setCursor(0, 1);
  delay(300);
  lcd.cursor();
  lcd.setCursor(1, 1);
  delay(300);
  lcd.cursor();
  lcd.setCursor(1, 0);
  delay(300);
  lcd.cursor();
  lcd.setCursor(0, 0);
  delay(300);
  lcd.cursor();*/
  delay(500);
}

void Rain_Update() {
  
  if(Latest_Rain_Value != Rain_Value) {
    Latest_Rain_Value = Rain_Value;
    lcd.clear();
  }
  if(Latest_Rain_Value <= 330) {
    //
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Take Umbrella");
    }
    else {
      //lcd.setCursor(2, 1);
      lcd.clear();
      lcd.setCursor(2, 1);
      lcd.print("It's clear");
    }
}

void DHT_Update() {
  //lcd.setCursor(0, 0);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print((int)temperature);
  lcd.write(0);
  lcd.print("C ");
  lcd.print((int)humidity);
  lcd.print("%");
}
