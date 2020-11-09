# Secure Task based programming with OmpSs and SGX

This repository consists of OmpSs applications integrated with SGX to extend the task parallelism and hardware heterogeneity characteristics already supported by OmpSs to include security. The overall application flow is depicted below.

![alt text](https://raw.githubusercontent.com/isabellyrocha/ompss-sgx-apps/master/figures/ompss_sgx_app.png)

------------------------------------
Experimental results
------------------------------------

Below are the results of experiments performed on a E3-1275 CPU with 8 cores and Intel SGX SDK version 2.8. Solid and dashed bars correspond to runtime and energy, respectively.

![alt text](https://raw.githubusercontent.com/isabellyrocha/ompss-sgx-apps/master/figures/threads.png)
![alt text](https://raw.githubusercontent.com/isabellyrocha/ompss-sgx-apps/master/figures/schedule.png)
![alt text](https://raw.githubusercontent.com/isabellyrocha/ompss-sgx-apps/master/figures/input.png)
![alt text](https://raw.githubusercontent.com/isabellyrocha/ompss-sgx-apps/master/figures/graph.png)

------------------------------------
# Reproduce results
------------------------------------

## Environment Setup

- Dependecies
```
$ sudo apt install automake autoconf libtool pkg-config make
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install -y hwloc
$ sudo apt-get install -y numactl
$ sudo apt-get install build-essential
$ sudo apt install bison
$ sudo apt-get install flex
$ sudo apt-get install gperf
$ sudo apt-get install libsqlite3-dev
```

- Install OmpSs
```
$ wget https://pm.bsc.es/ftp/ompss/releases/ompss-19.06.tar.gz
$ tar -xfzv ompss-19.06.tar.gz
$ cd ompss-19.06/
```

- Install Nanos
```
$ cd nanox-0.15/
$ ./configure --prefix=/home/ubuntu/ompss-19.06/nanox-0.15/
$ make
$ make install
```

- Install Mercurium 
```
$ cd mcxx-2.3.0/
$ autoreconf -fiv
$ ./configure --prefix=/home/ubuntu/ompss-19.06/mcxx-2.3.0/ --enable-ompss --with-nanox=/home/ubuntu/ompss-19.06/nanox-0.15
$ make
$ make install
```

- Setup path
```
$ export PATH=/home/ubuntu/ompss-19.06/mcxx-2.3.0/bin:$PATH
```

- Install SGX: https://github.com/intel/linux-sgx

