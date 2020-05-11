#!/bin/bash

# XML TO CSV:

python xml_to_csv.py -i ../../images/train -o ../../annotations/train_labels.csv

python xml_to_csv.py -i ../../images/test -o ../../annotations/test_labels.csv

# CSV TO TF: 

python generate_tfrecord.py --csv_input=../../annotations/train_labels.csv --img_path=../../images/train  --output_path=../../annotations/train.record

python generate_tfrecord.py --csv_input=../../annotations/test_labels.csv --img_path=../../images/test  --output_path=../../annotations/test.record
