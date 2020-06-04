from requests import Session

import time

# State vars
Distance = "UNDEFINED"
Direction = "UNDEFINED"
Firing = "UNDEFINED"

import numpy as np
import time
import os
import six.moves.urllib as urllib
import sys
sys.path.append("C:\\Users\\hamza\\Desktop\\TensorFlow\\models\\research\\")
sys.path.append("C:\\Users\\hamza\\Desktop\\TensorFlow\\models\\research\\object_detection\\utils")

import tarfile
import tensorflow as tf
import zipfile

from distutils.version import StrictVersion
from collections import defaultdict
from io import StringIO
from matplotlib import pyplot as plt
from PIL import Image

# This is needed since the notebook is stored in the object_detection folder.
sys.path.append("..")
from object_detection.utils import ops as utils_ops

if StrictVersion(tf.__version__) < StrictVersion('1.9.0'):
  raise ImportError('Please upgrade your TensorFlow installation to v1.9.* or later!')
  
# This is needed to display the images.
#%matplotlib inline

from object_detection.utils import label_map_util

from object_detection.utils import visualization_utils as vis_util

#MODEL_NAME = 'execute'
PATH_TO_FROZEN_GRAPH = 'execute/frozen_inference_graph.pb'
PATH_TO_LABELS = 'execute/label_map.pbtxt'

detection_graph = tf.Graph()
with detection_graph.as_default():
  od_graph_def = tf.GraphDef()
  with tf.gfile.GFile(PATH_TO_FROZEN_GRAPH, 'rb') as fid:
    serialized_graph = fid.read()
    od_graph_def.ParseFromString(serialized_graph)
    tf.import_graph_def(od_graph_def, name='')

category_index = label_map_util.create_category_index_from_labelmap(PATH_TO_LABELS, use_display_name=True)

