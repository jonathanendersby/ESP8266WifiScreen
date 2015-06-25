#include <ESP8266WiFi.h>
#include <stdio.h>

const char* ssid     = "your_wifi_ssid";
const char* password = "your_password";
const char* host = "yourserver.co.za";
String lines;

void setup() {
  Serial.begin(115200);
  delay(10);

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(4000);
  Serial1.begin(9600);
  delay(1000);
  clearScreen();
  LCDLine(1, "arbitraryuser.com");
  delay(4000);
  
  clearScreen();
}

void loop() {
  delay(1000);

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  
  // We now create a URI for the request
  String url = "/somefile.txt";
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  
  while(client.available()){
    lines = client.readStringUntil('\r');
  }
  
  char buff[250];
  lines.toCharArray(buff, lines.length());
  
  char* string0 = buff;
  char* line1 = split(string0, '\n');
  char* line2 = split(line1, '\n');
  char* line3 = split(line2, '\n');
  char* line4 = split(line3, '\n');
  
  Serial.println(line1);
  Serial.println("-------------");
  Serial.println(line2);
  Serial.println("-------------");
  Serial.println(line3);
  Serial.println("-------------");
  Serial.println(line4);
  Serial.println("-------------");
    
  LCDLine(1, line1);
  LCDLine(2, line2);
  LCDLine(3, line3);
  LCDLine(4, line4);  

  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}

char* split(char* data, char delim)
{
	while (*data && *data != delim) data++;
	*data++ = 0;
	return data;
}


void clearScreen(){
  Serial1.write("                                                                                                    ");  
  Serial1.write(254); // cursor to beginning of first line
  Serial1.write(128);
}


void LCDLine(int lineNum, char *theText){
  int delayTime = 50;
  int lcdPosition = 0;  // initialize lcdPosition and use to indicate value values

  // based upon the lineNum, set the position on the LCD
  if (lineNum==1){
    lcdPosition = 128;
  }
  else if (lineNum==2){
    lcdPosition = 192;
  }
  else if (lineNum==3){
    lcdPosition = 148;
  }
  else if (lineNum==4){
    lcdPosition = 212;
  }

  // don't write to the LCD if the lineNum value didn't generate a valid position
  if (lcdPosition > 0){
    Serial1.write(0xFE);   //command flag
    delay(delayTime);
    Serial1.write(lcdPosition);    //position

    if (strlen(theText) < 20) {
      // less than 20 characters, print then and then 
      Serial1.print(theText);
      // pad the rest of the line with spaces
      for (int i = strlen(theText); i < 20; i++) {
        Serial1.print(" ");
      } 
    } 
    else {  
      // 20 or more characters, just print the first 20
      for (int i = 0; i < 20; i++) {
        Serial1.print(theText[i]);
      }
    }
    delay(delayTime);
  }
}
