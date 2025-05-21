# Computer vision-guided meditation aid

A buoyant flower lamp meant as a decorative element at quiet water bodies./

## Brief overview video
https://youtu.be/GyVzt1gu94g

## Explanation

It essentially has 2 functions,\

1) Upon detecting the user's face, switch from idle mode (LEDs are statically yellow) to active mode (LEDs gradually transition across multiple colours).\
2) In meditation mode, the camera establishes a baseline for the user's standing shoulder height for over 10s. Henceforth, the lamp brightness will vary according to the user's breathing patterns.\
Breathing in increases the brightness, breathing out dims it.\

The camera is connected to the arduino, which controls LED behaviour, either through wired connection or bluetooth.\
face_bluetooth.py performs function 1 across a bluetooth connection.\
face_wired.py performs function 1 across a wired connection.\
prose_wired.py performs function 2 across a wired connection.\
fingers_wired.py is a add-on script that varies brightness depending on how open or closed the user's palm is.\

In the arduino folder,\
new_rectified.ino performs function 1.\
wired_brightness_grad.ino performs function 2.\


