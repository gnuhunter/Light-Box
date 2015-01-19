/* Alle Palettes skal oprettes i denne fil.

Listen over dem der er oprettet nu:
SetupTotallyRandomPalette()
SetupBlackAndWhiteStripedPalette()
SetupPurpleAndGreenPalette()
myRedWhiteBluePalette_p
myRedPalette_p
myBluePalette_p
myGreenPalette_p

*/

// -------------- UpdateLEDColorPalette - Start ----------------------
// UpdatePattern er den funktion der bliver kørt i loop()
void UpdateLEDColorPalette()
{
  // Preset color palettes from FastLED:
  if (ColorPaletteNumber == 1) {currentPalette = RainbowColors_p;}
  if (ColorPaletteNumber == 2) {currentPalette = RainbowStripeColors_p;}
  if (ColorPaletteNumber == 3) {currentPalette = OceanColors_p;}
  if (ColorPaletteNumber == 4) {currentPalette = CloudColors_p;}
  if (ColorPaletteNumber == 5) {currentPalette = LavaColors_p;}
  if (ColorPaletteNumber == 6) {currentPalette = ForestColors_p;}
  if (ColorPaletteNumber == 7) {currentPalette = PartyColors_p;}
  if (ColorPaletteNumber == 8) {currentPalette = HeatColors_p;} 
  // Custom made color palettes:
  if (ColorPaletteNumber == 9) {SetupTotallyRandomPalette();}
  if (ColorPaletteNumber == 10) {SetupBlackAndWhiteStripedPalette();}
  if (ColorPaletteNumber == 11) {SetupPurpleAndGreenPalette();}
  if (ColorPaletteNumber == 12) {currentPalette = myRedWhiteBluePalette_p;}
  if (ColorPaletteNumber == 13) {currentPalette = myRedPalette_p;}
  if (ColorPaletteNumber == 14) {currentPalette = myBluePalette_p;}
  if (ColorPaletteNumber == 15) {currentPalette = myGreenPalette_p;}
  if (ColorPaletteNumber == 16) {SetupFire2012FirePalette();}
  if (ColorPaletteNumber == 17) {SetupFire2012AquaPalette();}
  if (ColorPaletteNumber == 18) {SetupFire2012SimpleRedPalette();} 
  if (ColorPaletteNumber == 19) {currentPalette = OrangePalette_p;}
  
//  if (ColorPaletteNumber == 20) {currentPalette = SetupPurpleAndGreenPalette();}
}
// -------------- UpdateLEDColorPalette - Slut ----------------------


// -------------- Custom made color palettes - Start -----------------

// There are several different palettes of colors demonstrated here.
//
// FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
// OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
//
// Additionally, you can manually define your own color palettes, or you can write
// code that creates color palettes on the fly.  All are shown here.

// This function fills the palette with totally random colors.
void SetupTotallyRandomPalette()
{
  for( int i = 0; i < 16; i++) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code.  Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid( currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;

}

// This function sets up a palette of purple and green stripes.
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;
  
  currentPalette = CRGBPalette16( 
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black );
}


// This example shows how to set up a static color palette
// which is stored in PROGMEM (flash), which is almost always more 
// plentiful than RAM.  A static PROGMEM palette like this
// takes up 64 bytes of flash.
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};

const TProgmemPalette16 myRedPalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Black, // 'white' is too bright compared to red and blue
  CRGB::Black,
  CRGB::Black,

  CRGB::Red,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,

  CRGB::Red,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Red,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black
};

const TProgmemPalette16 myBluePalette_p PROGMEM =
{
  CRGB::Blue,
  CRGB::Black, // 'white' is too bright compared to red and blue
  CRGB::Black,
  CRGB::Black,

  CRGB::Blue,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,

  CRGB::Blue,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black
};

const TProgmemPalette16 myGreenPalette_p PROGMEM =
{
  CRGB::Green,
  CRGB::Black, // 'white' is too bright compared to red and blue
  CRGB::Black,
  CRGB::Black,

  CRGB::Green,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,

  CRGB::Green,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black,
  CRGB::Green,
  CRGB::Black,
  CRGB::Black,
  CRGB::Black
};

const TProgmemPalette16 OrangePalette_p PROGMEM =
{
  CRGB::Orange,
  CRGB::Black,
  CRGB::Black,
  
  CRGB::OrangeRed,
  CRGB::Black,
  CRGB::Black,
  
  CRGB::Orange,
  CRGB::Black,
  CRGB::Black,
  
  CRGB::OrangeRed,
  CRGB::Black,
  CRGB::Black  
};





// Additionl notes on FastLED compact palettes:
//
// Normally, in computer graphics, the palette (or "color lookup table")
// has 256 entries, each containing a specific 24-bit RGB color.  You can then
// index into the color palette using a simple 8-bit (one byte) value.
// A 256-entry color palette takes up 768 bytes of RAM, which on Arduino
// is quite possibly "too many" bytes. 
//
// FastLED does offer traditional 256-element palettes, for setups that
// can afford the 768-byte cost in RAM.
//
// However, FastLED also offers a compact alternative.  FastLED offers
// palettes that store 16 distinct entries, but can be accessed AS IF
// they actually have 256 entries; this is accomplished by interpolating
// between the 16 explicit entries to create fifteen intermediate palette 
// entries between each pair.
//
// So for example, if you set the first two explicit entries of a compact 
// palette to Green (0,255,0) and Blue (0,0,255), and then retrieved 
// the first sixteen entries from the virtual palette (of 256), you'd get
// Green, followed by a smooth gradient from green-to-blue, and then Blue.

// -------------- Custom made color palettes - Slut -----------------

// -------------- Palettes from Fire2012 by Mark Kriegsman - Start ----------------------

  // This first palette is the basic 'black body radiation' colors,
  // which run from black to red to bright yellow to white.
  //  gPal = HeatColors_p;

  // These are other ways to set up the color palette for the 'fire'.
  // First, a gradient from black to red to yellow to white -- similar to HeatColors_p
  //  gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  void SetupFire2012FirePalette()
  {
    currentPalette = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::Yellow, CRGB::White);
  }

  
  // Second, this palette is like the heat colors, but blue/aqua instead of red/yellow
  //  gPal = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
  void SetupFire2012AquaPalette()
  {
    currentPalette = CRGBPalette16( CRGB::Black, CRGB::Blue, CRGB::Aqua,  CRGB::White);
  }

  // Third, here's a simpler, three-step gradient, from black to red to white
  //  gPal = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
  void SetupFire2012SimpleRedPalette()
  {
    currentPalette = CRGBPalette16( CRGB::Black, CRGB::Red, CRGB::White);
  }

// -------------- Palettes from Fire2012 by Mark Kriegsman - Start ----------------------
