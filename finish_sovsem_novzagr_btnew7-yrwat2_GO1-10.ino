//датчик уровня воды
int lol;
int lol_map = 0;
int outputValue = 0;
//блютуз
int kek;
int kek1;
//------------------------
//жк
#include <LiquidCrystal_I2C.h>
byte lampoff[8] = 
{
  B00000,
  B01100,
  B11100,
  B11100,
  B11100,
  B11100,
  B01100,
  B00000,
};
byte lampon[8] = 
{
  B00001,
  B01101,
  B11101,
  B11101,
  B11101,
  B11101,
  B01101,
  B00001,
};
byte p20[8] = 
{
  B00000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B10000,
  B00000,
};
byte p40[8] = 
{
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
};
byte p60[8] = 
{
  B00000,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B00000,
};
byte p80[8] = 
{
  B00000,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B11110,
  B00000,
};
byte p100[8] = 
{
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
};
byte on[8] = 
{
  B11111,
  B10001,
  B10101,
  B10101,
  B10101,
  B10101,
  B10001,
  B11111,
};

byte off[8] = 
{
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
};
LiquidCrystal_I2C lcd(0x3F, 16, 2);
//------------------------
//датчик темпиратуры земли
#include <OneWire.h>
OneWire  ds(10);  //  pin 10
//------------------------
//датчик влажности темпиратуры воздуха
#include <stDHT.h>
DHT sens (DHT11);
//------------------------
//датчик влажности земли
int aPin=0; // контакт подключения аналогового выхода датчика
int water_value=0; // переменная для сохранения значения датчика
int very_moist_value = 220; //327 значение изначально было
int water_value_percent = 0;
//------------------------
//датчик освещённости
int pinPhoto = 13;
int val = 0;
int val_per = 0;
//------------------------


void setup() {
Serial.begin(9600);
lcd.begin(); // инициализация жк
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print("     Hello! ");
lcd.createChar(0, p20);
lcd.createChar(1, p40);
lcd.createChar(2, p60);
lcd.createChar(4, p100);
lcd.createChar(7, off);
lcd.createChar(6, on);
lcd.createChar(5, lampoff);
lcd.createChar(3, lampon);
lcd.setCursor(0,1);
lcd.print("                ");
for (int i = 0; i<16; i++)
{
  for (int j = 0; j<5; j++)
  {
    lcd.setCursor(i,1);
    lcd.write(j);
    delay(20);
  }
}
delay(250);
lcd.setCursor(0, 0);
lcd.println(" - - - - - - - -");
lcd.setCursor(0, 1);
lcd.println("- - - - - - - - ");
delay(200);
lcd.setCursor(0, 0);
lcd.println("- - - - - - - - ");
lcd.setCursor(0, 1);
lcd.println(" - - - - - - - -");
delay(200);
lcd.setCursor(0, 0);
lcd.println(" - - - - - - - -");
lcd.setCursor(0, 1);
lcd.println("- - - - - - - - ");
delay(200);
lcd.setCursor(0, 0);
lcd.println("- - - - - - - - ");
lcd.setCursor(0, 1);
lcd.println(" - - - - - - - -");
delay(200);
lcd.setCursor(0, 0);
lcd.println("- - - - - - - - ");
lcd.setCursor(0, 1);
lcd.println(" - - - - - - - -");
delay(200);
//------------------------
//датчик влажности темпиратуры воздуха
pinMode(3, INPUT);
digitalWrite(3, HIGH);
//------------------------
pinMode(pinPhoto, INPUT );
//реле
pinMode(7, OUTPUT);     //включаем канал реле на 7 пине
pinMode(6, OUTPUT);     //включаем канал реле на 6 пине
pinMode(A1, INPUT);
kek = 0;
//------------------------
}

