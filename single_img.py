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
  od_graph_def = tf.compat.v1.GraphDef()
  with tf.io.gfile.GFile(PATH_TO_FROZEN_GRAPH, 'rb') as fid:
    serialized_graph = fid.read()
    od_graph_def.ParseFromString(serialized_graph)
    tf.import_graph_def(od_graph_def, name='')

category_index = label_map_util.create_category_index_from_labelmap(PATH_TO_LABELS, use_display_name=True)

imageName = 'error.jpg'

def run_inference_for_single_image1(image, graph):
    with graph.as_default():
        with tf.Session() as sess:
            # Get handles to input and output tensors
            ops = tf.get_default_graph().get_operations()
            all_tensor_names = {output.name for op in ops for output in op.outputs}
            tensor_dict = {}
            for key in ['num_detections', 'detection_boxes', 'detection_scores','detection_classes', 'detection_masks']:
                tensor_name = key + ':0'
                if tensor_name in all_tensor_names:
                    tensor_dict[key] = tf.get_default_graph().get_tensor_by_name(tensor_name)
                #END if tensor_name in
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
                    tensor_dict['detection_masks'] = tf.expand_dims(detection_masks_reframed, 0)
                #END IF DETECTION MASKS
            
            #END FOR KEY LOOP
                
            image_tensor = tf.get_default_graph().get_tensor_by_name('image_tensor:0')
            # Run inference
            output_dict = sess.run(tensor_dict,
                                 feed_dict={image_tensor: np.expand_dims(image, 0)})
            # all outputs are float32 numpy arrays, so convert types as appropriate
            output_dict['num_detections'] = int(output_dict['num_detections'][0])
            output_dict['detection_classes'] = output_dict[
              'detection_classes'][0].astype(np.uint8)
            output_dict['detection_boxes'] = output_dict['detection_boxes'][0]
            output_dict['detection_scores'] = output_dict['detection_scores'][0]
            if 'detection_masks' in output_dict:
                output_dict['detection_masks'] = output_dict['detection_masks'][0]
    return output_dict

def Run_Object_Detection_On_Images(image_path):
    IMAGE_SIZE = (12, 8)
    imageName = image_path.split('/', 8)[8]
    print("============== TESTING: " + imageName + " ==============")
    image = Image.open(image_path)
    # the array based representation of the image will be used later in order to prepare the
    # result image with boxes and labels on it.
    image_np = load_image_into_numpy_array(image)
    # Expand dimensions since the model expects images to have shape: [1, None, None, 3]
    image_np_expanded = np.expand_dims(image_np, axis=0)
    # Actual detection.
    output_dict = run_inference_for_single_image1(image_np, detection_graph)
    # Visualization of the results of a detection.
    vis_util.visualize_boxes_and_labels_on_image_array(
      image_np,
      output_dict['detection_boxes'],
      output_dict['detection_classes'],
      output_dict['detection_scores'],
      category_index,
      instance_masks=output_dict.get('detection_masks'),
      use_normalized_coordinates=True,
      line_thickness=5)
    plt.figure(figsize=IMAGE_SIZE)
    plt.imshow(image_np)
    
    if(imageName.split('.')[0] == "masked"):
        assert str(output_dict['detection_classes'][0]) == "1"
    elif(imageName.split('.')[0] == "unmasked"):
        assert str(output_dict['detection_classes'][0]) == "2"
    
    print("Class: " + str(output_dict['detection_classes'][0]))
    print("Top: " + str(output_dict['detection_boxes'][0][0]))
    print("Left: " + str(output_dict['detection_boxes'][0][1]))
    print("Bot: " + str(output_dict['detection_boxes'][0][2]))
    print("Right: " + str(output_dict['detection_boxes'][0][3]))
    print("Successful detection of " + imageName.split('.')[0] + " image!\n\n")

def load_image_into_numpy_array(image):
    (im_width, im_height) = image.size
    return np.array(image.getdata()).reshape((im_height, im_width, 3)).astype(np.uint8)

from os import listdir
from os.path import isfile, join

system_path = "./single_img_tests/"
image_path = system_path + sys.argv[1]
#image_path = system_path + input("Enter the name of the image you wish to test: ")

print("\n")

Run_Object_Detection_On_Images(image_path)

exit()
