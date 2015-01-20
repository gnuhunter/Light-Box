// ------- LCD opsætning start --------
#include <MenuBackend.h>    //MenuBackend library - copyright by Alexander Brevig

#include <LiquidCrystal.h>  //this library is included in the Arduino IDE

const int LCD_LED_PIN = 10;   // select the pin for the LED
int LCD_LED = 1;

// LiquidCrystal display with:
// rs on pin 12
// rw on ground
// enable on pin 11
// d4, d5, d6, d7 on pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// 
unsigned long LastActivityTime;  
int LCDPowerOffDelay = 15;  // Antallet af sek. uden aktivitet før LCD slukker.

// ------- LCD opsætning slut --------

// ------- Bottens opsætning start -------
const int buttonPinLeft = 28;      // pin for the Up button
const int buttonPinRight = 26;    // pin for the Down button
const int buttonPinEsc = 24;     // pin for the Esc button
const int buttonPinEnter = 22;   // pin for the Enter button

int lastButtonPushed = 0;

int lastButtonEnterState = LOW;   // the previous reading from the Enter input pin
int lastButtonEscState = LOW;   // the previous reading from the Esc input pin
int lastButtonLeftState = LOW;   // the previous reading from the Left input pin
int lastButtonRightState = LOW;   // the previous reading from the Right input pin


long lastEnterDebounceTime = 0;  // the last time the output pin was toggled
long lastEscDebounceTime = 0;  // the last time the output pin was toggled
long lastLeftDebounceTime = 0;  // the last time the output pin was toggled
long lastRightDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 150;    // the debounce time (500 var default)

// ------- Bottens opsætning slut -------

// -------- Onbord Led start -----------
const int ONBORD_LED_PIN = 13;   // select the pin for the LED
// -------- Onbord Led stop -----------

// -------- LED opsætning start ----------
#include <FastLED.h>

// Måske vi skal gå væk fra define? Så kan jeg nemlig lave om på det i menuen.
#define NUM_LEDS 100
#define DATA_PIN 6
#define CLOCK_PIN 7
#define LED_TYPE    WS2801
#define COLOR_ORDER RGB
CRGB leds[NUM_LEDS];
int Updates_per_Second = 50;

// Default LED setings.
int brightness = 200; // 0-255
CRGBPalette16 currentPalette;
TBlendType    currentBlending = BLEND;
int PatternNumber = 2;
int ColorPaletteNumber = 1;

// -------- LED opsætning slut ----------


// -------- LED Palettes start ------------
// Høre hvis til hver af de palettes der bliver lavet i progmem.
// 
//extern CRGBPalette16 myRedWhiteBluePalette;
//extern CRGBPalette16 Fire2012FirePalette_p PROGMEM;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;
extern const TProgmemPalette16 myRedPalette_p PROGMEM;
extern const TProgmemPalette16 myBluePalette_p PROGMEM;
extern const TProgmemPalette16 myGreenPalette_p PROGMEM;
extern const TProgmemPalette16 Fire2012FirePalette_p PROGMEM;
extern const TProgmemPalette16 Fire2012AquaPalette_p PROGMEM;
extern const TProgmemPalette16 Fire2012SimpleRedPalette_p PROGMEM;
extern const TProgmemPalette16 OrangePalette_p PROGMEM;

// -------- LED Palettes slut ------------


// -------- Menu opsætning start --------

//Menu variables
MenuBackend menu = MenuBackend(menuUsed,menuChanged);
//initialize menuitems
  // Change Scene menu:
  MenuItem menuItemChangeScene = MenuItem("ItemChangeScene");
    MenuItem menuItemScene1 = MenuItem("ItemScene01");
    MenuItem menuItemScene2 = MenuItem("ItemScene02");
  // Change Pattern menu:
  MenuItem menuItemChangePattern = MenuItem("ItemChangePattern");
    MenuItem menuItemChangePattern1 = MenuItem("ItemPattern01");
    MenuItem menuItemChangePattern2 = MenuItem("ItemPattern02");      
    MenuItem menuItemChangePattern3 = MenuItem("ItemPattern03");
    MenuItem menuItemChangePattern4 = MenuItem("ItemPattern04");
