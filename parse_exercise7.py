import re
import json
import matplotlib.pyplot as plt
from pandas import DataFrame

def getData(string: str) -> tuple:
    matches = re.findall(r'[-+]?\d*\.\d+|\d+', string)
    return matches[0], matches[1], matches[2], float(matches[3]), float(matches[4])

if __name__ == "__main__":


    file = open("./bucleExterior.txt",'r')
    data = []

    for x in file:
        data.append(getData(x))

    df = DataFrame(data, columns=['Threads','DataVolume','N','Time','MFlops'])

    test = df.groupby(['Threads','DataVolume'])

    threads1 = []
    threads2 = []
    threads4 = []
    threads8 = []
    for key, _ in test:
        x = test.get_group(key)['MFlops'].mean()
        if key[0] == '1':
            threads1.append((key[1], x))
        if key[0] == '2':
            threads2.append((key[1], x))
        if key[0] == '4':
            threads4.append((key[1], x))
        if key[0] == '8':
            threads8.append((key[1], x))
        
    plt.plot(*zip(*threads1))
    plt.xlabel("Volumen de datos (MB)")
    plt.ylabel("Rendimiento (MFlops)")
    plt.title("Cantidad de hilos: %s" % key)
    plt.show()
    

    # plt.plot(*zip(*threads2))
    # plt.show()

    # plt.plot(*zip(*threads4))
    # plt.show()

    # plt.plot(*zip(*threads8))
    # plt.show()
   