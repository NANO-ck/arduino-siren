# Arduino Uno 2 tones siren
A siren with 2 tones (as the french ones) for an Arduino Uno
You can use it with this audio amplifier I found on Aliexpress to make it louder https://fr.aliexpress.com/item/32663297600.html (there still may be better ones)

# Here are the frequencies of the french services
| Type      | Police        | Firefighters  |
|-----------|---------------|---------------|
| 1rst tone | 435Hz         | 435Hz         |
| 2nd tone  | 580Hz         | 488Hz         |
| Frequency | 60 cycles/min | 30 cycles/min |

# Siren V1
The 1rst version of the siren is very simple, there's only 1 siren type, and you only need an arduino and a buzzer/speaker. You can use an Arduino Uno, NANO, or any other.
Here is how to set it up:
<img src="https://github.com/NANO-ck/arduino-siren/raw/main/siren-v1.PNG" alt="schema v1"/>

# Siren V2
The 2nd version of the siren provides multiple siren types, which you can choose by pressing a single button, which has the role of moving to the other siren type. 
For this version, you will need 5 LEDs (or 4 if you remove the power indicator one), a resistor & a pushbutton (or any switch). If you want to make the sound louder, you can also add an amplifier.

Credits: To make this 2nd version, and to bypass a problem I struggled with, I used this project to inspire me: https://www.tinkercad.com/things/gzWORQfpPWl-siren-system-

Here is how to set it up:
<img src="https://github.com/NANO-ck/arduino-siren/raw/main/siren-v2.PNG" alt="schema v2"/>

# Siren V3
The third version of the siren is the same as the 2nd, but it has an LED display to display the actual siren

Here is how to set it up:
<img src="https://github.com/NANO-ck/arduino-siren/raw/main/siren-v3.PNG" alt="schema v3"/>
