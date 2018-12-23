//Servo
#include <Servo.h>
int chrismasTreeServo = 8;
Servo chrismastree;

//PIR
int bewegung = 11;
int bewegungsstatus = 0;

//Buzzer
int speakerPin = 10;
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int beats[] = { 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

// LED
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 12, NEO_GRB + NEO_KHZ800);
uint32_t red = strip.Color(255, 0, 0); 
uint32_t orange = strip.Color(255, 128, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t lilac = strip.Color(255, 0, 255);
uint32_t pink = strip.Color(255, 0, 128);
uint32_t white = strip.Color(255, 255, 255);
uint32_t off = strip.Color(0, 0, 0);
uint32_t rainbow[] = {
  red, orange, yellow, green, blue, lilac, pink, white};
/*rainbowColor*/
void rainbowColor() {
  int l = 0;
  for (int k = 0; k <= 60; k++) {
    strip.setPixelColor(k, rainbow[l]);
    strip.show(); 
    l++; 
    if (l == 8){
      l = 0;
    }
  }
}

int tempo = 300;
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}
void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  Serial.begin(9600);

  //Servo
  chrismastree.attach(chrismasTreeServo);

  //PIR
  pinMode(bewegung, INPUT);

  //Buzzer
  pinMode(speakerPin, OUTPUT);

  //LED
    strip.begin();
  strip.setBrightness(50);
strip.show();
}

void loop() {

  bewegungsstatus = digitalRead(bewegung);
  if (bewegungsstatus == HIGH)
  {
    Serial.print("jow");
     

  //delay 1 
  strip.setBrightness(70);
   strip.show();
      chrismastree.write(90);
  rainbowColor(); 
  for (int i = 0; i < length; i++) {
    if (notes[i] == ' ') {
      delay(beats[i] * tempo); // rest
    } else {
      playNote(notes[i], beats[i] * tempo);
    }

    // pause between notes
    delay(tempo / 2);
  }

   //delay 2
   delay(10000);
   chrismastree.write(0);
   strip.setBrightness(0);
   strip.show();

    
  }
  else
  {
    Serial.print("nop");
  }  
}
