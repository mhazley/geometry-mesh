/*
 * This code listens for a button press and then sends
 * an event, which a mesh node is subscribed to.
 * 
 * The point is to switch between mesh publish and cloud
 * publish to see what the experience is like in terms of timing
 */

#include "Particle.h"
#include "geometry-kegerator.h"

//#define CLOUD

static uint8_t r = 255;
static uint8_t g = 0;
static uint8_t b = 0;

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
}
 
void loop() 
{
    // Empty for now
}