void loop() {   
kek1 = Serial.parseInt();
if (kek1!=kek && kek1!=0)
{
kek=kek1;
}
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);
  switch (kek) {
case 0:
    {//всё авт
 //датчик освещённости
  val = digitalRead(pinPhoto);
  lcd.setCursor(0, 0);
  if( val < 0.5)
  {
    digitalWrite(6, HIGH );
    lcd.print("Light:yes      \5");
    //Serial.println("Light:yes       ");
      }
  else
  {
    digitalWrite(6, LOW );
    lcd.print("Light:no       \3");
    //Serial.println("light:no        ");    
  } 
  lcd.setCursor(0, 1);
  //датчик влажности земли
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);  // Переводим показания датчика в проценты
 
  if (water_value < 500) 
      {        
       if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, HIGH);
        lcd.print("water value=" + String(water_value_percent) + "% \7");        
        //Serial.println("poliv:no        "); 
  } 

      }
    else
      {
               if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, LOW);
        lcd.print("water value=" + String(water_value_percent) + "% \6");
        //Serial.println("poliv:yes       ");
      }
      }
  //------------------------
  lcd.setCursor(0, 0);
  //------------------------
  delay(1350);
break;
    }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
case 1:
{//свет вкл насос авт
 //датчик освещённости
  val = digitalRead(pinPhoto);
  lcd.setCursor(0, 0);
  digitalWrite(6, LOW );
  lcd.print("Lamp:on        \3");
  //Serial.println("light:on        "); 
  lcd.setCursor(0, 1);
  //датчик влажности земли
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);  // Переводим показания датчика в проценты
  
  if (water_value < 500) 
      {        
       if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, HIGH);
        lcd.print("water value=" + String(water_value_percent) + "% \7");        
        //Serial.println("poliv:no        "); 
  } 

      }
    else
      {
               if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, LOW);
        lcd.print("water value=" + String(water_value_percent) + "% \6");
        //Serial.println("poliv:yes       ");
      }
      }
  //------------------------
  lcd.setCursor(0, 0);
  //------------------------
  delay(1350);
break;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
case 2:
{//свет авт насос вкл
//датчик освещённости
  val = digitalRead(pinPhoto);
  lcd.setCursor(0, 0);
  if( val < 0.5)
  {
    digitalWrite(6, HIGH );
    lcd.print("Light:yes      \5");
    //Serial.println("Light:yes       ");   
  }
  else
  {
    digitalWrite(6, LOW );
    lcd.print("Light:no       \3");
    //Serial.println("light:no        ");    
  } 
          lcd.setCursor(0, 1);
//датчик влажности земли
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);  // Переводим показания датчика в проценты
  
      if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, LOW);
        lcd.print("Pump: on       \7");
        //lcd.print("water value=" + String(water_value_percent) + "% \6");
        //Serial.println("poliv:on        ");
  }
  //------------------------
  lcd.setCursor(0, 0);
  //------------------------
  delay(1350);
break;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
case 3:
{//всё вкл
  //датчик освещённости
  val = digitalRead(pinPhoto);
  lcd.setCursor(0, 0);
  digitalWrite(6, LOW );
  lcd.print("Lamp:on        \3");
  //Serial.println("light:on        "); 
  lcd.setCursor(0, 1);
//датчик влажности земли
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);  // Переводим показания датчика в проценты
  
      if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, LOW);
        lcd.print("Pump: on       \7");
        //lcd.print("water value=" + String(water_value_percent) + "% \6");
        //Serial.println("poliv:on        ");
  }
  //------------------------
  lcd.setCursor(0, 0);
  //------------------------
  delay(1350);
break;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
case 4:
{//всё выкл
  //датчик освещённости
  val = digitalRead(pinPhoto);
  lcd.setCursor(0, 0);
  digitalWrite(6, HIGH );
  lcd.print("Lamp:off       \5");
  //Serial.println("light:pff       "); 
  lcd.setCursor(0, 1);
//датчик влажности земли
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);  // Переводим показания датчика в проценты
  
  digitalWrite(7, HIGH);
  lcd.print("Pump: off      \7");
  //lcd.print("water value=" + String(water_value_percent) + "% \7");
  //Serial.println("poliv:off       ");
  //------------------------
  lcd.setCursor(0, 0);
  //------------------------
  delay(1350);