//    MenuItem menuItemChangePattern5 = MenuItem("ItemChangePattern5");
  // Change Color Palette menu:
  MenuItem menuItemChangeColorPalette = MenuItem("ItemChangeColorPalette");
    MenuItem menuItemPalette1 = MenuItem("ItemPalette01");
    MenuItem menuItemPalette2 = MenuItem("ItemPalette02");
    MenuItem menuItemPalette3 = MenuItem("ItemPalette03");
    MenuItem menuItemPalette4 = MenuItem("ItemPalette04");
    MenuItem menuItemPalette5 = MenuItem("ItemPalette05");
    MenuItem menuItemPalette6 = MenuItem("ItemPalette06");
    MenuItem menuItemPalette7 = MenuItem("ItemPalette07");
    MenuItem menuItemPalette8 = MenuItem("ItemPalette08");
    MenuItem menuItemPalette9 = MenuItem("ItemPalette09");
    MenuItem menuItemPalette10 = MenuItem("ItemPalette10");
    MenuItem menuItemPalette11 = MenuItem("ItemPalette11");
    MenuItem menuItemPalette12 = MenuItem("ItemPalette12");
    MenuItem menuItemPalette13 = MenuItem("ItemPalette13");
    MenuItem menuItemPalette14 = MenuItem("ItemPalette14");
    MenuItem menuItemPalette15 = MenuItem("ItemPalette15");
    MenuItem menuItemPalette16 = MenuItem("ItemPalette16");
    MenuItem menuItemPalette17 = MenuItem("ItemPalette17");
    MenuItem menuItemPalette18 = MenuItem("ItemPalette18");
    MenuItem menuItemPalette19 = MenuItem("ItemPalette19");
  // Setup menu:
  MenuItem menuItemSetup = MenuItem("ItemSetup");
    MenuItem menuItemSetupUpdatePerSec = MenuItem("ItemSetupUpdatePerSec");
    MenuItem menuItemSetupBrightness = MenuItem("ItemSetupBrightness");      
    MenuItem menuItemSetupColorTemperature = MenuItem("menuItemSetupColorTemperature");      
    MenuItem menuItemSetupUp = MenuItem("ItemSetupUp");      
    MenuItem menuItemSetupDown = MenuItem("ItemSetupDown");      

// -------- Menu opsætning slut --------

void setup()
{
  
  // ----- LCD Setup ----
  pinMode(LCD_LED_PIN, OUTPUT);  // declare the LCD LED Pin as an OUTPUT
  digitalWrite(LCD_LED_PIN, HIGH);   // turn the LCD LED on
  lcd.begin(16, 2);
  lcd.setCursor(0,0);  
  lcd.print("Light Box       ");
  lcd.setCursor(0,1);
  lcd.print("Loading.");

  for (int i = 0; i <= 3; i++){
  delay( 1000 ); 
  lcd.print(".");
  }

  LastActivityTime = millis();  // LCD poweroff time
    
  // Onbord Led
  pinMode(ONBORD_LED_PIN, OUTPUT);  // declare the ledPin as an OUTPUT
  digitalWrite(ONBORD_LED_PIN, LOW);   // turn the ledPin off
  
  // ------ Bottons -----
  pinMode(buttonPinLeft, INPUT);
  pinMode(buttonPinRight, INPUT);
  pinMode(buttonPinEnter, INPUT);
  pinMode(buttonPinEsc, INPUT);

  // LED
  FastLED.addLeds<LED_TYPE, DATA_PIN, CLOCK_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( Typical8mmPixel );
  FastLED.setBrightness( brightness );
  FastLED.setTemperature( DirectSunlight );
  // Black-body radiation light sources emit a (relatively) continuous
  // spectrum, and can be described as having a Kelvin 'temperature'
  // Candle 1900 K           Tungsten40W 2600 K   Tungsten100W 2850 K
  // Halogen 3200 K          CarbonArc 5200 K     HighNoonSun 5400 K
  // DirectSunlight 6000 K   OvercastSky 7000 K   ClearBlueSky 20000 K
  UpdateLEDColorPalette(); // Aktivate the default Color Palette

  //configure menu
  // Her styres hvilke menu items der kommer efter hinanden. Et menu item kan godt være i flere menuer.
  // first menu item
  menu.getRoot().add(menuItemChangeScene);
  // Main menu order
  menuItemChangeScene.addRight(menuItemChangePattern).addRight(menuItemChangeColorPalette).addRight(menuItemSetup);
  // Menu items
  menuItemChangeScene.add(menuItemScene1).addRight(menuItemScene2);
  menuItemChangePattern.add(menuItemChangePattern1).addRight(menuItemChangePattern2).addRight(menuItemChangePattern3).addRight(menuItemChangePattern4);
  
  menuItemChangeColorPalette.add(menuItemPalette1).addRight(menuItemPalette2).addRight(menuItemPalette3).addRight(menuItemPalette4).addRight(menuItemPalette5).addRight(menuItemPalette6).addRight(menuItemPalette7).addRight(menuItemPalette8).addRight(menuItemPalette9).addRight(menuItemPalette10).addRight(menuItemPalette11).addRight(menuItemPalette12).addRight(menuItemPalette13).addRight(menuItemPalette14).addRight(menuItemPalette15).addRight(menuItemPalette16).addRight(menuItemPalette17).addRight(menuItemPalette18).addRight(menuItemPalette19);
  
  menuItemSetup.add(menuItemSetupUpdatePerSec).addRight(menuItemSetupBrightness).addRight(menuItemSetupColorTemperature);

  menuItemSetupBrightness.add(menuItemSetupUp).addRight(menuItemSetupDown);

  menu.toRoot();
}  // setup()...

