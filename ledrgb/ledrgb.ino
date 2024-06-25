//// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
//// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
//
//#include <Adafruit_NeoPixel.h>
//#ifdef __AVR__
//#include <avr/power.h>
//#endif
//
//// Which pin on the Arduino is connected to the NeoPixels?
//// On a Trinket or Gemma we suggest changing this to 1
//#define PIN            2
//
//// How many NeoPixels are attached to the Arduino?
//#define NUMPIXELS      12
//
//// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
//// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
//// example for more information on possible values.
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
//
//int delayval = 40; // delay for half a second
//
//void setup() {
//  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//#if defined (__AVR_ATtiny85__)
//  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//#endif
//  // End of trinket special code
//
//  pixels.begin(); // This initializes the NeoPixel library.
//}
//
//void loop() {
//
//  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
//
//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,100,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(100,0,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//   for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,0,100)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
//
//  }
//}
#include <Adafruit_NeoPixel.h>

#define LED_PIN 2
#define BUTTON_PIN 12
#define NUMPIXELS 6
#define AUDIO_PIN A2
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int currentEffect = 0;
int totalEffects = 6;

int audioThreshold = 190; // Ngưỡng âm thanh để thay đổi màu, có thể điều chỉnh
int currentColor = 0;
int maxAudioLevel = 260; // Giá trị âm thanh tối đa dự kiến, điều chỉnh nếu cần


void setup() {
 pixels.begin();
 pixels.setBrightness(200);//
//  pinMode(BUTTON_PIN, INPUT_PULLUP);
 pinMode(BUTTON_PIN, INPUT);
 Serial.begin(9600);
}

void loop() {
  delay(50);
 if (digitalRead(BUTTON_PIN) == HIGH) {
  Serial.println(digitalRead(BUTTON_PIN));
  Serial.println("v-----");
   currentEffect ++;
   delay(1500); // Debounce
   
   Serial.println(currentEffect);
   
 }
 if (currentEffect>4)
   {
    currentEffect=0;
   }
  switch (currentEffect) {
   case 0:
   pixels.setBrightness(200);//
     cauVong(10);
     break;
   case 1:
   pixels.setBrightness(200);//
     nuocChay(pixels.Color(255, 0, 0), 50);
     break;
   case 2:
   pixels.setBrightness(200);//
     muaRoi(100, 1);
     break;
   case 3:
     nhipDap(1);
     break;
   case 4:
   pixels.setBrightness(200);//
     nhayTheoNhipNhac();
     break;
 }
 }

 


// Hiệu ứng cầu vồng
void cauVong(uint8_t wait) {
 uint16_t i, j;
 for(j=256; j>=0; j--) {
   for(i=0; i< pixels.numPixels(); i++) {
     pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
   }
   pixels.show();
   delay(wait);
   if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
   
 }
}

// Hiệu ứng lấp đầy màu
void nuocChay(uint32_t color, int wait) {
 for(int i=pixels.numPixels(); i>=0; i--) {
   pixels.setPixelColor(i, color);
   pixels.show();
   delay(wait);
   if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
 }
 for(int i=pixels.numPixels(); i>=0; i--) {
   pixels.setPixelColor(i, 0);
   pixels.show();
   delay(wait);
   if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
 }
}



// Hiệu ứng lấp lánh
void muaRoi(int wait, int iterations) {
 for (int i = NUMPIXELS-1; i >=0; i--) {
  //  int pixel = random(pixels.numPixels());
    int pixel=i;
    int rgb1 = random(255);
    int rgb2 = random(255);
    int rgb3 = random(255);
    //  Serial.println(rgb1);
      // Serial.println(pixel);
   pixels.setPixelColor(pixel, pixels.Color(rgb1, rgb2, rgb3));
   pixels.show();
   delay(wait);
   pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
   if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
 }
 for (int i =0 ; i <NUMPIXELS; i++) {
  //  int pixel = random(pixels.numPixels());
    int pixel=i;
    int rgb1 = random(255);
    int rgb2 = random(255);
    int rgb3 = random(255);
    //  Serial.println(rgb1);
      // Serial.println(pixel);
   pixels.setPixelColor(pixel, pixels.Color(rgb1, rgb2, rgb3));
   pixels.show();
   delay(wait);
   pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
   if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
 }
}

// Hiệu ứng nhịp đập
void nhipDap( int iterations) {
 for (int i = 0; i < iterations; i++) {
     int rgb1 = random(255);
    int rgb2 = random(255);
    int rgb3 = random(255);
   for (int j = 0; j < 255; j++) {
     pixels.fill(pixels.Color(rgb1, rgb2, rgb3), 0, NUMPIXELS);
     pixels.setBrightness(j);
     pixels.show();
     delay(10);
   }
   for (int j = 255; j >= 0; j--) {
     pixels.fill(pixels.Color(rgb1, rgb2, rgb3), 0, NUMPIXELS);
     pixels.setBrightness(j);
     pixels.show();
     delay(10);
   }
   if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
 }
}

// Hàm hỗ trợ cho hiệu ứng cầu vồng
uint32_t Wheel(byte WheelPos) {
 WheelPos = 255 - WheelPos;
 if(WheelPos < 85) {
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
 }
 if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
 }
 WheelPos -= 170;
 return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



void nhayTheoNhipNhac(){
  int audioLevel = analogRead(AUDIO_PIN);
  // Serial.println(audioLevel); // In ra giá trị âm thanh để debug

  showAudioLevel(audioLevel);

  if (audioLevel > audioThreshold) {
    changeColor();
  }
  if (digitalRead(BUTTON_PIN)==HIGH)
   {
    return;
   }
}

void showAudioLevel(int audioLevel) {
  int ledsToLight = map(audioLevel, 0, maxAudioLevel, 0, NUMPIXELS);
  ledsToLight = constrain(ledsToLight, 0, NUMPIXELS);

  for (int i = 0; i < NUMPIXELS; i++) {
    if (i < ledsToLight) {
      pixels.setPixelColor(i, getCurrentColor());
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Tắt LED
    }
  }
  pixels.show();
}

void changeColor() {
  currentColor = (currentColor + 1) % 7; // 7 màu khác nhau
}

uint32_t getCurrentColor() {
  switch (currentColor) {
    case 0:
      return pixels.Color(255, 0, 0); // Đỏ
    case 1:
      return pixels.Color(0, 255, 0); // Xanh lá
    case 2:
      return pixels.Color(0, 0, 255); // Xanh dương
    case 3:
      return pixels.Color(255, 255, 0); // Vàng
    case 4:
      return pixels.Color(255, 0, 255); // Hồng
    case 5:
      return pixels.Color(0, 255, 255); // Cyan
    case 6:
      return pixels.Color(255, 255, 255); // Trắng
    default:
      return pixels.Color(0, 0, 0); // Đen (không nên xảy ra)
  }
}
