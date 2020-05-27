#!/bin/bash

# Launch training:(Note: --model_dir=training/ the virtual directory can be changed in order to view multiple training graphs on TensorBoard

python model_main.py --alsologtostderr --model_dir=training/ --pipeline_config_path=training/ssd_inception_v2_coco.config

# Launch training graph for training in progress: (Note: --logdir=training\ virtual directory depends on what was used for training)

tensorboard --logdir=training\