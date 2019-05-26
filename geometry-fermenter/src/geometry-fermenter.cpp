/*
 * This code listens for a button press and then sends
 * an event, which a mesh node is subscribed to.
 * 
 * The point is to switch between mesh publish and cloud
 * publish to see what the experience is like in terms of timing
 */

#include "Particle.h"
#include "geometry-fermenter.h"

//#define CLOUD

static bool publish = false;

void button_handler(system_event_t event, int duration, void* )
{
    if (!duration) 
    {
        // just pressed
        RGB.control(true);
        RGB.color(255, 0, 255);
        publish = true;
    }
    else 
    { 
        // just released
        RGB.control(false);
    }
}

void setup()
{
    Serial.begin(115200);
    System.on(button_status, button_handler);
}
 
void loop() 
{
    if( publish )
    {
#ifdef CLOUD                
        Serial.print(Time.timeStr()); Serial.println(": Publishing Cloud Event");
        Particle.publish("group-event", PRIVATE);
#else
        Serial.print(Time.timeStr()); Serial.println(": Publishing Mesh Event");
        Mesh.publish("group-event");
#endif
        publish = false;
    }
}