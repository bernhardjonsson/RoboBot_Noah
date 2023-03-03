# -*- coding: utf-8 -*-
"""
Created on Wed Mar  1 11:10:52 2023

@author: ctn
"""

import cv2
import sys
import numpy as np
import time

img = cv2.imread(cv2.samples.findFile("new/sandberg_001.png"))
#if img is None:
#    sys.exit("Could not read the image.")

vid = cv2.VideoCapture(0)

h = (230,255,255)
l = (86,125,224)



#H = (200,250,255)
#L = (150,200,200)

#while(True):
#ret, img = vid.read()
img_yuv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
#img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
img_th = cv2.inRange(img, l,h)

kernel = np.ones((3,3), np.uint8)
eroded = cv2.erode(img_th,kernel)
eroded_bgr =  cv2.cvtColor(eroded, cv2.COLOR_GRAY2RGB)

contours, _ = cv2.findContours(eroded, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)

max_c = 0
for i,c in enumerate(contours):
    x,y,w,h = cv2.boundingRect(c)
    if(w/h < 1.3 and w/h > 0.7 and w > 10 and h > 10):
        eroded_bgr =  cv2.cvtColor(eroded, cv2.COLOR_GRAY2RGB)
        cv2.putText(eroded_bgr, str(w), (x,y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
        cv2.rectangle(eroded_bgr, (x, y), (x + w, y + h), (0,255,0), 1)

cv2.imshow("Display window", eroded_bgr)
#if cv2.waitKey(1) & 0xFF == ord('q'):
#    break

#vid.release()
#cv2.destroyAllWindows()
ø
