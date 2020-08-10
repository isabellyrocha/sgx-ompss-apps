PROGRAM=dot-product-p

export IFS=";"

THREADS="1;2;4;8"
MSIZE="32;512"
BSIZE="128;512"

for MS in $MSIZE; do
  for BS in $BSIZE; do
    for thread in $THREADS; do
      echo "$thread,$MS,$BS"
      NX_GPUS=0 NX_SMP_WORKERS=$thread NX_ARGS="--summary" ./$PROGRAM $MS $BS
    done
  done
done
