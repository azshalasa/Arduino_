////////////////////////////////////////////////////
////// SETUP - SD-MODULE ///////////////////////////
////////////////////////////////////////////////////
// CS - Pin 53
// MOSI - Pin 51
// SCK - Pin 52
// MISO - Pin 50
////////////////////////////////////////////////////
////// SETUP - DHT-MODULE///////////////////////////
////////////////////////////////////////////////////
// MIDPIN - A1
////////////////////////////////////////////////////
////// SETUP - BMP085-MODULE////////////////////////
////////////////////////////////////////////////////
// VCC - 3.3v
// SCL - 21
// SDA - 20
////////////////////////////////////////////////////
////////////////////////////////////////////////////


#include <SD.h>
#include "DHT.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

#define DHTPIN A1
#define DHTTYPE DHT11

int looping;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

const int chipSelect = 53;

void setup() {
  // Abre a porta serial e aguarda para conexão
  Serial.begin(9600);
  dht.begin();
  looping = 0;
  
  while (!Serial) {
    ; // Espera a serial port abrir
  }

  // Check na Inicialização do sensor de pressão
  if (!bmp.begin()) {
  Serial.println("Sensor BMP085 nao encontrado, certifique-se das conexoes!");
  while (1) {}
  }

  // Check na Inicialização do módulo SD  
  Serial.print("Inicializando SD card...");
  pinMode(53, OUTPUT);
  
  if (!SD.begin(chipSelect)) {
    Serial.println("Inicialização do SD falhou...!");
    return;
  }
  Serial.println('\n');
  Serial.println("Inicializacao completa...");
  
}

void loop() {
  delay(2000);
  
  File myFile = SD.open("datalog.txt", FILE_WRITE);
  
  delay(1000);
  
  // Se o .txt estiver aberto, escreva dentro
  if (myFile) {
    Serial.print("Escrevendo dados...");

    myFile.println("################################################################");
    myFile.println('\n'); 
    myFile.println("O Looping ocorre acada 01 minutos:");
    myFile.println('\n');     
    myFile.println("Looping:");
    myFile.println(looping);
    myFile.println('\n'); 

    myFile.println("#################### Sensor DHT ################################");
    myFile.println('\n');       
    myFile.println("Umidade:");
        Serial.print('\n');
        Serial.print(dht.readHumidity());
    myFile.println(dht.readHumidity());
    myFile.println('\n');
    myFile.println("Temperatura:");
        Serial.print('\n');
        Serial.print(dht.readTemperature());
    myFile.println(dht.readTemperature());
    myFile.println('\n');
    
    myFile.println("#################### Sensor BMP180 #############################");
    myFile.println('\n');       
    myFile.println("Temperatura:");
        Serial.print('\n');
        Serial.print(bmp.readTemperature());
    myFile.println(bmp.readTemperature());
    myFile.println('\n'); 
    myFile.println("Pressao:");
        Serial.print('\n');
        Serial.print(bmp.readPressure());
    myFile.println(bmp.readPressure());
        Serial.print('\n');
        Serial.print('\n');
    myFile.println("Pa:");
    myFile.println('\n'); 
    myFile.println("Altitude:");
        Serial.print('\n');
        Serial.print(bmp.readAltitude(101500));
    myFile.println(bmp.readAltitude(101500));
    myFile.println("Metros");
    myFile.println('\n');
    myFile.println("Sea Level:");
        Serial.print('\n');
        Serial.print(bmp.readSealevelPressure());
    myFile.println(bmp.readSealevelPressure());  
    myFile.println('\n');                
    myFile.println("################################################################");
    delay(1000);

    // Fexa o .txt
    myFile.close();
    Serial.print('\n');
    Serial.println("Concluido.");
    Serial.print("Looping:");
    Serial.print(looping);
    Serial.println('\n');

  } 
  else {
    Serial.println("Erro em abrir .txt");
  }  
looping++;  
}
