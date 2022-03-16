# This file only works on Windows, the commands are capable for Windows Command Shell (cmd.exe)

import imp
import os
from data_gen import data_gen
from compare import cmp

dataFileName = "heap"
progName = "heap_test"
numTestPt = 10
normalExit = 0

# compileCommandStr = "g++ " + dataFileName + ".cpp -g -o " + progName
compileCommandStr = "mingw32-make"


def RuntimeError(errorCode):    # Runtime Error at Testpoint #i
    resultFile = open(dataFileName + ".result", "w")
    resultFile.write("Runtime Error with code " + str(errorCode))


def main():
    print("Copyright 2022 Zhong Tiantian (tiantianz.20@intl.zju.edu.cn)")
    print("This is an autotest script for " + progName + ".\n")
    print("To have it function normally, you will have this file along with compare.py, data_gen.py.\n")
    print("NOTE: This script only works for Windows, as it relies on Windows Command Shell commands.\n")
    print("Compiling...")
    os.system(compileCommandStr)
    print("Done Compiling. Start testing...")
    try:
        os.remove("user_output")
    except:
        print("No user_output folder found. Continuing...")
    
    try:
        os.remove("result")
    except:
        print("No result folder found. Continuing...")

    os.makedirs("result", exist_ok=True)
    os.makedirs("user_output", exist_ok=True)
    
    if not os.path.exists("data"):
        print("No input data found. Generating new data set.")
        data_gen()

    for i in range(numTestPt):
        copyCommandStr = "copy data\\" + dataFileName + \
            ".in" + str(i) + " " + dataFileName + ".in"
        stdAnsCommandStr = "copy data\\" + dataFileName + \
            ".ans" + str(i) + " " + dataFileName + ".ans"
        execCommandStr = progName
        copyUserOutputStr = "move " + dataFileName + \
            ".out user_output\\" + dataFileName + ".out" + str(i)
        renameCmpResultCommandStr = "move " + dataFileName + \
            ".result result\\" + dataFileName + ".result" + str(i)
        cleanInCommandStr = "del " + dataFileName + ".in"
        cleanAnsCommandStr = "del " + dataFileName + ".ans"

        os.system(copyCommandStr)
        os.system(stdAnsCommandStr)
        exitCode = os.system(execCommandStr)
        if (exitCode != normalExit):
            RuntimeError(exitCode)
        else:
            cmp()
        os.system(renameCmpResultCommandStr)
        os.system(copyUserOutputStr)
        os.system(cleanInCommandStr)
        os.system(cleanAnsCommandStr)

    os.system("del *.exe")
    os.system("del *.o")

    # Generate an overview of the testpoints result
    print("Generating result overview.")
    os.system("del result_overview.txt")
    overviewFile = open("result_overview.txt", "w")
    overviewFile.write("Program Name = " + progName + "\n")
    overviewFile.write("Number of Test Points = " + str(numTestPt) + "\n")
    overviewFile.write("Testpoints Details:\n")
    for i in range(numTestPt):
        resFile = open("result/" + dataFileName + ".result" + str(i), "r")
        if resFile.readline() == "******Passed******":
            overviewFile.write("#" + str(i) + ": Passed\n")
        else:
            overviewFile.write("#" + str(i) + ": FAILED\n")
        resFile.close()
    overviewFile.close()
    print("Result overview is written in result_overview.txt")


if __name__ == "__main__":
    main()
