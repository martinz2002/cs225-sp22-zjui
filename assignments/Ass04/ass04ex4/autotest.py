# This file only works on Windows, the commands are capable for Windows Command Shell (cmd.exe)

import goto
import sys
import os
from data_gen import data_gen
from compare import cmp

dataFileName = "heap"
progName = "heap_test"
numTestPt = 10
normalExit = 0

# compileCommandStr = "g++ " + dataFileName + ".cpp -g -o " + progName
compileCommandStr = "mingw32-make"


def RuntimeError(exitCode):    # Runtime Error at Testpoint #i
    resultFile = open(dataFileName + ".result", "w")
    resultFile.write("Runtime Error " + str(exitCode))

def WriteOverview(isCE):
    # Generate an overview of the testpoints result
    print("Generating result overview.")
    os.system("del result_overview.txt")
    overviewFile = open("result_overview.txt", "w")
    overviewFile.write("Program Name = " + progName + "\n")
    overviewFile.write("Number of Test Points = " + str(numTestPt) + "\n")
    overviewFile.write("Testpoints Details:\n")
    if isCE:
        overviewFile.write("Compile Error.")
        exit()
    for i in range(numTestPt):
        resFile = open("result/" + dataFileName + ".result" + str(i), "r")
        resFileFirstLine = resFile.readline().split("\n")[0]
        if resFileFirstLine == "******Passed******":
            overviewFile.write("#" + str(i) + ": AC\n")
        elif resFileFirstLine == "------Testpoint failed. Detailed information:------":
            overviewFile.write("#" + str(i) + ": WA\n")
        elif resFileFirstLine[0:12] == "Runtime Error":
            overviewFile.write("RE")
        resFile.close()
    overviewFile.close()
    print("Result overview is written in ""result_overview.txt"".")

def main():
    print("This is an autotest script for " + progName + ".\n")
    print("To have it function normally, you will have this file along with compare.py, data_gen.py.\n")
    print("Compiling...")
    isCE = False
    if os.system(compileCommandStr) != 0:
        isCE = True

    print("Done Compiling. Start testing...")
    try:
        os.remove("user_output")
    except:
        print("No previous user_output folder found. Continuing...")
    
    try:
        os.remove("result")
    except:
        print("No previous result folder found. Continuing...")

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

    WriteOverview(isCE)

    os.system("del *.exe")
    os.system("del *.o")




if __name__ == "__main__":
    print("Copyright (C) 2022 Zhong Tiantian, Zhejiang University")
    if sys.platform != "win32":
        print("This script is not supported on " + sys.platform() + ".")
    else:
        main()
