#define TRIGGER_PIN  D3  //D3
#define ECHO_PIN      D4 //D4


const char* ssid     = "miungg";
const char* password = "149148200";

const char* host = "192.168.43.80";

WiFiClient client;
const int httpPort = 80;
String url;
long duration, distance;
unsigned long timeout;
  
void setup() {
  Serial.begin(9600);
  delay(10);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // mulai terhubung ke wifi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void baca_jarak(){
  digitalWrite(TRIGGER_PIN, LOW);  
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  Serial.println(" cm");
}

void loop() {
  Serial.print("baca jarak ");
  baca_jarak();
  
  Serial.print("connecting to ");
  Serial.println(host);

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    //return;
  }

// membuat url
  url = "/arites/index.php/ujicoba/sensor?data=";
  url += distance;
  
  Serial.print("Requesting URL: ");
  Serial.println(url);

// mengirim permintaan ke server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

// membaca data
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
  Serial.println();
  delay(5000);
}
