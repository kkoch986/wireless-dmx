# ESP-NOW Base Wireless DMX Rig

My home brewed wireless DMX rig using cheap esp32 chips and the
[ESP-NOW](https://www.espressif.com/en/products/software/esp-now/overview)
framework for transmitting data among a small network of ESP-based devices.

The general idea is to be able to extend my core DMX set up for the animatronic skeletons
wirelessly into devices spread across the entire scene without needing wires.

Existing wireless DMX setups exist but they can run upwards of $200 for a transmitter 
and a handful of receivers. 
Currently I'm testing it on a stack of Wemos D1 Minis and it's working well so far
with an all-in cost under $20 for a controller and 9 receivers.

There are also other internet-based protocols like ArtNet DMX and E131 but my goal with
this was not to introduce any more controllers to my set up and be able to just plug 
a device inline to my existing DMX set up so I avoided introducing much new stuff.

I also was reading about ESP-NOW and was curious to play around with it so...

TODO: document more about how the set up works and how to use it
TODO: document the schematics etc...
TODO: model, print and commit the models for the cases