break;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
case 5:
    {//всё авт
 //датчик освещённости
  val = digitalRead(pinPhoto);
  lcd.setCursor(0, 0);
  if( val < 0.5)
  {
    digitalWrite(6, HIGH );
    lcd.print("Light:yes      \5");
    //Serial.println("Light:yes       ");
      }
  else
  {
    digitalWrite(6, LOW );
    lcd.print("Light:no       \3");
    //Serial.println("light:no        ");    
  } 
  lcd.setCursor(0, 1);
  //датчик влажности земли
  int water_value = analogRead(aPin);                              // Считываем показания датчика(от 0 до 1023, где 1023 - сухо)
  int water_value_percent = map(water_value,very_moist_value,1023,100,0);  // Переводим показания датчика в проценты
 
  if (water_value < 500) 
      {        
       if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, HIGH);
        lcd.print("water value=" + String(water_value_percent) + "% \7");        
        //Serial.println("poliv:no        "); 
  } 

      }
    else
      {
               if (lol < 370)
  {
        digitalWrite(7, HIGH);
        lcd.print("End of water!   ");        
        //Serial.println("End of water!   ");
  }
  else
  {
        digitalWrite(7, LOW);
        lcd.print("water value=" + String(water_value_percent) + "% \6");
        //Serial.println("poliv:yes       ");
      }
      }
  //------------------------
  lcd.setCursor(0, 0);
  //------------------------
  delay(1350);
break;
    }
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

  //------------------------
  //lcd.setCursor(0, 0);
  //датчик влажности темпиратуры воздуха
  int t = sens.readTemperature(3);
  int h = sens.readHumidity(3);
  lcd.print("Hum air:" + String(h) + "%""     ");

  lcd.setCursor(0, 1);
  lcd.print("Temp air:" + String(t) + "C    ");

  //------------------------
  delay(1350);
  lcd.setCursor(0, 0);
   //датчик темпиратуры земли
  byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius, fahrenheit; 
  if ( !ds.search(addr)) {
    ds.reset_search();
    //return;
  }
  //for( i = 0; i < 8; i++) {
  //}
  if (OneWire::crc8(addr, 7) != addr[7]) {   
      return;
  }
  // the first ROM byte indicates which chip
 
      type_s = 0;
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);        // start conversion, with parasite power on at the end
  present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);         // Read Scratchpad
  for ( i = 0; i < 9; i++) {           // we need 9 bytes
    data[i] = ds.read(); 
  }
  int16_t raw = (data[1] << 8) | data[0];
  if (type_s) {
    raw = raw << 3; // 9 bit resolution default
    if (data[7] == 0x10) {
      // "count remain" gives full 12 bit resolution
      raw = (raw & 0xFFF0) + 12 - data[6];
    }
  } else {
    byte cfg = (data[4] & 0x60);
    // at lower res, the low bits are undefined, so let's zero them
    if (cfg == 0x00) raw = raw & ~7;  // 9 bit resolution, 93.75 ms
    else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
    else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
    //// default is 12 bit resolution, 750 ms conversion time
  }
  celsius = (float)raw / 16.0;
  lcd.print("Temp G=" + String(celsius) + "C   ");
  //lcd.print("bluetooth val=" + String(kek1));
 Serial.println ("Temperature G=" + String(celsius) + "C   ");
  //------------------------
  lcd.setCursor(0, 1);
  //датчик уровня воды
  lol = analogRead(A1);
  outputValue = map(lol,0, 570, 0, 100);

  //Serial.println (lol);
  lcd.print("Water lvl=" + String(outputValue)+ "%        ");
  //lcd.print(String(lol))
  //------------------------
  delay(1350);
  lcd.setCursor(0, 0);
  lcd.println(" - - - - - - - -");
  lcd.setCursor(0, 1);
  lcd.println("- - - - - - - - ");
  delay(300);
  lcd.setCursor(0, 0);
  lcd.println("- - - - - - - - ");
  lcd.setCursor(0, 1);
  lcd.println(" - - - - - - - -");
  delay(300);
  lcd.setCursor(0, 0);
  lcd.println(" - - - - - - - -");
  lcd.setCursor(0, 1);
  lcd.println("- - - - - - - - ");
    delay(350);
      //val_per = map(val,0, 1, 0, 1);
    //Serial.println("Light=" + String(val_per) + "%");
    Serial.println("s");
    Serial.println("Влажность воздуха =" + String(h) + "%");
    Serial.println("Температура воздуха =" + String(t) + "C    ");
    Serial.println("Температура земли =" + String(celsius) + "C   ");
    Serial.println("Влажность земли =" + String(water_value_percent) + "%  ");
    Serial.println("Уровень воды в баке =" + String(outputValue)+ "%        ");
    Serial.println("               ");
    Serial.println("- - - - - - - - ");
    Serial.println("f");

  //-----------------------
}
