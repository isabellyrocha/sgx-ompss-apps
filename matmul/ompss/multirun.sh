PROGRAM=matmul-p

export IFS=";"

THREADS="1;2;4;8"
SIZES="32;16;8"
BSIZES="32;16;8"

for size in $SIZES; do
  for thread in $THREADS; do
    echo "$size,$thread"
    NX_GPUS=0 NX_SMP_WORKERS=$thread ./$PROGRAM $size 8
  done
done