def run_inference_for_single_image(image, graph):
    if 'detection_masks' in tensor_dict:
        # The following processing is only for single image
        detection_boxes = tf.squeeze(tensor_dict['detection_boxes'], [0])
        detection_masks = tf.squeeze(tensor_dict['detection_masks'], [0])
        # Reframe is required to translate mask from box coordinates to image coordinates and fit the image size.
        real_num_detection = tf.cast(tensor_dict['num_detections'][0], tf.int32)
        detection_boxes = tf.slice(detection_boxes, [0, 0], [real_num_detection, -1])
        detection_masks = tf.slice(detection_masks, [0, 0, 0], [real_num_detection, -1, -1])
        detection_masks_reframed = utils_ops.reframe_box_masks_to_image_masks(
            detection_masks, detection_boxes, image.shape[0], image.shape[1])
        detection_masks_reframed = tf.cast(
            tf.greater(detection_masks_reframed, 0.5), tf.uint8)
        # Follow the convention by adding back the batch dimension
        tensor_dict['detection_masks'] = tf.expand_dims(
            detection_masks_reframed, 0)
    image_tensor = tf.get_default_graph().get_tensor_by_name('image_tensor:0')

    # Run inference
    output_dict = sess.run(tensor_dict,
                            feed_dict={image_tensor: np.expand_dims(image, 0)})

    # all outputs are float32 numpy arrays, so convert types as appropriate
    output_dict['num_detections'] = int(output_dict['num_detections'][0])
    output_dict['detection_classes'] = output_dict[
        'detection_classes'][0].astype(np.uint8)
    output_dict['detection_boxes'] = output_dict['detection_boxes'][0]
    
    vertTop = output_dict['detection_boxes'][0][0]
    horiLef = output_dict['detection_boxes'][0][1]
    vertBot = output_dict['detection_boxes'][0][2]
    horiRig = output_dict['detection_boxes'][0][3]
	
    #print("Top (min 0.0): " + str(vertTop))
    #print("Bot (max 1): " + str(vertBot))
    #print("Left Bar: " + str(horiLef))
    #print("Right Bar: " + str(horiRig))
	
    global Distance
    global Direction
    global Firing
    
	# Direction checks
    if(float(horiLef) > 0.60):
        if(Direction != "LEFT"):
            Direction = "LEFT"
            print("LEFT SIDE DETECTION")
            s = Session()
            s.get("http://76.216.216.19:8070/left")
            
    elif(float(horiRig) < 0.40):
        if(Direction != "RIGHT"):
            Direction = "RIGHT"
            print("RIGHT SIDE DETECTION")
            s = Session()
            s.get("http://76.216.216.19:8070/right")
    else:
        if(Direction != "CENTER"):
            s = Session()
            s.get("http://76.216.216.19:8070/center")
            Direction = "CENTER"
    
    # Class checks
    #if(int(output_dict['detection_classes'][0]) == 1):
        #print("masked")
    #if(int(output_dict['detection_classes'][0]) == 2):
        #print("unmasked")
    
    # Distance checks
    if(float(horiRig) - float(horiLef) > 0.25):
        if(Distance != "CLOSER"):
            Distance = "CLOSER"
            print(Distance + ": " + str(float(horiRig) - float(horiLef)))
            s = Session()
            s.get("http://70.181.237.196:8080/close")
            s.get("http://108.197.149.150/close")
            if(Firing != "FIRING"):
              s.get("http://76.216.216.19:8070/shoot")
              Firing = "FIRING"
    elif(float(horiRig) - float(horiLef) > 0.16):
        if(Distance != "CLOSE"):
            Distance = "CLOSE"
            print(Distance + ": " + str(float(horiRig) - float(horiLef)))
            s = Session()
            s.get("http://70.181.237.196:8080/closer")
            s.get("http://108.197.149.150/closer")
            if(Firing == "FIRING"):
              s.get("http://76.216.216.19:8070/")
              Firing = "STOPPING"
    elif(Distance != "FAR"):
        Distance = "FAR"
        print(Distance + ": " + str(float(horiRig) - float(horiLef)))
        s = Session()
        s.get("http://70.181.237.196:8080/far")
        s.get("http://108.197.149.150/far")
        if(Firing == "FIRING"):
              s.get("http://76.216.216.19:8070/")
              Firing = "STOPPING"
    
    output_dict['detection_scores'] = output_dict['detection_scores'][0]
    if 'detection_masks' in output_dict:
        output_dict['detection_masks'] = output_dict['detection_masks'][0]
    return output_dict

import cv2
cap = cv2.VideoCapture(0)
try:
    with detection_graph.as_default():
        with tf.Session() as sess:
                # Get handles to input and output tensors
                ops = tf.get_default_graph().get_operations()
                all_tensor_names = {output.name for op in ops for output in op.outputs}
                tensor_dict = {}
                for key in [
                  'num_detections', 'detection_boxes', 'detection_scores',
                  'detection_classes', 'detection_masks'
                ]:
                    tensor_name = key + ':0'
                    if tensor_name in all_tensor_names:
                        tensor_dict[key] = tf.get_default_graph().get_tensor_by_name(
                      tensor_name)

                while True:
                    ret, image_np = cap.read()
                    # Expand dimensions since the model expects images to have shape: [1, None, None, 3]
                    image_np_expanded = np.expand_dims(image_np, axis=0)
                    # Actual detection.
                    output_dict = run_inference_for_single_image(image_np, detection_graph)
                    # Visualization of the results of a detection.
                    vis_util.visualize_boxes_and_labels_on_image_array(
                        image_np,
                        output_dict['detection_boxes'],
                        output_dict['detection_classes'],
                        output_dict['detection_scores'],
                        category_index,
                        instance_masks=output_dict.get('detection_masks'),
                        use_normalized_coordinates=True,
                        line_thickness=8)
                    cv2.imshow('object_detection', cv2.resize(image_np, (800, 600)))
                    if cv2.waitKey(25) & 0xFF == ord('q'):
                        cap.release()
                        cv2.destroyAllWindows()
                        break
except Exception as e:
    print(e)
    cap.release()
