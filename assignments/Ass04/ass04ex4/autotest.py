# This file only works on Windows, the commands are capable for Windows Command Shell (cmd.exe)
# This file can be transplanted to differnet programming problems.
# 此脚本可复用。
# 此脚本必须结合 compare.py, gen_data.py 一同使用。

import shutil as st
import sys
import os
from data_gen import gen
from compare import cmp

# compileCommandStr = "g++ " + dataFileName + ".cpp -g -o " + progName
compileCommandStr = "mingw32-make"


def RuntimeError(exitCode, dataFileName):    # Runtime Error at Testpoint #i
    resultFile = open(dataFileName + ".result", "w")
    resultFile.write("Runtime Error " + str(exitCode))


def WriteOverview(isCE, numTestPt, progName, dataFileName):
    # Generate an overview of the testpoints result
    print("Generating result overview.")
    overviewFile = open("result/overview.result", "w")
    overviewFile.write("Program Name = " + progName + "\n")
    overviewFile.write("Number of Test Points = " + str(numTestPt) + "\n")
    overviewFile.write("Test Details:\n")

    if isCE:
        overviewFile.write("Compile Error")
        exit()
    cntAC = cntWA = cntRE = 0

    for i in range(numTestPt):
        resFile = open("result/" + dataFileName + ".result" + str(i), "r")
        resFileFirstLine = resFile.readline().split("\n")[0]
        if resFileFirstLine == "******Passed******":
            overviewFile.write("#" + str(i) + ": AC\n")
            cntAC += 1
        elif resFileFirstLine == "------Testpoint failed. Detailed information:------":
            overviewFile.write("#" + str(i) + ": WA\n")
            cntWA += 1
        else:
            overviewFile.write("#" + str(i) + ": RE\n")
            cntRE += 1
        resFile.close()
    overviewFile.write("In total:\n AC = " + str(cntAC) +
                       "\nWA = " + str(cntWA) + "\nRE = " + str(cntRE) + "\n")
    overviewFile.close()
    print("Result overview is written in ""result/overview.result"".")


def main():
    print("To have this script functioning normally, you will have this file along with compare.py, data_gen.py.\n")

    if os.path.exists("user_output"):
        st.rmtree("user_output")
    if os.path.exists("result"):
        st.rmtree("result")


    os.makedirs("result", exist_ok=True)
    os.makedirs("user_output", exist_ok=True)

    if (not os.path.exists("data")) or (not os.path.exists("data/config")):
        print("No input data found or lost the test configuration file. Generating new data set using ""data_gen.py"".")
        gen()

    configFile = open("data/config", "r")
    configFileContent = configFile.readlines()
    progName = configFileContent[0][:-1]
    dataFileName = configFileContent[1][:-1]
    numTestPt = int(configFileContent[2][:-1])

    print("Compiling...")
    isCE = False
    if os.system(compileCommandStr) != 0:
        isCE = True
        WriteOverview(isCE, numTestPt, progName, dataFileName)
        exit(-1)

    print("Done Compiling. Start testing...")

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
        if (exitCode != 0):
            RuntimeError(exitCode)
        else:
            cmp(dataFileName)
        os.system(renameCmpResultCommandStr)
        os.system(copyUserOutputStr)
        os.system(cleanInCommandStr)
        os.system(cleanAnsCommandStr)

    WriteOverview(isCE, numTestPt, progName, dataFileName)

    os.system("del *.exe")
    os.system("del *.o")


if __name__ == "__main__":
    print("Copyright (C) 2022 Zhong Tiantian, Zhejiang University")

    if sys.platform != "win32":
        print("This script is not supported on " + sys.platform() + ".")
    else:
        main()
