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
$ source /home/ubuntu/linux-sgx/linux/installer/bin/sgxsdk/environment
```

- Installing SGX driver
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

- Installing SGX PSW:
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

- Test Sample Code
```
$ cd SampleCode/LocalAttestation
$ make
$ ./app
```
