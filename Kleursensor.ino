//Benodigde Libraries
#include "Wire.h"
#include "Adafruit_TCS34725.h"
 
// Initialiseer het kleurensensor
// Bron: https://learn.adafruit.com/adafruit-color-sensors/program-it
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

//Prototypes
char kleurdetectie(void);
 
//Setup wordt eenmaal uitgevoerd wanneer de Arduino start
void setup() 
{
 Serial.begin(9600); 
 //Controleer of de kleurensensor iets teruggeeft
  if (tcs.begin()) 
  {
    Serial.println("Sensor gevonden");
  } 
  else 
  {
    //Geen sensor gevonden. Zet het programma op dit punt stil
    Serial.println("Kleursensor niet gevonden ... stoppen!");
    while (1); // Stop! Dit weghalen voor uiteindelijke programma.
  } 
}
 
void loop() 
{
  kleurdetectie(); 
}

char kleurdetectie(void)
{
  //Variabele voor verschillende kleuren:
  char rood = 0;
  char groen = 0;
  char blauw = 0;
  char geel = 0;
  char oranje = 0;
  
  // De sensor retourneert waarden voor R, G, B en een duidelijke waarde
  uint16_t clearcol, red, green, blue;
  float average, r, g, b;
  delay(100); // Kleurmeting duurt circa 50ms, daarom delay
  tcs.getRawData(&red, &green, &blue, &clearcol);
  
  // Poging om de kleur te bepalen voor de medicijndoosjes van kleuren ROOD, GROEN en BLAUW. 
  // Gemiddelde RGB
  average = (red+green+blue)/3;     // Gemiddeld kleurwaarde, alle waarden liggen nu rond de 1 
  r = red/average;
  g = green/average;
  b = blue/average;

  //Voer de duidelijke waarde en r, g, b voer serieel uit om te controleren dat r, g en b tussen 0,5 en 1,5 moeten zijn. 
  //Als de sensor rood ziet, moet r ruim boven 1,0 liggen, g en b tussen 0,5 en 1,0, enz.
  Serial.print("\tCLEAR:"); Serial.print(clearcol);
  Serial.print("\tROOD:"); Serial.print(r);
  Serial.print("\tGROEN:"); Serial.print(g);
  Serial.print("\tBLAUW:"); Serial.print(b);
  
  if ((r > 1.4) && (g < 0.9) && (b < 0.9)) 
  {
    Serial.print("\tROOD");
    rood = 1 ;  
  }
  else if ((r < 0.95) && (g > 1.4) && (b < 0.9)) 
  {
    Serial.print("\tGROEN");
    groen = 1;
    //Hier komt de voor de servo's aanbesturing.  
  }
  else if ((r < 0.8) && (g < 1.2) && (b > 1.2)) 
  {
    Serial.print("\tBLAUW");
    blauw = 1;
    //Hier komt de voor de servo's aanbesturing. 
  }
  else if ((r > 1.15) && (g > 1.15) && (b < 0.7)) 
  {
    Serial.print("\tGEEL");
    geel = 1;
    //Hier komt de voor de servo's aanbesturing. 
  }
  else if ((r > 1.4) && (g < 1.0) && (b < 0.7)) 
  {
    Serial.print("\tORANJE");
    oranje = 1;
    //Hier komt de voor de servo's aanbesturing. 
  } 
  else 
  {
    Serial.print("\tGEEN KLEUR GEVONDEN"); 
  } 
  // Output line break
  Serial.println("");
  // Pas de wachttijd aan voor seriële foutopsporing aan:
  delay(100);
}
