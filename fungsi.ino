//bapak dosen satria dan ari
//membuat fungsi pada arduino
const int trigPin = D4;  //D4
const int echoPin = D3;  //D3


const int trigPin1 = D2;  //D4
const int echoPin1 = D1;  //D3


// defines variables
long duration;
int distance;

long duration1;
int distance1;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT);

Serial.begin(9600); // Starts the serial communication
}

void loop() {
// Clears the trigPin

int j1 = jarak(trigPin,echoPin);
int j2 = jarak(trigPin1,echoPin1);
Serial.print("Distance1: ");
Serial.print(j1);
Serial.print("Distance2: ");
Serial.println(j2);
delay(2000);

}

int jarak(int a, int b){
  int distan;
  digitalWrite(a, LOW);
  delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(a, HIGH);
  delayMicroseconds(10);
  digitalWrite(a, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(b, HIGH);

// Calculating the distance
  distan= duration*0.034/2;
// Prints the distance on the Serial Monitor
  Serial.print(distan);
  return distan;

}
