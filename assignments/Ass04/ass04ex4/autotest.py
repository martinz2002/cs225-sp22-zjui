# This file only works on Windows, the commands are capable for Windows Command Shell (cmd.exe)

import os
dataFileName = "heap"
progName = "heap_test"
numTestPt = 10

# compileCommandStr = "g++ " + dataFileName + ".cpp -g -o " + progName
compileCommandStr = "mingw32-make"

def main():
    print("Copyright 2022 Zhong Tiantian (tiantianz.20@intl.zju.edu.cn)")
    print("This is an autotest script for " + progName + ".\n")
    print("To have it function normally, you will have this file along with compare.py, data_gen.py.\n")
    print("NOTE: This script only works for Windows, as it relies on Windows Command Shell commands.\n")
    print("Compiling...")
    os.system(compileCommandStr)
    print("Done Compiling. Start testing...")
    os.system("del result user_output")
    os.system("del user_output")
    os.system("mkdir result")
    os.system("mkdir user_output")
    for i in range(numTestPt):
        copyCommandStr = "copy data\\" + dataFileName + \
            ".in" + str(i) + " " + dataFileName + ".in"
        stdAnsCommandStr = "copy data\\" + dataFileName + \
            ".ans" + str(i) + " " + dataFileName + ".ans"
        execCommandStr = progName
        copyUserOutputStr = "move " + dataFileName + \
            ".out user_output\\" + dataFileName + ".out" + str(i)
        cmpCommandStr = "python compare.py"
        renameCmpResultCommandStr = "move " + dataFileName + \
            ".result result\\" + dataFileName + ".result" + str(i)
        cleanInCommandStr = "del " + dataFileName + ".in"
        # cleanOutCommandStr = "del " + dataFileName + ".out"
        cleanAnsCommandStr = "del " + dataFileName + ".ans"
        # before running copy input file to the program dir, and remove the id of the copy in extension name

        print("Copying input file #" + str(i) + "...")
        os.system(copyCommandStr)
        print("Done. Dealing with answer file #" + str(i) + "...")
        os.system(stdAnsCommandStr)
        print("Done. Executing the program...")
        os.system(execCommandStr)
        print("Done. Comparing your answer with the standard answer...")
        os.system(cmpCommandStr)
        os.system(renameCmpResultCommandStr)
        print("Done. The result is written in result\\" +
              dataFileName + ".result" + str(i))
        os.system(copyUserOutputStr)
        os.system(cleanInCommandStr)
        # os.system(cleanOutCommandStr)
        os.system(cleanAnsCommandStr)
        print("End of testpoint #" + str(i))

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
