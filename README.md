# 4WD Arduino Robot Car
[🚀 View Interactive Schematic Dashboard](https://tanixshivram.github.io/Arduino-Robo-Car/)

## What this car is all about
This is a 4WD robot car I built that can either be driven manually or act on its own. I wanted to create a platform that could handle both user input and autonomous navigation in one package.

## How it works
The car has two main "personalities":
* **Manual Mode:** Using the "Arduino Bluetooth Control" app on my phone, I can steer the car around like a remote-controlled vehicle. It's great for navigating tight spaces manually.(it also has automatic breaking when an object is detected so i dont crash into a wall while driving)
* **Autonomous Mode:** When I switch to this mode, the car uses its ultrasonic sensor to "see" what's in front of it. If it gets too close to an obstacle, it automatically hits the brakes and stops, so it doesn't crash into anything. then it checks which side is obstacle free and moves in that direction.

## The setup
I built this using an Arduino Uno and an L298N motor driver to power the 4 wheels. For the communication, I’m using an HC-05 Bluetooth module. 

One of the cooler challenges I ran into was that the Bluetooth module works on 3.3V, but the Arduino sends signals at 5V. To make sure I didn't fry the module, I built a simple voltage divider using a couple of resistors to keep the signals safe. I also made sure everything shared a common ground so the controls stay responsive and the connection stays solid.

## What's next?
*(Coming Soon: Demo video of the car driving and the auto-braking in action!)*
