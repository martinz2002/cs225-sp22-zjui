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
    numGeneralTestPt = int(numTestPt / 3)
    numOverlappedTestPt = int(numGeneralTestPt / 3)
    numFailTestPt = numTestPt - numGeneralTestPt - numOverlappedTestPt

    # make a special test point where input list is empty; this is the last case
    for idTestPt in range(numGeneralTestPt):
        stringLen = random.randint(minLen, maxLen)
        charMatched = []
        overlappedTimes = random.randint(1, 10)
        for i in range(int(stringLen / overlappedTimes)): # 6 is the magic number
            charMatched.append(chr(random.randint(minNum, maxNum)))
        
        charInput = []

        for i in range(overlappedTimes):
            for j in charMatched:
                charInput.append(j)
        
        

        inputFile = open("data/" + dataFileName + ".in" + str(idTestPt), "w")
        inputFile.writelines(charInput)
        inputFile.write("\n")
        inputFile.writelines(charMatched)
        inputFile.close()
        ansFile = open("data/" + dataFileName + ".ans" + str(idTestPt), "w")
        ansFile.write(str(startIndex))
        ansFile.close()

    for fake_idTestPt in range(numFailTestPt):
        idTestPt = fake_idTestPt + numGeneralTestPt + numOverlappedTestPt
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
