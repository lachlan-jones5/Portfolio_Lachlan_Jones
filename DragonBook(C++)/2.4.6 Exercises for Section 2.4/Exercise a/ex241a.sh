#!/bin/bash

counter=1
while [ $counter -le 7 ]
do
  filename="test_files/${counter}_correct.txt"
  cat $filename
  ./ex241a $filename
  filename="test_files/${counter}_incorrect.txt"
  cat $filename
  ./ex241a $filename
  ((counter++))
done
