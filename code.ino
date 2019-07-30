#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Enter your project auth code";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wi-FI name";
char password[] = "password";

#define DHTPIN D7          // What digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

float mq135;
float lm35;
float mq2;
float soilsensor;
int pump=D4;
int fan=D5;
float ldr;
float h;
float t;
float light=D6;
int a=0;
int j=0;
int k=0;
int a1=0;
int displayState = 0; 
unsigned long previousMillis1 = 0;        // will store last time Display was updated
long interval = 3000; // m


unsigned long previousMillis2 = 0;       // will store last time Time was updated
long OnTime = 100;           // milliseconds of on-time
long OffTime = 200;          // milliseconds of off-time
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
#define MUX_A D3
#define MUX_B D2
#define MUX_C D1

#define ANALOG_INPUT A0

void sendSensor()
{
   h = dht.readHumidity();
   t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  }
WiFiClient client; // Create a client that can connect to a specified internet IP address and port
unsigned long myChannelNumber = 524562; // ThingSpeak channel number
const char * myWriteAPIKey = "LPWFELUJIPDBFOBJ"; // ThingSpeak API write key
WidgetLCD lcd(V1);
void setup()
{
  // Debug console
  pinMode(MUX_A, OUTPUT);
  pinMode(MUX_B, OUTPUT);     
  pinMode(MUX_C, OUTPUT);
  Serial.begin(115200); // Start the Serial communication to send messages to the computer
  delay(1000);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
pinMode(D8,INPUT);
  Blynk.begin(auth, ssid, password);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
   timer.setInterval(4000L, sendSensor1);
  timer.setInterval(6000L,lcddisplay );
  timer.setInterval(10000L,thingspeak );
    
   // Connect to Wi-Fi network
  Serial.println('\n');
  WiFi.begin(ssid, password); // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) // Wait for the Wi-Fi to connect
  {
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }
  Serial.println('\n');
  Serial.println("HI USER YOUR ONLINE GET READY!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP()); // Send the IP address of the ESP8266 to the computer
  Serial.println('\n');
  ThingSpeak.begin(client); // Connect to the Cloud through ThingSpeak

}

void changeMux(int c, int b, int a) {
  digitalWrite(MUX_A, a);
  digitalWrite(MUX_B, b);
  digitalWrite(MUX_C, c);
}
void sendSensor1()
{
  changeMux(LOW, LOW, LOW);//0
  mq135 = analogRead(A0); //reading the sensor on A0
  Blynk.virtualWrite(V7, mq135); //sending to Blynk
  if(mq135>600)
  {
    digitalWrite(D5,LOW);
     if(a==0)
    {
      Blynk.email("saiganesh223468@gmail.com","Exhaust Fan","Poor Air quality or Temperature is more");
      Blynk.notify("Poor Air quality or Temperature is more");
  // Blynk.email("mobilenumber@ideacelluar.net","exhaust fan","poor air quality");
      a++;
    }
  }
  else if(mq135<600)
  {
    digitalWrite(D5,HIGH);
    a=0;
  }
 /* if(t>30)
  {
    digitalWrite(D5,LOW);
     if(a1==0)
    {
      Blynk.email("saiganesh223468@gmail.com","Exhaust Fan","Temperature is more");
      Blynk.notify(" Temperature is more");
      a1++;
    }
  }
  else if(mq135<600)
  {
    digitalWrite(D5,HIGH);
    a1=0;
  }*/
  changeMux(LOW, LOW, HIGH);//1
  lm35 = analogRead(A0); //reading the sensor on A0
  Blynk.virtualWrite(V8, lm35); //sending to Blynk
  
  changeMux(LOW, HIGH, LOW);//2
  mq2 = analogRead(A0); //reading the sensor on A0
  Blynk.virtualWrite(V9, mq2); //sending to Blynk
 
  //changeMux(LOW, HIGH, HIGH);//3
  ldr = digitalRead(D8); //reading the sensor on A0
  Blynk.virtualWrite(V10, ldr); //sending to Blynk
  if(ldr==HIGH)
      {
        digitalWrite(D6,LOW);
        if(k==0)
    {
      Blynk.email("saiganesh223468@gmail.com"," Lights","Lights on!!");
      Blynk.notify("Lights on!!");
   //Blynk.email("mobilenumber@ideacelluar.net","lights","lights on");
      k++;
    }
      }
else if(ldr==LOW)
  {
    digitalWrite(D6,HIGH);
    k=0;
  }  
  
  changeMux(HIGH, LOW, LOW);//4
  soilsensor = analogRead(A0); //reading the sensor on A0
  Blynk.virtualWrite(V11, soilsensor); //sending to Blynk
  if(soilsensor>600)
    {
      digitalWrite(D4,LOW);
      if(j==0)
    {
      Blynk.email("saiganesh223468@gmail.com"," Water Pump","Pump Started Watering Plants");
      Blynk.notify("Pump Started Watering Plants");
     //Blynk.email("mobilenumber@ideacelluar.net","water pump","water started pumping");
      j++;
    }
    }
    else if(soilsensor<650)
  {
    digitalWrite(D4,HIGH);
    j=0;
  }
}
  



void lcddisplay()
{
  unsigned long currentMillis = millis();
 
  if((displayState  == 0) && (currentMillis - previousMillis1 >= interval))
  {
    displayState = 1;  // Turn it off
    lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "Air Quality is:"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(1, 1, mq135);
  }
   else if ((displayState == 1) && (currentMillis - previousMillis1 >= interval))
  {
    displayState = 2;  // turn it on
    previousMillis1 = currentMillis;   // Remember the time
    lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(1, 0, "Temperature is:"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(2, 1, t);
  }
  else if ((displayState == 2) && (currentMillis - previousMillis1 >= interval))
  {
    displayState = 3;  // turn it on
    previousMillis1 = currentMillis;   // Remember the time
  lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(2, 0, "MQ-2 value is:"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(3, 1, mq2);
  }
  else if ((displayState == 3) && (currentMillis - previousMillis1 >= interval))
  {
    displayState = 4;  // turn it on
    previousMillis1 = currentMillis;   // Remember the time
    lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(3, 0, "ldr value is:"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(4, 1, ldr);
  }
  else if((displayState  == 4) && (currentMillis - previousMillis1 >= interval))
  {
    displayState = 0;  // Turn it off
    lcd.clear(); //Use it to clear the LCD Widget
  lcd.print(0, 0, "soilsensor value:"); // use: (position X: 0-15, position Y: 0-1, "Message you want to print")
  lcd.print(2, 1, soilsensor);
  }
}
   

void thingspeak()
{
ThingSpeak.setField(1, mq135);
  ThingSpeak.setField(2, lm35);
  ThingSpeak.setField(3, mq2);
  ThingSpeak.setField(5, soilsensor);
  ThingSpeak.setField(6, ldr);
  ThingSpeak.setField(7, h);
  ThingSpeak.setField(8, t);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey); // Write the fields all at once
  // IMPORTANT - ThingSpeak will only accept updates every 15 seconds (FREE LICENCE)
}
void loop()
{
  Blynk.run();
  timer.run();

  Serial.print("Air Quality: ");
  Serial.print(mq135);
  Serial.println("ppm");
  Serial.print("lm35 ");
  Serial.println(lm35);
  Serial.print("mq2: ");
  Serial.println(mq2);
  Serial.print("soilsensor= ");
  Serial.println(soilsensor);
  Serial.print("ldr: ");
  Serial.println(ldr);
  Serial.println("lux");
  Serial.println('\n');
}
