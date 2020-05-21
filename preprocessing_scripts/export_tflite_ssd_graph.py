# Copyright 2018 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================
import tensorflow as tf
from google.protobuf import text_format
from object_detection import export_tflite_ssd_graph_lib
from object_detection.protos import pipeline_pb2

flags = tf.app.flags
flags.DEFINE_string('output_directory', None, 'Path to write outputs.')
flags.DEFINE_string(
    'pipeline_config_path', None,
    'Path to a pipeline_pb2.TrainEvalPipelineConfig config '
    'file.')
flags.DEFINE_string('trained_checkpoint_prefix', None, 'Checkpoint prefix.')
flags.DEFINE_integer('max_detections', 10,
                     'Maximum number of detections (boxes) to show.')
flags.DEFINE_integer('max_classes_per_detection', 1,
                     'Number of classes to display per detection box.')
flags.DEFINE_integer(
    'detections_per_class', 100,
    'Number of anchors used per class in Regular Non-Max-Suppression.')
flags.DEFINE_bool('add_postprocessing_op', True,
                  'Add TFLite custom op for postprocessing to the graph.')
flags.DEFINE_bool(
    'use_regular_nms', False,
    'Flag to set postprocessing op to use Regular NMS instead of Fast NMS.')
flags.DEFINE_string(
    'config_override', '', 'pipeline_pb2.TrainEvalPipelineConfig '
    'text proto to override pipeline_config_path.')

FLAGS = flags.FLAGS


def main(argv):
  del argv  # Unused.
  flags.mark_flag_as_required('output_directory')
  flags.mark_flag_as_required('pipeline_config_path')
  flags.mark_flag_as_required('trained_checkpoint_prefix')

  pipeline_config = pipeline_pb2.TrainEvalPipelineConfig()

  with tf.gfile.GFile(FLAGS.pipeline_config_path, 'r') as f:
    text_format.Merge(f.read(), pipeline_config)
  text_format.Merge(FLAGS.config_override, pipeline_config)
  export_tflite_ssd_graph_lib.export_tflite_graph(
      pipeline_config, FLAGS.trained_checkpoint_prefix, FLAGS.output_directory,
      FLAGS.add_postprocessing_op, FLAGS.max_detections,
      FLAGS.max_classes_per_detection, FLAGS.use_regular_nms)


if __name__ == '__main__':
  tf.app.run(main)
