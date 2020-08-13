import numpy as np

def file_to_map(file_name):
    result = {}
    with open(file_name) as f:
        line = f.readline().strip()
        while line:
            (key, value, start, end, duration, energy) = line.split(",")
            if key not in result.keys():
                result[key] = {}
            if value not in result[key].keys():
                result[key][value] = {'duration': [], 'energy': []}
            if float(duration) > 0:
                result[key][value]['duration'].append(float(duration))
            if float(energy) > 0:
                result[key][value]['energy'].append(float(energy))
            line = f.readline().strip()
    return result

ompss = file_to_map("ompss/exp.out")
sgx = file_to_map("sgx/exp.out")

for key in ompss.keys():
    for value in ompss[key].keys():
#        print(ompss[key][value]['energy'])
        energy = (np.mean(sgx[key][value]['energy']) - np.mean(ompss[key][value]['energy']))/np.mean(ompss[key][value]['energy'])
        duration =  (np.mean(sgx[key][value]['duration']) - np.mean(ompss[key][value]['duration']))/np.mean(ompss[key][value]['duration'])
        print("%s,%s,%f,%f" % (key, value, duration, energy))
