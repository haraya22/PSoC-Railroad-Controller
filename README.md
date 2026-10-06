# Multi-Rate-Interactive-State-Machine-Embedded-Controller
The system is an interactive hardware layout which includes a character LCD dashboard, pushbuttons, and a duel-channel LED array.  By engineering an asynchronous software scheduling engine, the project manages multiple things such as:
##
- Time interval text scrolling,
- Switching cycles
- LED alternative frequencies. 
##
All of these implementations were made for the processor to never freeze while running. The application features an advanced runtime state-tracking which allows users to toggle an alternating "railroad-style" blinking pattern. With this implementation users are able to:
##
- Freeze sequence mid-execution on either light (LED3 or LED4)
- View a live button-press counter (tallies)
- Trigger a kill-switch system (SW3) that would stop the LEDs from processing the pattern.
