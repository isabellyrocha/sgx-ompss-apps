import subprocess

#sizes = ["4", "8","16", "32", "64", "128", "256", "512", "1024"]
sizes = ["1", "2", "3", "4", "5"]
threads = ["1", "2", "4", "8"]
schedulers = ["bf", "wf", "versioning"]

def get_size(size):
    if size == "32":
        return "large"
    elif size == "16":
        return "medium"
    return "small"

for i in range(2):
#    for size in sizes:
#        command = "NX_SMP_WORKERS=1 ./dot-product-p %s 128" % size
#        output,error  = subprocess.Popen(
#                    command, universal_newlines=True, shell=True,
#                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
#        print("graph,%s,%s" % (size, output))

#    for size in sizes:
#        command = "NX_SMP_WORKERS=1 ./dot-product-p 1 %s" % size
#        output,error  = subprocess.Popen(
#                    command, universal_newlines=True, shell=True,
#                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
#        print("input,%s,%s" % (size, output))

#    for thread in threads:
#        command = "NX_SMP_WORKERS=%s ./dot-product-p 1 128" % thread
#        output,error  = subprocess.Popen(
#                    command, universal_newlines=True, shell=True,
#                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
#        print("thread,%s,%s" % (thread, output))

    for scheduler in schedulers:
        command = "NX_SMP_WORKERS=1 NX_ARGS=\"--schedule=%s\" ./dot-product-p 1 128" % scheduler
        output,error  = subprocess.Popen(
                    command, universal_newlines=True, shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        print("scheduler,%s,%s" % (scheduler, output))
