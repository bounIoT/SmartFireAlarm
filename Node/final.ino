#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ag_ismi "CMPE_IOT"
#define ag_sifresi "cmpeiot123"
#define IP "http://iotlab3group13.eu-gb.mybluemix.net"

dht DHT;

#define DHT11_PIN 7

#define ONE_WIRE_BUS 10
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


int buzzer = 12;
int smokePin = A1;
int gasPin = A2;
// Your threshold value
int sensorThres = 300;
char* id = "123123";


void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(smokePin, INPUT);
  pinMode(gasPin, INPUT);
  sensors.begin();
  
  Serial.begin(115200);               
  Serial.println("AT"); 
  
  delay(3000); 
 //analogReference(INTERNAL);
  if(Serial.find("OK")){         
     Serial.println("AT+CWMODE=1"); 
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial.println(baglantiKomutu);
    
     delay(5000);
 }
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  int tempOld=DHT.temperature;
  int hum=DHT.humidity;
  int smoke = analogRead(smokePin);
  int gas = analogRead(gasPin);
  
  sensors.requestTemperatures();
  int temp=(int)(sensors.getTempCByIndex(0));
  data_send(temp,hum,smoke,gas);

  if (smoke > sensorThres)
  {
    tone(buzzer, 1000);
  }
  else
  {
    noTone(buzzer);
  }
  
  delay(120000);
}

void data_send(int temp,int hum,int smoke,int gas){
 Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  
                                                                   
                                                                   
 delay(1000);
  if(Serial.find("Error")){     
   Serial.println("AT+CIPSTART Error");
    return;
  }
  
 String yollanacakkomut = "GET /data?&id=";
 yollanacakkomut += (id);
 yollanacakkomut +="&temp="; 
 yollanacakkomut += (temp);
 yollanacakkomut +="&humid=";
 yollanacakkomut += (hum);
 yollanacakkomut +="&smoke=";
 yollanacakkomut += (smoke);   
 yollanacakkomut +="&gas=";
 yollanacakkomut += (gas);                                   
 yollanacakkomut += " HTTP/1.1";
 yollanacakkomut += "\r\n";
 yollanacakkomut += "Host: iotlab3group13.eu-gb.mybluemix.net";
 yollanacakkomut += "\r\n";
 yollanacakkomut += "Accept: */*"; 
 yollanacakkomut += "\r\n\r\n";                                                   
 delay(1000);                                                                             
 
 Serial.print("AT+CIPSEND=");                  
 Serial.println(yollanacakkomut.length()+2);       
 
 delay(1000);
 
 if(Serial.find(">")){                           
                                                
 Serial.print(yollanacakkomut);
 Serial.print("\r\n\r\n");
 }
 else{
 Serial.println("AT+CIPCLOSE");
 }
}



