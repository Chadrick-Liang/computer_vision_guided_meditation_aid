import cv2
import mediapipe as mp
import datetime
import serial
import time

cap = cv2.VideoCapture(0)

serialcomm = serial.Serial('COM5', 9600)
serialcomm.timeout = 1

mpDraw = mp.solutions.drawing_utils
mpFaceMesh = mp.solutions.face_mesh
faceMesh = mpFaceMesh.FaceMesh(max_num_faces=10)
#next_time = datetime.datetime.now()
#delta = datetime.timedelta(seconds=0.1)
toggle = 0

while True:
    period = datetime.datetime.now()
    success, img = cap.read()
    imgRGB = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = faceMesh.process(imgRGB)
    if results.multi_face_landmarks:
        for faceLms in results.multi_face_landmarks:
            mpDraw.draw_landmarks(img, faceLms, mpFaceMesh.FACEMESH_CONTOURS)
        #period >= next_time and
        if toggle == 0:
            #serialcomm.write(str(1).encode())
            #serialcomm.write(b"b")
            #serialcomm.write(str('\n').encode())
            time.sleep(2)
            serialcomm.write(str(5).encode())
            print(5)
            #next_time += delta
            toggle = 1
    elif (not results.multi_face_landmarks) and toggle == 1:
        # and period >= next_time
        #serialcomm.write(b"a")
        #serialcomm.write(str('\n').encode())
        time.sleep(2)
        serialcomm.write(str(4).encode())
        print(4)
        #next_time += delta
        toggle = 0
    else:
         pass

    cv2.imshow('img', img)
    if cv2.waitKey(1) == ord('q'):
        break

serialcomm.close()
cap.release()
cv2.destroyAllWindows()