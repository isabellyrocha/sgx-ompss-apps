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

