#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial SIM900(3, 5);
SoftwareSerial GPS(7, 8);

TinyGPSPlus gps;  

double latitude;
double longitude;

void setup() {     
  SIM900.begin(9600);
  Serial.begin(9600); 
  GPS.begin(9600);
  Serial.println("power up" );
  setupConn();
}

void loop()
{
        GPS.listen();
        
        smartDelay(1000); 
        
        bool valid;
        latitude = gps.location.lat(); 
        valid = gps.location.isValid(); 
        longitude = gps.location.lng();  
        if (!valid){          
          Serial.print("Latitude : ");
          Serial.println("*****");
          Serial.print("Longitude : ");
          Serial.println("*****");
        }
        else{
          Serial.print("Latitude in Decimal Degrees : ");
          Serial.println(latitude, 6);
          Serial.print("Longitude in Decimal Degrees : ");
          Serial.println(longitude, 6);
          Serial.println("SubmitHttpRequest - started" );
          SubmitHttpRequest();
          Serial.println("SubmitHttpRequest - finished" );
        }
}

void setupConn(){
  SIM900.listen();
  delay(1000);
  SIM900.println("AT+CSQ"); 
  delay(100);
  ShowSerialData();
  
  SIM900.println("AT+CGATT?"); 
  delay(100);
  ShowSerialData();
  
  SIM900.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=3,1,\"APN\",\"CMNET\"");
  delay(1000);
  ShowSerialData();
 
  SIM900.println("AT+SAPBR=1,1");
  delay(1000);
  ShowSerialData();
 
  SIM900.println("AT+HTTPINIT"); 
  delay(1000); 
  ShowSerialData();
  
}


void SubmitHttpRequest()
{
  
  SIM900.listen(); 
  delay(1000);
  SIM900.write("AT+HTTPPARA=\"URL\",\"prasanthdondeti.000webhostapp.com/index.php?lat=");
  SIM900.print(String(latitude,7));
  SIM900.write("&lon=");
  SIM900.print(String(longitude,7));
  SIM900.write("\"\r\n");
  delay(3000);
  ShowSerialData();
 
  SIM900.println("AT+HTTPACTION=0");
  delay(3000);
  while(!SIM900.available());
  ShowSerialData();
 
  SIM900.println("AT+HTTPREAD");
  delay(3000);
  ShowSerialData();
 
}
 
void ShowSerialData()
{
  while(SIM900.available()!=0)
    Serial.write(char(SIM900.read()));
  Serial.println();
}


static void smartDelay(unsigned long ms){
  unsigned long start = millis();
  do{
    while (GPS.available())  
      gps.encode(GPS.read());
  } while (millis() - start < ms);
}
