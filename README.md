# Casio Calculator External Memory (Casio FX92+)

![github-intro](https://user-images.githubusercontent.com/60618118/148842566-0fca7c9a-aee2-4199-9532-d9d905ae6102.jpg)

The inspiration for this project came initially from the Casio 92B, which was the recommended calculator for the humanities in Belgium and France. Unfortunately the 92B, except for its elegance, was not very impressive...
  
Having recently discovered the 92+ and its algorithmic mode just after high school, I was happy to see that "the" calculator that had been with me for six years was going to keep me busy for a while!
  
 ...The only disappointment was of course that the 92+ has no internal memory.
  
So I thought it would be interesting to create an external, detachable memory module to be able to save those long programs that become a heavy task to rewrite.
  
Although this module can be compatible with any calculator (or any device with a matrix keyboard), it was primarily designed for the Casio FX-92+.

[![Youtube](https://img.youtube.com/vi/2eeQFywnhbU/0.jpg)](https://www.youtube.com/watch?v=2eeQFywnhbU)
  
## The Module
  
An Arduino microcontroller at the heart of the module drives the four integrated circuits (CD4066), which in turn simulate a key press on the calculator. A CD4066 IC consists of 4 bilateral electronic switches, a key on the calculator is "pressed" when the electronic switch corresponding to the column and the electronic switch corresponding to the row of the desired key are activated simultaneously.

At the bottom of the module, 5 buttons are used to select one of the 5 algorithms stored in the EEPROM of the arduino. Each algorithm can contain 200 instructions/keystroke coordinates.
  
## MATRIXIO
  
I also wrote a program to load the algorithms into the arduino's EEPROM. The Instructions and key coordinates can be sent manually via the arduino IDE serial monitor, or automatically via a loader written in Python.

After uploading MATRIXIO to the arduino, set the serial monitor line ending to "newline".
  
`MATRIXIO v1.0 (c) Jan 2022 Aditya Chugh -type 'help'-`

### MATRIXIO Commands
```
xy : 		Instruction, where x is column and y is row of calculator key
a~t : 		Shortcut instruction sequences
write : 	Enable writing of instructions to EEPROM memory
read : 		Disable writing of instructions to EEPROM memory
prog 1~5 : 	Memory address set to beginning of program 1~5
clear 1~5 : 	Clears all 200 instructions of program 1~5
list 1~5 : 	Lists all 200 instructions of program 1~5
addr 0~999 : 	Memory address set to 0~999 (for uno & nano)

On Casio FX-92B & FX-92+, the bottom-most row is matrixed differently, keys should hence be addressed as such : 

'0' : 65
',' : 64
'x10^x' : 63
'ANS/REP' : 62
'EXE' : 61

Shortcut instruction sequences for Casio FX-92+:

a : avancer de
b : tourner de
c : s'orienter ??
d : aller ?? x,y

e : stylo ??crit
f : stylo relev??
g : mettre var ??
h : demander valeur

i : commentaire
j : afficher r??sultat
k : style
l : attendre

m : r??p??ter
n : r??p??ter jusqu'??
o : si alors
p : si alors sinon

q : ex??cuter
r : copier et ins??rer
s : ins??rer ligne
t : tout supprimer

```
## Keyboard Matrix Layout
In order to enter instructions into the memory module, you will need to refer to the second image to get the coordinates of the buttons needing to be "pressed".

<img src="https://user-images.githubusercontent.com/60618118/148846426-03d987a7-4d7a-4fbe-92f6-1d9f49573ca8.jpg" width="33%"> <img src="https://user-images.githubusercontent.com/60618118/148846461-9cea8d04-2e72-436b-bf92-1d6ddaa8ca17.jpg" width="33%"> <img src="https://user-images.githubusercontent.com/60618118/148846635-a3a908b2-60d7-4e95-8a05-c00d08f6e0af.jpg" width="20%">



## Schematic

<img src="https://user-images.githubusercontent.com/60618118/148841993-c133e295-6a00-4389-a011-c1bb7adf9ca5.png" width="40%"> <img src="https://user-images.githubusercontent.com/60618118/148843127-4374f280-dd76-484b-a168-1225d1070dbc.gif" width="33%">

