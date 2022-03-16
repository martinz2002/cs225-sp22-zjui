from audioop import reverse
import os
import random
import numpy as np
import shutil as st

minNum = -10000
maxNum = 10000
minLen = 0
maxLen = 1000
numTestPt = 10


def data_gen():

    if os.path.exists("data"):
        st.rmtree("data")
    os.mkdir("data")

    # make a special test point where input list is empty
    fileIn = open("data/heap.in" + str(9), "w")  # input file
    fileOut = open("data/heap.ans" + str(9), "w")
    fileIn.write("\n")
    fileOut.write("EMPTY HEAP\n")
    fileIn.close()
    fileOut.close()

    for idTestPt in range(numTestPt - 1):
        data = np.random.randint(
            minNum, maxNum, random.randint(minLen, maxLen))
        np.savetxt("data/heap.in" + str(idTestPt), data, fmt="%d")

        data.sort()
        data = data.tolist()
        data.append(data[-1])
        data = data[::-1]

        data = np.array(data)

        np.savetxt("data/heap.ans" + str(idTestPt), data, fmt="%d")



if __name__ == "__main__":
    data_gen()
