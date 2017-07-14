int trigpin = 10; // Trigger Pin
int echopin = 9;  // Echo Pin

/** returns distance with obstacle measured by Ultrasonic Sensor
 * @param trig : Trigger Pin
 * @param echo : Echo Pin
 */
void ultrasonic(int trig, int echo) {
  int duration;
  int distance;
  static int lastdistance = 0;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);  // trigger pulse duration = 10 microseconds

  duration = pulseIn(echo, HIGH); // echo received in microseconds
  distance = duration * 0.034 / 2; // Distance returned in cm, velocity of sound  = 340 m/s

  /**Controlling output distance
   * 1. removing negative values of distance are returned by sensor( comes when distance with obstacle is <2cm or >4m)
   * 2. Removing large fluctuations by delaying the measured output
   */
  if(abs(lastdistance-distance)>50 || distance<0){ // Removing large fluctuations by delaying the measured output
    delay(200);
    if(distance>lastdistance){ 
      lastdistance = lastdistance+50;
    }else{
      lastdistance = lastdistance-50;
    }
  }else{
    Serial.println(distance); // printing final output on Serial monitor
    lastdistance = distance;
  }
}

void setup() {
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  Serial.begin(9600);
}

void loop() {
  ultrasonic(trigpin, echopin); // Passing pin numbers
  delay(200);
}


