# 此脚本可复用。
# 此脚本既可单独运行，也可做为 autotest.py 的一个模块使用。
from asyncore import read
from sys import stdout


def cmp(dataFileName):
    myAns = open(dataFileName+".out", "r")
    stdAns = open(dataFileName+".ans", "r")
    result = open(dataFileName+".result", "w")

    myAnsContent = myAns.readlines()
    stdAnsContent = stdAns.readlines()
    

    # Remove all the appending line wrappers
    if len(myAnsContent) != 0:
        while myAnsContent[-1] == "\n":
            myAnsContent.pop(-1)
    if len(stdAnsContent) != 0:
        while stdAnsContent[-1] == "\n":
            stdAnsContent.pop(-1)

    if myAnsContent == stdAnsContent:
        result.write("******Passed******")
    else:
        result.write("------Testpoint failed. Detailed information:------\n")
        if len(myAnsContent) != len(stdAnsContent):
            result.write("Output length incorrect.\n")
            result.write("Standard output has " + str(len(stdAnsContent)) + " lines.\n")
            result.write("    Your output has " + str(len(myAnsContent)) + " lines.\n\n")
        else:
            result.write("Output length correct.\n")

        for i in range(min(len(myAnsContent), len(stdAnsContent))):
            if myAnsContent[i] != stdAnsContent[i]:
                result.write("line " + str(i) + ": \n     " + str(myAnsContent[i]) + "     <->\n     " + str(stdAnsContent[i]) + "\n")
    myAns.close()
    stdAns.close()
    result.close()

if __name__ == "__main__":
    configFile = open("data/config", "r")
    configFileContent = configFile.readlines()
    dataFileName = configFileContent[1][:-1]
    cmp(dataFileName)