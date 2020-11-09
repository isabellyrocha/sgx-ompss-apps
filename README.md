#     Secure Task based programming with OmpSs and SGX

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
Reproduce results
------------------------------------

## Environment Setup

- Dependecies
```
$ sudo apt install automake autoconf libtool pkg-config make
$ sudo apt-get install libboost-all-dev
$ sudo apt-get install -y hwloc
$ sudo apt-get install -y numactl
$ sudo apt-get install build-essential
$ # Install GNU bison 2.3
$ wget http://ftp.gnu.org/gnu/bison/bison-2.3.tar.gz
$ tar -xvzf bison-2.3.tar.gz
$ cd bison-2.3
$ PATH=$PATH:/usr/local/m4/bin/
$ ./configure --prefix=/usr/local/bison --with-libiconv-prefix=/usr/local/libiconv/
$ make
$ sudo make install
$ # Install GNU flex 2.5.4
$ sudo apt-get install flex
$ sudo apt-get install gperf
$ sudo apt-get install libsqlite3-dev
```

- Install Mercurium 
```
$ git clone https://github.com/bsc-pm/mcxx.git
$ cd mcxx
$ autoreconf -fiv
$ export MERCURIUM=/home/ubuntu/mcxx
$ ./configure --prefix=$MERCURIUM --enable-nanos6-bootstrap
```

- Install Nanos
```
$ git clone https://github.com/bsc-pm/nanos6.git
$ cd nanos6
$ autoreconf -f -i -v
$ ./configure --prefix=/home/ubuntu/nanos6
$ make all check
$ make install
```
