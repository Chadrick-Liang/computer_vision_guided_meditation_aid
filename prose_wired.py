import cv2
import mediapipe as mp
import numpy as np
import datetime
import math as math
import serial

serialcomm = serial.Serial('COM6', 9600)
serialcomm.timeout = 1

mp_drawing = mp.solutions.drawing_utils
mp_pose = mp.solutions.pose

ini_list = []
list_count = 0
last = datetime.datetime.now()

cap = cv2.VideoCapture(0)
## Setup mediapipe instance
with mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5) as pose:
    while cap.isOpened():
        ret, frame = cap.read()
        current = datetime.datetime.now()
        
        # Recolor image to RGB
        image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image.flags.writeable = False
      
        # Make detection
        results = pose.process(image)
    
        # Recolor back to BGR
        image.flags.writeable = True
        image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
        
        # Render detections
        mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS,
                                mp_drawing.DrawingSpec(color=(245,117,66), thickness=2, circle_radius=2), 
                                mp_drawing.DrawingSpec(color=(245,66,230), thickness=2, circle_radius=2) 
                                 )      

        height, width, x = image.shape      

        left_shoulder = results.pose_landmarks.landmark[mp_pose.PoseLandmark.LEFT_SHOULDER.value].y
        right_shoulder = results.pose_landmarks.landmark[mp_pose.PoseLandmark.RIGHT_SHOULDER.value].y
        lefty = height - int(round(left_shoulder, 3) * height)
        righty = height - int(round(right_shoulder, 3) * height)

        
        # Check if both shoulders are detected
        if left_shoulder and right_shoulder and (current - last).total_seconds() >= 1:
            #print(f"left shoulder is at height {lefty} and right shoulder is at height {righty}")
            if list_count < 10:
                ini_list.append(lefty)
                ini_list.append(righty)
                list_count += 1
                print(f"Hello? the list count is {list_count}")
            if list_count == 10:
                ground = sum(ini_list)/len(ini_list)
                print(f"The average resting value is {ground}")
                list_count += 1
            if list_count > 10:
                ele =math.ceil((lefty + righty)/2 - ground)
                if ele <= 0:
                    ele = 1
                else:
                    ele = round((ele / 30) * 90)
                print(f"The elevation is {ele}")
                serialcomm.write(str(ele).encode())
                #serialcomm.write('\n'.encode())
            last = current
        
        cv2.imshow('Mediapipe Feed', image)

        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

    #serialcomm.close()
    cap.release()
    cv2.destroyAllWindows()