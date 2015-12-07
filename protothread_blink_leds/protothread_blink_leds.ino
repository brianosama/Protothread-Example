#include <pt.h>

#define LEDGREEN 3
#define LEDRED 10

static struct pt pt1, pt2;

// setup the variables, ports to be used
void setup() {
  pinMode(LEDGREEN, OUTPUT);
  pinMode(LEDRED, OUTPUT);

  PT_INIT(&pt1); // initialize the thread pointer
  PT_INIT(&pt2); // initialize the thread pointer
}

// function that toggles the Red LED
void toggleLEDRed(){
  boolean state = digitalRead(LEDRED);
  state ^= 1;
  digitalWrite(LEDRED, state);  
}

// function that toggles the Green LED
void toggleLEDGreen(){
  boolean state = digitalRead(LEDGREEN);
  state ^= 1;
  digitalWrite(LEDGREEN, state);  
}

// thread function that blinks the Red LED
int thread1_LedRed(int interval){
  static unsigned long timestamp_red = 0;
  PT_BEGIN(&pt1); // this signifies the start of the thread
  while(1){
    PT_WAIT_UNTIL(&pt1, millis() - timestamp_red > interval); // this will check the 2nd argument, if true it will continue, if false it blocks and go to other thread
    timestamp_red = millis();
    toggleLEDRed();
  }
  PT_END(&pt1); // this signifies the end of the thread
}

int thread2_LedGreen(int interval){
  static unsigned long timestamp_green = 0;
  PT_BEGIN(&pt2); // this signifies the start of the thread
  while(1){
    PT_WAIT_UNTIL(&pt2, millis() - timestamp_green > interval);
    timestamp_green = millis();
    toggleLEDGreen();
  }
  PT_END(&pt2); // this signifies the start of the thread
}

// the super loop
void loop() {
  thread1_LedRed(100); // call the thread function, toggle Red Led every 100 ms
  thread2_LedGreen(500); // call the thread function, toggle Green Led every 500 ms
}
