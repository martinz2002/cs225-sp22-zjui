import os
import random
import numpy as np
import shutil as st

minNum = -10000
maxNum = 10000
minLen = 0
maxLen = 1000


def data_gen(dataFileName, numTestPt):

    # make a special test point where input list is empty; this is the last case
    fileIn = open("data/"+dataFileName+".in" +
                  str(numTestPt - 1), "w")  # input file
    fileOut = open("data/"+dataFileName+".ans" + str(numTestPt - 1), "w")
    fileIn.write("\n")
    fileOut.write("EMPTY HEAP\n")
    fileIn.close()
    fileOut.close()

    for idTestPt in range(numTestPt - 1):
        data = np.random.randint(
            minNum, maxNum, random.randint(minLen, maxLen))
        np.savetxt("data/"+dataFileName+".in" + str(idTestPt), data, fmt="%d")

        data.sort()
        data = data.tolist()
        data.append(data[-1])
        data = data[::-1]
        data = np.array(data)

        np.savetxt("data/"+dataFileName+".ans" + str(idTestPt), data, fmt="%d")


def gen():
    try:
        numTestPt = int(input("Input the number of testpoints to generate: "))
    except:
        print("Invalid input. Exiting.")
        exit(-1)

    dataFileName = input("Enter the base name of input files: ")
    if dataFileName == "" or dataFileName == "\n":
        print("Invalid input. Exiting.")
        exit(-2)
    progExecName = input(
        "Enter the base name of the program (executable) file: ")
    if dataFileName == "" or dataFileName == "\n":
        print("Invalid input. Exiting.")
        exit(-2)

    if os.path.exists("data"):
        st.rmtree("data")

    os.mkdir("data")
    configFile = open("data/config", "w")
    configFile.writelines(
        [progExecName, "\n", dataFileName, "\n", str(numTestPt), "\n"])
    configFile.close()

    data_gen(dataFileName, numTestPt)


if __name__ == "__main__":
    gen()
