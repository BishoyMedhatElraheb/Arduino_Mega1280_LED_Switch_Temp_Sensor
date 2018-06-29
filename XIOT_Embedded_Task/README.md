The instructions for setting the app up in a local sandbox :-
--> First i didn't understand what do you mean by local sandbox, i search the internet and found more and more applications to use as a sandbox,
    but all of them work with specific development kit.
--> So finally i think that Proteus simulation program can used as a local sandbox to test the code i write.
--> So i use proteus version.8 and use the arduino library which included in (Arduino Library for Proteus.rar) folder.


Assumptions i’ve made :-
--> I choose to work with Arduino Mega 1280
--> My idea is when you begin the simulation, i ask the user to input the number of the Switch Pin & the LED Pin.
--> As example, if the user choose the Switch Pin 3 & the LED Pin 13 then try to press the button @ Pin 3 @ Proteus.
    the LED @ Pin 13 will turn on. and so on.
--> If the user want to control another Pins, 
    he must first press the button @ Pin 18 then the program will ask him again to input the number of the Switch Pin & the LED Pin.
--> Of course while the program work, the temperature function also work & give the temperature value 
    which come from the sensor LM35 every 3 seconds.


Issues with my example :-
--> I have three problems that i can't solve while making the program.
--> The first one is the tempertaure function that has a delay of 3 seconds,
    the problem is this delay make the whole void loop function wait for these 3 seconds and continue work after that.
--> The second problem happens when the user press switch @ Pin 18, if he didn't put the input pin number very quickly, 
    the program will put the switch pin = 0 and the program will stuck.
--> The third problem happens when the void loop start, 
    the temperature function will not work untill the user input the number of the Switch Pin & the LED Pin.