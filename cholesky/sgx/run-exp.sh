#!/bin/bash

PROGRAM=app
default_size=2048
default_block=256
default_threads=1
default_scheduler="bf"

#sizes=[1024, 512, 16]
#blocks=[1024, 512 , 16]
#threads=[1, 2, 4, 8]
#schedulers=["bf", "wf"]

#make

for iteration in {1..10};
do
  for size in 2048 1024 256
  do
    echo "sgx,size,$iteration,$size,$default_block,$default_threads,$default_scheduler,"
    NX_SMP_WORKERS=$default_threads NX_ARGS="--schedule=$default_scheduler" ./$PROGRAM $size $default_block 1
    sleep 1s
  done

  for block in 2048 1024 256
  do
    echo "sgx,block,$iteration,$default_size,$block,$default_threads,$default_scheduler,"
    NX_SMP_WORKERS=$default_threads NX_ARGS="--schedule=$default_scheduler" ./$PROGRAM $default_size $block 1
    sleep 1s
  done

  for threads in 1 2 4 8
  do
    echo "sgx,threads,$iteration,$default_size,$default_block,$threads,$default_scheduler,"
    NX_SMP_WORKERS=$threads NX_ARGS="--schedule=$default_scheduler" ./$PROGRAM $default_size $default_block 1
    sleep 1s
  done

  for scheduler in "bf" "wf"
  do
    echo "sgx,scheduler,$iteration,$default_size,$default_block,$default_threads,$scheduler,"
    NX_SMP_WORKERS=$default_threads NX_ARGS="--schedule=$scheduler" ./$PROGRAM $default_size $default_block 1
    sleep 1s
  done
done
make clean
