import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import sys
import time


def circle():
	gray = cv.cvtColor(frame, cv.COLOR_BGR2GRAY)  
	gray = cv.medianBlur(gray, 7)
	rows = gray.shape[0]
	circles = cv.HoughCircles(gray, cv.HOUGH_GRADIENT, 1, rows / 8,param1=100, param2=25,
    	minRadius=20, maxRadius=70)

	if circles is not None:
		circles = np.uint16(np.around(circles))
		for i in circles[0, :]:
			center = (i[0], i[1])
			# circle center
			cv.circle(frame, center, 1, (0, 100, 100), 3)
			# circle outline
			radius = i[2]
			cv.circle(frame, center, radius, (255, 0, 255), 3)

	cv.imshow("detected circles", frame)
	cv.waitKey(0)

def hsv_colormask(frame):

	hsv_image = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
	min1hsv = np.array([5, 50, 20])   # calc min and max values for mask
	max1hsv = np.array([15, 255, 255])
	min2hsv = np.array([0, 90, 20])   # lower part values
	max2hsv = np.array([15, 170, 255])
	min3hsv = np.array([15, 20, 20])   # upper part values
	max3hsv = np.array([30, 40, 255])
	gray2 = cv.inRange(hsv_image,min1hsv,max1hsv)
	#gray2 = gray2 + cv.inRange(hsv_image,min2hsv,max2hsv) + cv.inRange(hsv_image,min3hsv,max3hsv)

	return gray2

if __name__ == "__main__":
	
    vid = cv.VideoCapture(0)
	while(True):
		ret, img = vid.read()
		img_th = hsv_colormask(img)

		kernel = np.ones((3,3), np.uint8)

		img_th = cv.dilate(img_th, kernel,iterations=1)
		eroded = cv.erode(img_th,kernel,iterations=1)
		eroded_bgr =  cv.cvtColor(eroded, cv.COLOR_GRAY2BGR)
		contours, _ = cv.findContours(eroded, cv.RETR_TREE, cv.CHAIN_APPROX_NONE)

		max_c = 0
		for i,c in enumerate(contours):
			x,y,w,h = cv.boundingRect(c)
			if(w/h < 1.3 and w/h > 0.7 and w > 10 and h > 10):
				eroded_bgr =  cv.cvtColor(eroded, cv.COLOR_GRAY2BGR)
				cv.putText(eroded_bgr, str(w), (x,y - 10), cv.FONT_HERSHEY_SIMPLEX, 0.9, (36,255,12), 2)
				cv.rectangle(eroded_bgr, (x, y), (x + w, y + h), (0,255,0), 1)

		cv.circle(img, (150,150), 7, (0, 0, 0), 2)
		cv.imshow("feed", img)
		cv.imshow("Display window", eroded_bgr)
		cv.imshow("h",cv.cvtColor(img,cv.COLOR_BGR2HSV)[:,:,0])
		cv.imshow("s",cv.cvtColor(img,cv.COLOR_BGR2HSV)[:,:,1])
		print(cv.cvtColor(img,cv.COLOR_BGR2HSV)[150,150,:])

		if cv.waitKey(1) & 0xFF == ord('q'):
			break

	vid.release()
	cv.destroyAllWindows()
	"""
	frame = cv.imread("images/sandberg_000.png")
	frame = cv.resize(frame, (800, 600), interpolation=cv.INTER_LINEAR)
	
	p1=(475,425)
	p2=(475,450)
	p3=(475,475)

	hsv_image = cv.cvtColor(frame, cv.COLOR_BGR2HSV)   # convert image to hsv color

	# get different color channels
	b = frame[:,:,0]
	g = frame[:,:,1]
	r = frame[:,:,2]

	h = hsv_image[:,:,0]
	s = hsv_image[:,:,1]
	v = hsv_image[:,:,2]

	gray2 = hsv_colormask(frame)
	gray3 = cv.dilate(gray2, None,iterations=3)
	gray4 = cv.erode(gray3, None,iterations=3)

	cv.circle(frame, p1, 7, (0, 0, 0), 2)
	cv.circle(frame, p2, 7, (0, 0, 0), 2)
	cv.circle(frame, p3, 7, (0, 0, 0), 2)
	print(hsv_image[p1])
	print(hsv_image[p2])
	print(hsv_image[p3])



	plt.subplot(2,3,1)
	plt.imshow(h,'gray')
	plt.title('h channel')
	plt.subplot(2,3,2)
	plt.imshow(s,cmap='gray')
	plt.title('s channel')
	plt.subplot(2,3,3)
	plt.imshow(h,cmap='gray')
	plt.title('v channel')
	plt.subplot(2,3,4)
	plt.imshow(r,'gray')
	plt.title('r channel')
	plt.subplot(2,3,5)
	plt.imshow(g,cmap='gray')
	plt.title('b channel')
	plt.subplot(2,3,6)
	plt.imshow(b,cmap='gray')
	plt.title('b channel')

	cv.imshow('Original',frame)
	cv.imshow('color_mask',gray2)
	cv.imshow('erode',gray4)
	cv.waitKey(0)
	plt.show()
	cv.destroyAllWindows()
	"""
