#!/bin/bash

PROGRAM=app
default_size=64
default_block=16
default_threads=1
default_scheduler="bf"

#sizes=[1024, 512, 16]
#blocks=[1024, 512 , 16]
#threads=[1, 2, 4, 8]
#schedulers=["bf", "wf"]

#make

for iteration in {1..10};
do
  for size in 64 32 16
  do
    echo "sgx-encrypted,size,$iteration,$size,$default_block,$default_threads,$default_scheduler,"
    NX_SMP_WORKERS=$default_threads NX_ARGS="--schedule=$default_scheduler" ./$PROGRAM $size $default_block
    sleep 1s
  done

  for block in 64 32 16
  do
    echo "sgx-encrypted,block,$iteration,$default_size,$block,$default_threads,$default_scheduler,"
    NX_SMP_WORKERS=$default_threads NX_ARGS="--schedule=$default_scheduler" ./$PROGRAM $default_size $block
    sleep 1s
  done

  for threads in 1 2 4 8
  do
    echo "sgx-encrypted,threads,$iteration,$default_size,$default_block,$threads,$default_scheduler,"
    NX_SMP_WORKERS=$threads NX_ARGS="--schedule=$default_scheduler" ./$PROGRAM $default_size $default_block
    sleep 1s
  done

  for scheduler in "bf" "wf"
  do
    echo "sgx-encrypted,scheduler,$iteration,$default_size,$default_block,$default_threads,$scheduler,"
    NX_SMP_WORKERS=$default_threads NX_ARGS="--schedule=$scheduler" ./$PROGRAM $default_size $default_block
    sleep 1s
  done
done
make clean