// -------- menuChanged ------
// Alle menu punkter skal skrives ind her.

void menuChanged(MenuChangeEvent changed){
  
  MenuItem newMenuItem=changed.to; //get the destination menu
  
  lcd.setCursor(0,1); //set the start position for lcd printing to the second row
  
    if(newMenuItem.getName()==menu.getRoot()){
      lcd.print("Main Menu       ");
      lcd.setCursor(0,0);
      lcd.print("Light Box       ");      
  }else if(newMenuItem.getName()=="ItemChangeScene"){
      // Scenes:
      lcd.print("Change Scene    ");
  }else if(newMenuItem.getName()=="ItemScene01"){
      lcd.print("Scene 1         ");
  }else if(newMenuItem.getName()=="ItemScene02"){
      lcd.print("Scene 2         ");
  }else if(newMenuItem.getName()=="ItemChangePattern"){
    
      // Patterns:
      lcd.print("Change Pattern  ");
  }else if(newMenuItem.getName()=="ItemPattern01"){
      lcd.print("Turn Lights Off ");
  }else if(newMenuItem.getName()=="ItemPattern02"){
      lcd.print("Chasing Lights  ");
  }else if(newMenuItem.getName()=="ItemPattern03"){
      lcd.print("Fire2012        ");
  }else if(newMenuItem.getName()=="ItemPattern04"){
      lcd.print("Softtwinkles    ");
//  }else if(newMenuItem.getName()=="ItemChangePattern5"){
//      lcd.print("Confetti        ");
  }else if(newMenuItem.getName()=="ItemChangeColorPalette"){
    
      // Color Palettes:
      lcd.print("Change Palette  ");
  }else if(newMenuItem.getName()=="ItemPalette01"){
      lcd.print("Rainbow Colors  ");
  }else if(newMenuItem.getName()=="ItemPalette02"){
      lcd.print("RainbowStripeCol");
  }else if(newMenuItem.getName()=="ItemPalette03"){
      lcd.print("Ocean Colors    ");
  }else if(newMenuItem.getName()=="ItemPalette04"){
      lcd.print("Cloud Colors    ");
  }else if(newMenuItem.getName()=="ItemPalette05"){
      lcd.print("Lava Colors     ");
  }else if(newMenuItem.getName()=="ItemPalette06"){
      lcd.print("Forest Colors   ");
  }else if(newMenuItem.getName()=="ItemPalette07"){
      lcd.print("Party Colors    ");
  }else if(newMenuItem.getName()=="ItemPalette08"){
      lcd.print("Heat Colors     ");
  }else if(newMenuItem.getName()=="ItemPalette09"){
      lcd.print("RandomPalette   ");
  }else if(newMenuItem.getName()=="ItemPalette10"){
      lcd.print("White Striped   ");
  }else if(newMenuItem.getName()=="ItemPalette11"){
      lcd.print("Purple And Green");
  }else if(newMenuItem.getName()=="ItemPalette12"){
      lcd.print("Red White Blue  ");
  }else if(newMenuItem.getName()=="ItemPalette13"){
      lcd.print("Red Striped     ");
  }else if(newMenuItem.getName()=="ItemPalette14"){
      lcd.print("Blue Striped    ");
  }else if(newMenuItem.getName()=="ItemPalette15"){
      lcd.print("Green Striped   ");
  }else if(newMenuItem.getName()=="ItemPalette16"){
      lcd.print("Fire2012 Fire   ");
  }else if(newMenuItem.getName()=="ItemPalette17"){
      lcd.print("Fire2012 Aqua   ");
  }else if(newMenuItem.getName()=="ItemPalette18"){
      lcd.print("Fire2012 Red    ");
  }else if(newMenuItem.getName()=="ItemPalette19"){
      lcd.print("Orange Colors  ");
  }else if(newMenuItem.getName()=="ItemSetup"){
    
      // Setup:
      lcd.print("Setup Menu      ");
  }else if(newMenuItem.getName()=="ItemSetupUpdatePerSec"){
      lcd.print("Updates Per Sec ");
  }else if(newMenuItem.getName()=="ItemSetupBrightness"){
      lcd.print("Brightness      ");
    }else if(newMenuItem.getName()=="ItemSetupUp"){
        lcd.print("Up              ");
        if(menu.getCurrent()==menuItemSetupBrightness){
          lcd.setCursor(0,0);
          lcd.print("Brightness   ");
          if (brightness <= 99) {lcd.print(" ");}
          if (brightness <= 9) {lcd.print(" ");} 
          lcd.print(brightness);
        }
    }else if(newMenuItem.getName()=="ItemSetupDown"){
        lcd.print("Down            ");
  }else if(newMenuItem.getName()=="menuItemSetupColorTemperature"){
      lcd.print("Color Temperatur");
  }
}


