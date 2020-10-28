
for directory in ["ompss", "sgx", "sgx-encrypted"]:
    with open("%s/exp.out" % directory) as f:
        line = f.readline()
        while line:
            if "Checksum" not in line:
                second = f.readline()
                while "Checksum" in second:
                    second = f.readline()
                print("%s%s" %(line.rstrip(), second.rstrip()))
            line = f.readline()
