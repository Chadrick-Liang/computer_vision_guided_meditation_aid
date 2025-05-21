import cvzone
import cv2
import serial
import datetime

from cvzone.HandTrackingModule import HandDetector
cap = cv2.VideoCapture(0)
detector = HandDetector(detectionCon=0.8, maxHands=1)

serialcomm = serial.Serial('COM6', 9600)
serialcomm.timeout = 1
last = datetime.datetime.now()

while True:
    ret, frame = cap.read()
    current = datetime.datetime.now()
    frame = cv2.resize(frame, (800, 800))
    hands, img = detector.findHands(frame)
    if hands:
        lmList=hands[0]
        #length, info, img = detector.findDistance(lmList['lmList'][8][0:2], lmList['lmList'][4][0:2], img)
        length, info, img = detector.findDistance(lmList['lmList'][12][0:2], lmList['lmList'][0][0:2], img)
        #print(lmList)
        #fingerUp=detector.fingersUp(lmList)
        if (current - last).total_seconds() >= 1:
            length = round((length/310) * 80)
            print(length)
            serialcomm.write(str(length).encode())
            last = current

        '''print(fingerUp)
        if fingerUp==[0,0,0,0,0]:
            cv2.putText(frame,'Finger count:0',(20,460),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),1,cv2.LINE_AA)
        elif fingerUp==[0,1,0,0,0]:
            cv2.putText(frame,'Finger count:1',(20,460),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),1,cv2.LINE_AA)    
        elif fingerUp==[0,1,1,0,0]:
            cv2.putText(frame,'Finger count:2',(20,460),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),1,cv2.LINE_AA)
        elif fingerUp==[0,1,1,1,0]:
            cv2.putText(frame,'Finger count:3',(20,460),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),1,cv2.LINE_AA)
        elif fingerUp==[0,1,1,1,1]:
            cv2.putText(frame,'Finger count:4',(20,460),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),1,cv2.LINE_AA)
        elif fingerUp==[1,1,1,1,1]:
            cv2.putText(frame,'Finger count:5',(20,460),cv2.FONT_HERSHEY_COMPLEX,1,(255,255,255),1,cv2.LINE_AA)'''
    
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()


