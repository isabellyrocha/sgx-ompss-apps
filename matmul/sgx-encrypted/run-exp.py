import subprocess

sizes = ["32", "16", "8"]
threads = ["1", "2", "4", "8"]
schedulers = ["bf", "wf", "versioning"]

def get_size(size):
    if size == "32":
        return "large"
    elif size == "16":
        return "medium"
    return "small"

for i in range(10):
    for size in sizes:
        command = "NX_SMP_WORKERS=1 ./app %s 32" % size
        print(command)
        output,error  = subprocess.Popen(
                    command, universal_newlines=True, shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        print(error)
        print("graph,%s,%s" % (get_size(size), output))

    for size in sizes:
        command = "NX_SMP_WORKERS=1 ./app 32 %s" % size
        output,error  = subprocess.Popen(
                    command, universal_newlines=True, shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        print("input,%s,%s" % (get_size(size), output))

    for thread in threads:
        command = "NX_SMP_WORKERS=%s ./app 32 32" % thread
        output,error  = subprocess.Popen(
                    command, universal_newlines=True, shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        print("thread,%s,%s" % (get_size(size), output))

    for scheduler in schedulers:
        command = "NX_SMP_WORKERS=1 NX_ARGS=\"--schedule=%s\" ./app 32 32" % scheduler
        output,error  = subprocess.Popen(
                    command, universal_newlines=True, shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE).communicate()
        print("scheduler,%s,%s" % (scheduler, output))
