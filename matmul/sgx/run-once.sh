PROGRAM=app

export NX_SMP_WORKERS=4

make
./$PROGRAM 16 128
make clean
