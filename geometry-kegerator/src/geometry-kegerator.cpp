/*
 * This code listens for a button press and then sends
 * an event, which a mesh node is subscribed to.
 * 
 * The point is to switch between mesh publish and cloud
 * publish to see what the experience is like in terms of timing
 */

#include "Particle.h"
#include "geometry-kegerator.h"
// #include "Adafruit_GFX.h"
// #include "Adafruit_SSD1306.h"
#include "oled-wing-adafruit.h"

//#define CLOUD

// Adafruit_SSD1306 display   = Adafruit_SSD1306(); 
OledWingAdafruit display = OledWingAdafruit(7);

static uint8_t r = 255;
static uint8_t g = 0;
static uint8_t b = 0;

double input               = 20.0;
double output              = 0;
double output_ms           = 2500.0;
double setpoint            = 32.0;

void doDisplay()
{
    display.clearDisplay(); // Clear the display
    
    display.setTextSize(1); //Set our text size, size 1 correlates to 8pt font
    display.setTextColor(WHITE); //We're using a Monochrome OLED so color is irrelevant, pixels are binary.
    display.setCursor(0,0); //Start position for the font to appear
    display.println("Hello World!");
    display.display();
}

void eventHandler(const char *event, const char *data)
{
    if( r == 255 )
    {
        r = 0;
        g = 255;
        b = 0;
    }
    else if ( g == 255 )
    {
        r = 0;
        g = 0;
        b = 255;
    }
    else
    {
        r = 255;
        g = 0;
        b = 0;
    }
    
    RGB.control(true);
    RGB.color(r, g, b);

    Serial.print(Time.timeStr()); Serial.println(": Receiving Event");
}

void setup()
{
    Serial.begin(115200);
#ifdef CLOUD    
    Particle.subscribe("group-event", eventHandler, MY_DEVICES);
#else
    Mesh.subscribe("group-event", eventHandler);
#endif

    // display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C address 0x3C (for the 128x32)
    // display.clearDisplay(); // Clear the display
    
    // doDisplay();

    display.setup();

	display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Hello, world!");
	display.display();

}
 
void loop() 
{
    display.loop();

	if (display.pressedA()) 
    {
        Serial.println("Button A Pressed");
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0,0);
		display.println("In loop!");
		display.display();
	}
}