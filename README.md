# Computer vision-guided meditation aid

A buoyant flower lamp meant as a decorative element at quiet water bodies. It blends embodied meditation cues (breathing) with ambient lighting in a decorative water-borne lamp, encouraging mindful stillness through visually intuitive feedback.<br>
Essentially aid users in using their breath as a meditation anchor, giving visual form to their breathing patterns.

---

## Collaborators

- Zhou Ying Qi
  
- Maheshi Parwani
  
- Ch’ng Zhi Qiang
  
- Hadi Priyatna Arief

---

## Brief overview video
<img src="/README_images/flower.png" alt="flower lamp" width="400"/> <br>
https://youtu.be/GyVzt1gu94g

## Explanation

It essentially has 2 functions,<br>

1) Upon detecting the user's face, switch from idle mode (LEDs are statically yellow) to active mode (LEDs gradually transition across multiple colours).<br>
2) In meditation mode, the camera establishes a baseline for the user's standing shoulder height for over 10s. Henceforth, the lamp brightness will vary according to the user's breathing patterns.<br>
Breathing in increases the brightness, breathing out dims it.<br>

The camera is connected to the arduino, which controls LED behaviour, either through wired connection or bluetooth.<br>
face_bluetooth.py performs function 1 across a bluetooth connection.<br>
face_wired.py performs function 1 across a wired connection.<br>
prose_wired.py performs function 2 across a wired connection.<br>
fingers_wired.py is a add-on script that varies brightness depending on how open or closed the user's palm is.<br>

In the arduino folder,<br>
new_rectified.ino performs function 1.<br>
wired_brightness_grad.ino performs function 2.<br>

