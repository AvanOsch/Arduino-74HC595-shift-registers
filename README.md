# Arduino-74HC595-shift-registers
I forked this from https://github.com/janisrove/Arduino-74HC595-shift-registers to make some changes to the original:<br/>
(Big thanks to Janis Rove for sharing his original code!)
- Couple of small changes to the effects
- Only amount of shift registers has to be changed (presuming all have 8 LEDs connected)
- Added more comments to the code to clarify what's going on

# I also created a new version, with the same effects:
I needed this in a project where the code also checks for button presses, updates to a screen and other things are happening that can't be paused while waiting for delay() to finish.
- Totally re-written version, that doesn't use "delay()"
- Only amount of shift registers need to be set (presuming all have 8 LEDs connected)
- Same 5 effects as in Janis Rove's version
- Added optional dimmer pin which dims all LEDs at the same time
  - Dimmer pin needs to be a PWM pin
  - One dimmer pin can dim all shift registers
  - It's also possible to dim each shift register separately
  - It's NOT possible to dim LEDs separately (at least not by this method)
  
  If you have additions, improvements or new effects, please don't hasitate to contact me or start your own fork!
