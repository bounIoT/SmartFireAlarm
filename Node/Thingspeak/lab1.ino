#include <dht.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ag_ismi "Yusufcan"
#define ag_sifresi "qcgc9192"
#define IP "184.106.153.149"    //thingspeak.com IP adresi

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
int sensorThres = 400;


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
  
  delay(30000);
}

void data_send(int temp,int hum,int smoke,int gas){
 Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  
                                                                   
                                                                   
 delay(1000);
  if(Serial.find("Error")){     
   Serial.println("AT+CIPSTART Error");
    return;
  }
  
 String yollanacakkomut = "GET /update?key=XO1JZDQFQ5B0C4IO&field1=";  
 yollanacakkomut += (temp);
 yollanacakkomut +="&field2=";
 yollanacakkomut += (hum);
 yollanacakkomut +="&field3=";
 yollanacakkomut += (smoke);   
 yollanacakkomut +="&field4=";
 yollanacakkomut += (gas);                                   
 yollanacakkomut += "\r\n\r\n";                                             
  delay(3000);                                                                             
 
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

