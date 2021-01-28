#include <WiFiNINA.h>
#include <SPI.h>
 #include <Ethernet.h>
#define SECRET_SSID "dlink"
#define SECRET_PASS ""
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int status = WL_IDLE_STATUS;     // the Wifi radio's status
IPAddress gateway(192,168,0,1); 
WiFiServer server(80);            
WiFiClient client;
WiFiClient client1;
int led =  LED_BUILTIN;
//EthernetClient client1;
IPAddress ipserver(192,168,0,100);
int pingResult;
void setup() {

  pinMode(led, OUTPUT);  
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
 // while (!Serial);

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to network: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(5000);
  }

  // you're connected now, so print out the data:
  Serial.println("You're connected to the network");
  
  Serial.println("----------------------------------------");
  printData();
 
  Serial.println("----------------------------------------");
     server.begin();
   Serial.print("Connected to wifi. My address:");
   IPAddress ip103 = WiFi.localIP();
    Serial.println("I am ");
   Serial.println(ip103);
   pingall();
  
   
}

void loop() {

//pingall();
 IPAddress ip103 = WiFi.localIP();
    Serial.println("I am ");
   Serial.println(ip103);
  //delay(1000);
client = server.available();
 Serial.println(client);
 if (client) {  
digitalWrite(LED_BUILTIN, LOW);
     // listen for incoming clients
     
String request = client.readStringUntil('\r');    
Serial.print("From client: "); Serial.println(request);
   
      
      client.println("Hi client! yes I am here.\r"); // sends the answer to the client

   client.flush();
  }
  digitalWrite(LED_BUILTIN, HIGH);
delay(1000);
//connectpc();


 //printData();
 Serial.println("----------------------------------------");
// delay(5000);


}
void printData() {
  Serial.println("Board Information:");
  // print your board's IP address:
 IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
 Serial.println(ip);

  Serial.println();
  Serial.println("Network Information:");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.println(rssi);

  byte encryption = WiFi.encryptionType();
  Serial.print("Encryption Type:");
  Serial.println(encryption, HEX);
  Serial.println();
}
void pingall()
{
  Serial.print("Pinging ");

  Serial.print(gateway);

  Serial.print(": ");

  pingResult = WiFi.ping(gateway);

  if (pingResult >= 0) {

    Serial.print("SUCCESS! RTT = ");

    Serial.print(pingResult);

    Serial.println(" ms");

  } else {

    Serial.print("FAILED! Error code: ");

    Serial.println(pingResult);

  }


  
Serial.print("Pinging ");
IPAddress ip1(192,168,0,100);  

  Serial.print(ip1);

  Serial.print(": ");

  pingResult = WiFi.ping(ip1);

  if (pingResult >= 0) {

    Serial.print("SUCCESS! RTT = ");

    Serial.print(pingResult);

    Serial.println(" ms");

  } else {

    Serial.print("FAILED! Error code: ");

    Serial.println(pingResult);

  }
  Serial.print("Pinging ");

  Serial.print(ipserver);

  Serial.print(": ");

  pingResult = WiFi.ping(ipserver);

  if (pingResult >= 0) {

    Serial.print("SUCCESS! RTT = ");

    Serial.print(pingResult);

    Serial.println(" ms");

  } else {

    Serial.print("FAILED! Error code: ");

    Serial.println(pingResult);

  }

  }
  void connectpc()
  {
    if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            IPAddress ip103 = WiFi.localIP();
            int n=50;
            while(n)
            {
            client.println("data from ");
            client.println(ip103);
            client.println("... ");
             digitalWrite(led, HIGH); 
            delay(200);
             digitalWrite(led, LOW);   
            n--;
            }
            client.stop();
    Serial.println("client disconnected");
    client.flush();
            client.println();
            // break out of the while loop:
            break;
          }
       client.stop();
    Serial.println("client disconnected");
    client.flush();
      }
      }
  }
    }
  }
  
