# Secure Task based programming with OmpSs and SGX

This repository consists of OmpSs applications integrated with SGX to extend the task parallelism and hardware heterogeneity characteristics already supported by OmpSs to include security. The overall application flow is depicted below.

![alt text](https://raw.githubusercontent.com/isabellyrocha/ompss-sgx-apps/master/figures/ompss_sgx_app.png)

------------------------------------
# Environment Setup
------------------------------------

## Install Dependecies
```
$ sudo apt install gcc-7 g++-7 gfortran-7
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

## Install OmpSs
```
$ wget https://pm.bsc.es/ftp/ompss/releases/ompss-19.06.tar.gz
$ tar -xfzv ompss-19.06.tar.gz
$ cd ompss-19.06/
```

## Install Nanos
```
$ cd nanox-0.15/
$ ./configure --prefix=/home/ubuntu/ompss-19.06/nanox-0.15/
$ make
$ make install
```

## Install Mercurium 
```
$ cd mcxx-2.3.0/
$ autoreconf -fiv
$ ./configure --prefix=/home/ubuntu/ompss-19.06/mcxx-2.3.0/ --enable-ompss --with-nanox=/home/ubuntu/ompss-19.06/nanox-0.15
$ make
$ make install
```

## Install MKL
```
$ wget http://registrationcenter-download.intel.com/akdlm/irc_nas/tec/12147/l_mkl_2017.4.239.tgz
$ tar xzvf l_mkl_2017.4.239.tgz
$ cd l_mkl_2017.4.239
$ sudo ./install_GUI.sh
$ printf '/opt/intel/lib/intel64\n/opt/intel/mkl/lib/intel64\n' | sudo tee -a /etc/ld.so.conf.d/intel_mkl.conf
$ sudo ldconfig
```

## Install OpenBLAS
```
$ wget https://github.com/xianyi/OpenBLAS/archive/v0.3.10.tar.gz
$ tar -xzf v0.3.10.tar.gz
$ cd OpenBLAS-0.3.10
$ FC=gfortran-7 CC=gcc-7 CXX=g++-7 MAX_STACK_ALLOC=16777216 NO_SHARED=1 USE_TLS=1 USE_LOCKING=0 USE_OPENMP=0 USE_THREAD=0 NO_PARALLEL_MAKE=1 make PREFIX=$HOME/OpenBLAS-0.3.10 install
```

## Install SGX 

- SGX driver
```
$ git clone https://github.com/intel/linux-sgx-driver.git
//Check if matching Kernel headers are installed: 
$ dpkg-query -s linux-headers-$(uname -r) //Check if matching Kernel headers are installed: 
$ sudo apt-get install linux-headers-$(uname -r) //If not run this command
$ sudo apt install make gcc // build
$ cd linux-sgx-driver
$ make
$ sudo mkdir -p "/lib/modules/"`uname -r`"/kernel/drivers/intel/sgx"    
$ sudo cp isgx.ko "/lib/modules/"`uname -r`"/kernel/drivers/intel/sgx"    
$ sudo sh -c "cat /etc/modules | grep -Fxq isgx || echo isgx >> /etc/modules"    
$ sudo /sbin/depmod
$ sudo /sbin/modprobe isgx
```

- SGX PSW
```
$ sudo apt-get install libssl-dev libcurl4-openssl-dev protobuf-compiler libprotobuf-dev
$ git clone https://github.com/intel/linux-sgx.git
$ ./download_prebuilt.sh
$ make
$ make sdk_install_pkg
$ make psw_install_pkg
$ cd linux/installer/bin
$ ./sgx_linux_x64_sdk_${version}.bin
$ sudo apt-get install libssl-dev libcurl4-openssl-dev libprotobuf-dev
$ sudo ./sgx_linux_x64_psw_${version}.bin
```

Test Sample Code
```
$ cd SampleCode/LocalAttestation
$ make
$ ./app
```

## Setup path for OmpSs and SGX
```
$ export PATH=/home/ubuntu/ompss-19.06/mcxx-2.3.0/bin:$PATH
$ source /home/ubuntu/linux-sgx/linux/installer/bin/sgxsdk/environment
```

## Install InfluxDB 
> We use InfluxDB for storage of the energy measurements.
Therefore, if you're not insterested in energy this step can be skipped.

- Install and setup database
```Shell
$ sudo apt install influxdb
$ service influxdb start
$ influx
$ CREATE DATABASE energy
```

- Initiate power metrics collection
```Shell
$ nohup python3 $HOME/ompss-sgx-apps/monitoring/pdu_power.py <http://pdu-address> 1 &
```
