/* Alle mønstre skal oprettes i denne fil.

Listen over dem der er oprettet nu:
0  TurnLightsOff()
1  ChasingLights()
2  Fire2012WithPalette()

*/

// -------------- UpdateLEDPattern - Start ----------------------
// UpdatePattern er den funktion der bliver kørt i loop()
void UpdateLEDPattern()
{
  if (PatternNumber == 1) {TurnLightsOff();}
//  if (PatternNumber == 1) {fill_solid( leds, NUM_LEDS, CRGB::Black);} // Skal testes <---------------------------
//  if (PatternNumber == 1) {fadeToBlackBy( leds, NUM_LEDS, 1);} // Skal testes <--------------------------- test også hvad der sker når 1 ændres.
  if (PatternNumber == 2) {ChasingLights();}
  if (PatternNumber == 3) {Fire2012WithPalette();}
  if (PatternNumber == 4) {softtwinkles();}
//  if (PatternNumber == 5) {confetti();}
  
}
// -------------- UpdateLEDPattern - Slut ----------------------


// -------------- Turn lights off - Start ----------------------
void TurnLightsOff()
{
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
  }
}

// -------------- Turn lights off - Slut ----------------------


// -------------- Chasing Lights - Start ----------------------

void ChasingLights()
{
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */

  int colorIndex = startIndex;
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 3; // styre hvor mange steps der skal hver mellem hver LED.
  }
}

// -------------- Chasing Lights - Slut ----------------------

// -------------- Fire2012 by Mark Kriegsman - Start ----------------------

// Fire2012 by Mark Kriegsman, July 2012
// as part of "Five Elements" shown here: http://youtu.be/knWiGsmgycY
//// 
// This basic one-dimensional 'fire' simulation works roughly as follows:
// There's a underlying array of 'heat' cells, that model the temperature
// at each point along the line.  Every cycle through the simulation, 
// four steps are performed:
//  1) All cells cool down a little bit, losing heat to the air
//  2) The heat from each cell drifts 'up' and diffuses a little
//  3) Sometimes randomly new 'sparks' of heat are added at the bottom
//  4) The heat from each cell is rendered as a color into the leds array
//     The heat-to-color mapping uses a black-body radiation approximation.
//
// Temperature is in arbitrary units from 0 (cold black) to 255 (white hot).
//
// This simulation scales it self a bit depending on NUM_LEDS; it should look
// "OK" on anywhere from 20 to 100 LEDs without too much tweaking. 
//
// I recommend running this simulation at anywhere from 30-100 frames per second,
// meaning an interframe delay of about 10-35 milliseconds.
//
// Looks best on a high-density LED setup (60+ pixels/meter).
//
//
// There are two main parameters you can play with to control the look and
// feel of your fire: COOLING (used in step 1 above), and SPARKING (used
// in step 3 above).
//
// COOLING: How much does the air cool as it rises?
// Less cooling = taller flames.  More cooling = shorter flames.
// Default 55, suggested range 20-100 
//#define COOLING  55
int Fire2012Cooling = 55;

// SPARKING: What chance (out of 255) is there that a new spark will be lit?
// Higher chance = more roaring fire.  Lower chance = more flickery fire.
// Default 120, suggested range 50-200.
//#define SPARKING 120
int Fire2012Sparking = 120;

void Fire2012WithPalette()
{
  random16_add_entropy( random());
// Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS];

  // Step 1.  Cool down every cell a little
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((Fire2012Cooling * 10) / NUM_LEDS) + 2));
    }
  
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if( random8() < Fire2012Sparking ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }

    // Step 4.  Map from heat cells to LED colors
    for( int j = 0; j < NUM_LEDS; j++) {
      // Scale the heat value from 0-255 down to 0-240
      // for best results with color palettes.
      byte colorindex = scale8( heat[j], 240);
      leds[j] = ColorFromPalette( currentPalette, colorindex);
    }
}

// -------------- Fire2012 by Mark Kriegsman - Slut ----------------------



const CRGB lightcolor(8,7,1);

void softtwinkles() {
  for( int i = 0; i < NUM_LEDS; i++) {
    if( !leds[i]) continue; // skip black pixels
    if( leds[i].r & 1) { // is red odd?
      leds[i] -= lightcolor; // darken if red is odd
    } else {
      leds[i] += lightcolor; // brighten if red is even
    }
  }
  
  if( random8() < 80) {
    int j = random16(NUM_LEDS);
    if( !leds[j] ) leds[j] = lightcolor;
  }
}
 


/*
; Et lys bevæger sig langsomt og ikke i en fast fart. Skifter farve på hver ny tur.
void testpattern(){
static int testLEDnr = 1;
static int colorindex = 1;
if (testLEDnr == 1) { colorindex = random8(); }
fadeToBlackBy(leds, NUM_LEDS, 1); //Sluk alle LEDs.
leds[testLEDnr] = ColorFromPalette(currentPalette, colorindex);
if (random8(1, 7) > 4){
testLEDnr++;
}
//	testLEDnr = (testLEDnr + (random8(1, 7) - 2));
if (testLEDnr > NUM_LEDS) { testLEDnr = 0; }
}

//-----------------------------

// Begyndelsen på en BPM funktion.

void bpmpattern(){
fill_solid(leds, NUM_LEDS, CRGB::Black); // kun en led skal køre det her.

int bpm = beat8(180);
for (int i = 0; i < NUM_LEDS; i++) {
	//		leds[i] = CRGB::Blue;
	int wave = cubicwave8(bpm);
	//		int wave = bpm;
	int wave2 = map(wave, 1, 256, 1, 100);
	if (i <= wave2) { leds[i] = CRGB::Blue; }
}
}
*/



