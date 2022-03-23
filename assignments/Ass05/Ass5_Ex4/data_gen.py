import os
import random
import numpy as np
import shutil as st

minNum = 33
maxNum = 126
minLen = 0
maxLen = 100
failString = "The pattern list does not appear in the target list."


def data_gen(dataFileName, numTestPt):
    numGeneralTestPt = int(numTestPt / 2)
    numOverlappedTestPt = 0
    numFailTestPt = numTestPt - numGeneralTestPt - numOverlappedTestPt

    # make a special test point where input list is empty; this is the last case
    for idTestPt in range(numGeneralTestPt):
        stringLen = random.randint(2, int((maxLen-minLen)/10)+1)
        charMatched = []
        overlappedTimes = random.randint(1, 10)
        for i in range(stringLen):  # 6 is the magic number
            charMatched.append(chr(random.randint(minNum, maxNum-40)))
        charInput = []
        for i in range(overlappedTimes):
            for j in range(stringLen):
                charchangenum = random.randint(1, int(len(charMatched)/2))
                charInput.extend(charMatched[:-charchangenum])
                for k in range(charchangenum):
                    charInput.append(chr(random.randint(maxNum-39, maxNum)))
        charInput.extend(charMatched)
        startIndex=len(charInput)-len(charMatched)
                

        inputFile = open("data/" + dataFileName + ".in" + str(idTestPt), "w")
        inputFile.writelines(charInput)
        inputFile.write("\n")
        inputFile.writelines(charMatched)
        inputFile.close()
        ansFile = open("data/" + dataFileName + ".ans" + str(idTestPt), "w")
        ansFile.write(str(startIndex))
        ansFile.close()

    for fake_idTestPt in range(numFailTestPt):
        idTestPt = fake_idTestPt + numGeneralTestPt
        stringLen = random.randint(minLen, maxLen)
        charInput = []
        for i in range(stringLen):
            charInput.append(chr(random.randint(minNum, maxNum - 40)))

        print(charInput)
        mismatchInput = []
        for i in range(random.randint(1, stringLen)):
            mismatchInput.append(chr(random.randint(maxNum - 39, maxNum)))

        inputFile = open("data/" + dataFileName + ".in" + str(idTestPt), "w")
        inputFile.writelines(charInput)
        inputFile.write("\n")
        inputFile.writelines(mismatchInput)
        inputFile.close()
        ansFile = open("data/" + dataFileName + ".ans" + str(idTestPt), "w")
        ansFile.write(failString)
        ansFile.close()


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