// --------- menuUsed -------
// Her skal skrives hvad der skal ske når et menu punkt bliver brugt. 
// De menu punkter som fungere som en mappe skal ikke skrives ind her.

void menuUsed(MenuUseEvent used){

  // Scene menu
  if (used.item == "ItemScene01") {ColorPaletteNumber = 1; PatternNumber = 2;}
  if (used.item == "ItemScene02") {ColorPaletteNumber = 16; PatternNumber = 3;}
  
  // Palettes menu
  if (used.item == "ItemPattern01") {PatternNumber = 1;}
  if (used.item == "ItemPattern02") {PatternNumber = 2;}
  if (used.item == "ItemPattern03") {PatternNumber = 3;}
  if (used.item == "ItemPattern04") {PatternNumber = 4;}
//  if (used.item == "ItemChangePattern5") {PatternNumber = 5;}

  // Color Palette menu
  if (used.item == "ItemPalette01") {ColorPaletteNumber = 1; }
  if (used.item == "ItemPalette02") {ColorPaletteNumber = 2; }
  if (used.item == "ItemPalette03") {ColorPaletteNumber = 3; }
  if (used.item == "ItemPalette04") {ColorPaletteNumber = 4; }
  if (used.item == "ItemPalette05") {ColorPaletteNumber = 5; }
  if (used.item == "ItemPalette06") {ColorPaletteNumber = 6; }
  if (used.item == "ItemPalette07") {ColorPaletteNumber = 7; }
  if (used.item == "ItemPalette08") {ColorPaletteNumber = 8; }
  if (used.item == "ItemPalette09") {ColorPaletteNumber = 9; }
  if (used.item == "ItemPalette10") {ColorPaletteNumber = 10; }
  if (used.item == "ItemPalette11") {ColorPaletteNumber = 11; }
  if (used.item == "ItemPalette12") {ColorPaletteNumber = 12; }
  if (used.item == "ItemPalette13") {ColorPaletteNumber = 13; }
  if (used.item == "ItemPalette14") {ColorPaletteNumber = 14; }
  if (used.item == "ItemPalette15") {ColorPaletteNumber = 15; }
  if (used.item == "ItemPalette16") {ColorPaletteNumber = 16; }
  if (used.item == "ItemPalette17") {ColorPaletteNumber = 17; }
  if (used.item == "ItemPalette18") {ColorPaletteNumber = 18; }
  if (used.item == "ItemPalette19") {ColorPaletteNumber = 19; }

  if(*menu.getCurrent().getBefore()==menuItemSetupBrightness){
      if (used.item == menuItemSetupUp) {brightness = qadd8(brightness, 5);}      
      if (used.item == menuItemSetupDown) {brightness = qsub8(brightness, 5);}
      lcd.setCursor(13,0);
      if (brightness <= 99) {lcd.print(" ");}
      if (brightness <= 9) {lcd.print(" ");} 
      lcd.print(brightness);
  }
  if (used.item == "ItemPalette20") { ColorPaletteNumber = 20; }

//  lcd.setCursor(0,0);  
//  lcd.print("Arduino Lights");
//  menu.toRoot();  //back to Main
//  digitalWrite(ONBORD_LED_PIN, LOW);   // turn the ledPin off
}

