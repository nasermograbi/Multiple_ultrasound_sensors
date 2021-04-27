#include <ros.h>
#include <ros/time.h>
#include <sensor_msgs/Range.h>

ros::NodeHandle nh;

#define echoPin1 2 // Echo Pin
#define trigPin1 10 // Trigger Pin

#define echoPin2 4 // Echo Pin
#define trigPin2 5 // Trigger Pin

#define echoPin3 6 // Echo Pin
#define trigPin3 7 // Trigger Pin

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

sensor_msgs::Range range_msg1;
sensor_msgs::Range range_msg2;
sensor_msgs::Range range_msg3;

ros::Publisher pub_range_1( "/ultrasound_1", &range_msg1);
ros::Publisher pub_range_2( "/ultrasound_2", &range_msg2);
ros::Publisher pub_range_3( "/ultrasound_3", &range_msg3);

char frameid_1[] = "/ultrasound_1";
char frameid_2[] = "/ultrasound_2";
char frameid_3[] = "/ultrasound_3";

void setup() {
  nh.initNode();
  nh.advertise(pub_range_1);
  nh.advertise(pub_range_2);
  nh.advertise(pub_range_3);
  
  range_msg1.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg1.header.frame_id = frameid_1;
  range_msg1.field_of_view = 0.1; //fake
  range_msg1.min_range = 0.0;
  range_msg1.max_range = 60;

  range_msg2.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg2.header.frame_id = frameid_2;
  range_msg2.field_of_view = 0.1; //fake
  range_msg2.min_range = 0.0;
  range_msg2.max_range = 60;

  range_msg3.radiation_type = sensor_msgs::Range::ULTRASOUND;
  range_msg3.header.frame_id = frameid_3;
  range_msg3.field_of_view = 0.1; //fake
  range_msg3.min_range = 0.0;
  range_msg3.max_range = 60;
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

float getRange_Ultrasound_1(){
  int val = 0;
  
  for(int i=0; i<4; i++) {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  val += duration;
  }
  return val / 232.8 ;

}


float getRange_Ultrasound_2(){
  int val = 0;
  
  for(int i=0; i<4; i++) {
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  val += duration;
  }
  return val / 232.8 ;

}

float getRange_Ultrasound_3(){
  int val = 0;
  
  for(int i=0; i<4; i++) {
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH);
  //Calculate the distance (in cm) based on the speed of sound.
  val += duration;
  }
  return val / 232.8 ;
  
}

long range_time_1;
long range_time_2;
long range_time_3;

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
distance of the nearest object by bouncing soundwaves off of it. */
if ( millis() >= range_time_1 ){
    int r =0;
    range_msg1.range = getRange_Ultrasound_1();
    range_msg1.header.stamp = nh.now();
    pub_range_1.publish(&range_msg1);
    range_time_1 = millis() + 50;
  }

if ( millis() >= range_time_2 ){
    int r =0;
    range_msg2.range = getRange_Ultrasound_2();
    range_msg2.header.stamp = nh.now();
    pub_range_2.publish(&range_msg2);
    range_time_2 = millis() + 50;
  }
  
if ( millis() >= range_time_3 ){
    int r =0;
    range_msg3.range = getRange_Ultrasound_3();
    range_msg3.header.stamp = nh.now();
    pub_range_3.publish(&range_msg3);
    range_time_3 = millis() + 50;
  }
  
  nh.spinOnce();
  
  delay(250);
  
}
