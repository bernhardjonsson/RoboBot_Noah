import numpy as np
import cv2
print("xx")
# step 1 - load the model

net = cv2.dnn.readNet('best2.onnx')

# step 2 - feed a 640x640 image to get predictions

def format_yolov5(frame):

    row, col, _ = frame.shape
    _max = max(col, row)
    result = np.zeros((_max, _max, 3), np.uint8)
    result[0:row, 0:col] = frame
    return result

image = cv2.imread('raw.png')

h,w = image.shape[:2]
mtx = np.matrix([[1012.48481176142, 2.31917529774243, 673.405383147365],[0, 1012.49214301672, 423.353090608865], [0, 0, 1]])
dist = np.matrix([-0.403525179503551,0.164851054474498,9.698403470899592e-05,-0.00278471711398937])
newcameramtx, roi = cv2.getOptimalNewCameraMatrix(mtx, dist, (w,h), 1, (w,h))
# undistort
dst = cv2.undistort(image, mtx, dist, None, newcameramtx)
x,y,w,h = roi
dst = dst[y:y+h, x:x+w]
image = dst

black = np.zeros((image.shape[0], image.shape[1], 1), dtype = "uint8")
black_all = np.zeros((image.shape[0], image.shape[1], 1), dtype = "uint8")
input_image = format_yolov5(image) # making the image square
blob = cv2.dnn.blobFromImage(input_image , 1/255.0, (640, 640), swapRB=True)
net.setInput(blob)
predictions = net.forward()

# step 3 - unwrap the predictions to get the object detections 

class_ids = []
confidences = []
boxes = []

output_data = predictions[0]
#print(output_data)

image_width, image_height, _ = input_image.shape
x_factor = image_width / 640
y_factor =  image_height / 640

for r in range(25200):
    row = output_data[r]
    confidence = row[4]
    if confidence >= 0.4:

        classes_scores = row[5:]
        _, _, _, max_indx = cv2.minMaxLoc(classes_scores)
        class_id = max_indx[1]
        if (classes_scores[class_id] > .25):
		
            confidences.append(float(confidence))
            class_ids.append(class_id)

            x, y, w, h = row[0].item(), row[1].item(), row[2].item(), row[3].item() 
            left = int((x - 0.5 * w) * x_factor)
            top = int((y - 0.5 * h) * y_factor)
            width = int(w * x_factor)
            height = int(h * y_factor)
            box = np.array([left, top, width, height])
            boxes.append(box)

class_list = []
with open("classes.txt", "r") as f:
    class_list = [cname.strip() for cname in f.readlines()]

indexes = cv2.dnn.NMSBoxes(boxes, confidences, 0.25, 0.45) 

result_class_ids = []
result_confidences = []
result_boxes = []

for i in indexes:
    i = i[0]
    result_confidences.append(confidences[i])
    result_class_ids.append(class_ids[i])
    result_boxes.append(boxes[i])

max_x = 0
max_y = 0
max_h = 0
max_w = 0

for i in range(len(result_class_ids)):

    box = result_boxes[i]
    class_id = result_class_ids[i]

    cv2.rectangle(image, box, (0, 255, 255), 2)
    cv2.rectangle(image, (box[0], box[1] - 20), (box[0] + box[2], box[1]), (0, 255, 255), -1)
    cv2.putText(image, class_list[class_id], (box[0], box[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, .5, (0,0,0))
    x = box[0]
    y = box[1]
    w = box[2]
    h = box[3]
    print(h/w)
    if(h/w > 0.7 and h/w < 1.3):
        cv2.circle(black_all, (int((box[2])/2+box[0]),int((box[3])/2+box[1])), int((box[2])/2)-2, (255,255,255), -1)
        if(w > max_w and h > max_h):
            max_x = x
            max_y = y
            max_h = h
            max_w = w

if len(result_class_ids) > 0:
    cv2.circle(black, (int((max_w)/2+max_x),int((max_h)/2+max_y)), int((max_w)/2)-2, (255,255,255), -1)    

cv2.imwrite("detection.png", image)
cv2.imwrite("black_all.png", black_all)
cv2.imwrite("black.png", black)

#cv2.imshow("output", image)
#cv2.waitKey()