// --------- readButtons -------
// Skal ikke ændres med mindre der skal laves flere knapper.
void  readButtons(){  //read buttons status
  int reading;
  int buttonEnterState=LOW;             // the current reading from the Enter input pin
  int buttonEscState=LOW;             // the current reading from the input pin
  int buttonLeftState=LOW;             // the current reading from the input pin
  int buttonRightState=LOW;             // the current reading from the input pin

  //Enter button
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinEnter);

                  // check to see if you just pressed the enter button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonEnterState) {
                    // reset the debouncing timer
                    lastEnterDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastEnterDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonEnterState=reading;
                    lastEnterDebounceTime=millis();
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonEnterState = reading;
                  

    //Esc button               
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinEsc);

                  // check to see if you just pressed the Down button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonEscState) {
                    // reset the debouncing timer
                    lastEscDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastEscDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonEscState = reading;
                    lastEscDebounceTime=millis();
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonEscState = reading; 
                  
                     
   //Down button               
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinRight);

                  // check to see if you just pressed the Down button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonRightState) {
                    // reset the debouncing timer
                    lastRightDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastRightDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonRightState = reading;
                   lastRightDebounceTime =millis();
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonRightState = reading;                  
                  
                  
    //Up button               
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinLeft);

                  // check to see if you just pressed the Down button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonLeftState) {
                    // reset the debouncing timer
                    lastLeftDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastLeftDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonLeftState = reading;
                    lastLeftDebounceTime=millis();;
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonLeftState = reading;  

                  //records which button has been pressed
                  if (buttonEnterState==HIGH){
                    lastButtonPushed=buttonPinEnter;

                  }else if(buttonEscState==HIGH){
                    lastButtonPushed=buttonPinEsc;

                  }else if(buttonRightState==HIGH){
                    lastButtonPushed=buttonPinRight;

                  }else if(buttonLeftState==HIGH){
                    lastButtonPushed=buttonPinLeft;

                  }else{
                    lastButtonPushed=0;
                  }                  
}


// ------ navigateMenus -----------
// Bestemmer hvad hver knap gør. 
// Hvis der bliver tilføjet flere knapper skal de også tilføjes her. Men ellers skal der ikke ændres noget her.
void navigateMenus() {
  MenuItem currentMenu=menu.getCurrent();
  
  switch (lastButtonPushed){
    case buttonPinEnter:
      if(!(currentMenu.moveDown())){  //if the current menu has a child and has been pressed enter then menu navigate to item below
        menu.use();
      }else{  //otherwise, if menu has no child and has been pressed enter the current menu is used
        menu.moveDown();
       } 
      break;
    case buttonPinEsc:
      menu.toRoot();  //back to main
      break;
    case buttonPinRight:
      menu.moveRight();
      break;      
    case buttonPinLeft:
      menu.moveLeft();
      break;      
  }
  
  lastButtonPushed=0; //reset the lastButtonPushed variable
}

void loop()
{
  readButtons();  //I splitted button reading and navigation in two procedures because 

  // kontroler hvornår der sidst var aktivitet, hvis det er over XXX sekunter siden skal LCD slukke. (Måske bare begynde at skruge ned?)
  if (lastButtonPushed != 0) {
    LastActivityTime = millis();
    digitalWrite(LCD_LED_PIN, HIGH);   // turn the LCD LED on
  } else if (millis() >= (LastActivityTime + (LCDPowerOffDelay * 1000))) {
    digitalWrite(LCD_LED_PIN, LOW);   // turn the LCD LED off
//    menu.toRoot();  //back to main menu
  }
  
  navigateMenus();  //in some situations I want to use the button for other purpose (eg. to change some settings)
  
  // Update Color Palette kun hvis det er ændret.
  int LastColorPaletteNumber;
  if (LastColorPaletteNumber != ColorPaletteNumber)
  {
    LastColorPaletteNumber = ColorPaletteNumber;
    UpdateLEDColorPalette();
  }
  
  
  
  // LED loop
  UpdateLEDPattern();
  FastLED.show();
  FastLED.delay(1000 / Updates_per_Second);
} //loop()... 

