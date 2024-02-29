#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

int lista[100000000];

int gpio = 32;
int _freq = 250;
int _channel = 0;
int _resolution = 8;
int brojac=0;
int pritisnut;
int i=0;
int pamti=0;

int PinTipkalo_A = 32; 
int PinTipkalo_B = 33;
int PinTipkalo_start=39;
int PinTipkalo_up=35;
int PinTipkalo_menu=13;

int min_x = 370; // minimalne i maksimalne vrijednosti koordinata dodira
int min_y = 210;
int max_x = 3900;
int max_y = 3800;

int x_piksel, y_piksel;
uint16_t boja;
// ILI9341 TFT LCD deklaracija spajanja zaslona
#define TFT_CS   5
#define TFT_DC  21
#define TS_CS   4

// Stvori objekt zaslona koji zovemo TFT
Adafruit_ILI9341 TFT = Adafruit_ILI9341(TFT_CS, TFT_DC);

XPT2046_Touchscreen ts(TS_CS);
// varijable za dimenzije zaslona
int myWidth;
int myHeight;
void prazni(){
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(3);
  
  TFT.drawFastVLine(210, 10, 220, ILI9341_WHITE);
  TFT.drawFastVLine(110, 10, 220, ILI9341_WHITE);
  TFT.drawFastHLine(10, 160, 300, ILI9341_WHITE);
  TFT.drawFastHLine(10, 80, 300, ILI9341_WHITE);
  
  TFT.drawFastHLine(10, 30, 90, ILI9341_WHITE);
  TFT.drawFastHLine(10, 55, 90, ILI9341_WHITE);    //skroz gore lijevo
  TFT.drawFastVLine(35, 10, 65, ILI9341_WHITE);
  TFT.drawFastVLine(70, 10, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(10, 110, 90, ILI9341_WHITE);
  TFT.drawFastHLine(10, 135, 90, ILI9341_WHITE); //skroz lijevo sredina
  TFT.drawFastVLine(35, 90, 65, ILI9341_WHITE);
  TFT.drawFastVLine(70, 90, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(10, 190, 90, ILI9341_WHITE);
  TFT.drawFastHLine(10, 215, 90, ILI9341_WHITE); //skroz dole lijevo
  TFT.drawFastVLine(35, 170, 65, ILI9341_WHITE);
  TFT.drawFastVLine(70, 170, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(115, 30, 90, ILI9341_WHITE); //skroz gore sredina
  TFT.drawFastHLine(115, 55, 90, ILI9341_WHITE);
  TFT.drawFastVLine(140, 10, 65, ILI9341_WHITE);
  TFT.drawFastVLine(175, 10, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(115, 110, 90, ILI9341_WHITE); //sredina
  TFT.drawFastHLine(115, 135, 90, ILI9341_WHITE);
  TFT.drawFastVLine(140, 90, 65, ILI9341_WHITE);
  TFT.drawFastVLine(175, 90, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(115, 190, 90, ILI9341_WHITE); //skroz dole sredina
  TFT.drawFastHLine(115, 215, 90, ILI9341_WHITE);
  TFT.drawFastVLine(140, 170, 65, ILI9341_WHITE);
  TFT.drawFastVLine(175, 170, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(220, 30, 90, ILI9341_WHITE);
  TFT.drawFastHLine(220, 55, 90, ILI9341_WHITE); //skroz gore desno
  TFT.drawFastVLine(245, 10, 65, ILI9341_WHITE);
  TFT.drawFastVLine(280, 10, 65, ILI9341_WHITE);
  
  
  TFT.drawFastHLine(220, 110, 90, ILI9341_WHITE); //skroz desno sredina
  TFT.drawFastHLine(220, 135, 90, ILI9341_WHITE);
  TFT.drawFastVLine(245, 90, 65, ILI9341_WHITE);
  TFT.drawFastVLine(280, 90, 65, ILI9341_WHITE);
  
  TFT.drawFastHLine(220, 190, 90, ILI9341_WHITE); // skroz dole desno
  TFT.drawFastHLine(220, 215, 90, ILI9341_WHITE);
  TFT.drawFastVLine(245, 170, 65, ILI9341_WHITE);
  TFT.drawFastVLine(280, 170, 65, ILI9341_WHITE);
  delay(1000);
}

void obican(){
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(3);
  
  TFT.drawFastVLine(210, 10, 220, ILI9341_WHITE);
  TFT.drawFastVLine(110, 10, 220, ILI9341_WHITE);
  TFT.drawFastHLine(10, 160, 300, ILI9341_WHITE);
  TFT.drawFastHLine(10, 80, 300, ILI9341_WHITE);
  
  while (digitalRead(PinTipkalo_up) == LOW) {
      pritisnut = ts.touched();
      if (digitalRead(PinTipkalo_A) == LOW) {
          boja = ILI9341_BLUE;
      }
      if (digitalRead(PinTipkalo_B) == LOW) {
          boja = ILI9341_RED;
          
      }
      //pritisnut = ts.touched();
      
      if (pritisnut) {
          TS_Point p = ts.getPoint(); // ocitavanje gdje je ekran pritisnut
          x_piksel = map(p.x, min_x, max_x, 0, 319); // pretvaranje ocitanja u piksele
          y_piksel = map(p.y, min_y, max_y, 0, 239);
          TFT.fillCircle(x_piksel, y_piksel, 1, boja);
      }
      if (digitalRead(PinTipkalo_menu) == LOW){
        exit(0);
    }
  }
  prazni();
}

void ekran() {
  //Serial.println(_freq);
  TFT.fillScreen(ILI9341_BLACK); // obojaj zaslon u crno
  TFT.setTextColor(ILI9341_RED);
  TFT.setTextSize(3);
  TFT.setCursor(50, 60);
  TFT.print("DOBRODOSLI U");
  TFT.setCursor(120, 90);
  TFT.setTextColor(ILI9341_GREEN);
  TFT.println("IGRU");
  TFT.setCursor(45, 120);
  TFT.println("KRIZIC-KRUZIC");
  TFT.setTextColor(ILI9341_YELLOW);
  TFT.setCursor(40, 170);
  TFT.print("Loading:   %");
  TFT.setTextSize(4);
  TFT.setCursor(180, 170);
  TFT.print(_freq);
}
 // if (brojac!=95){
  //TFT.print(_freq);
 // }
 // else {
 //     exit(0);
      
 // }
//}

void setup() {
  Serial.begin(115200);
  pinMode(PinTipkalo_A, INPUT_PULLUP);
  pinMode(PinTipkalo_B, INPUT_PULLUP);
  pinMode(PinTipkalo_start, INPUT_PULLUP);
  pinMode(PinTipkalo_up, INPUT_PULLUP);
  pinMode(PinTipkalo_menu, INPUT_PULLUP);
  ledcSetup(_channel, _freq, _resolution);
  ledcAttachPin(gpio, _channel);
  TFT.begin();  // inicijalizacuija zaslona
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setRotation(3);            // postavi orijentaciju
  TFT.setTextSize(3);
  myWidth  = TFT.width() ;       // ekran je širok
  myHeight = TFT.height();
  ts.begin(); 
  ts.setRotation(1);
}

void loop(){

    if (brojac==95){
        exit(0);
    }
    else{
        for (_freq = 0; _freq < 100; _freq = _freq + 5) {
            ekran();
            //TFT.setTextSize(4);
            //TFT.setCursor(180, 170);
            //TFT.print(_freq);
            ledcWriteTone(_channel, _freq);
            delay(200);
            brojac=brojac+5;

    }
  }
  prazni();
  //TFT.fillScreen(ILI9341_ORANGE);
  //delay(2000);
  
  while (i < 1) {
      pritisnut = ts.touched();
      if (digitalRead(PinTipkalo_A) == LOW) {
          boja = ILI9341_BLUE;
      }
      if (digitalRead(PinTipkalo_B) == LOW) {
          boja = ILI9341_RED;
          
      }
      //pritisnut = ts.touched();
      
      if (pritisnut) {
          TS_Point p = ts.getPoint(); // ocitavanje gdje je ekran pritisnut
          x_piksel = map(p.x, min_x, max_x, 0, 319); // pretvaranje ocitanja u piksele
          y_piksel = map(p.y, min_y, max_y, 0, 239);
          TFT.fillCircle(x_piksel, y_piksel, 1, boja);
      }
     // delay(100000);
    if (digitalRead(PinTipkalo_start) == LOW){
        obican();
    }
    if (digitalRead(PinTipkalo_menu) == LOW){
        exit(0);
    }
  }
}
  
  
  
  
  
  
 // TFT.drawFastHLine(10, 155, 90, ILI9341_WHITE);

 
  //delay(100000);

//void next(){
//    TFT.fillScreen(ILI9341_BLACK);
//    tft.drawFastVLine(190, 10, 80, ILI9341_YELLOW);
//    tft.drawFastVLine(100, 10, 80, ILI9341_YELLOW);
//    delay(100000);
    
//}
  

