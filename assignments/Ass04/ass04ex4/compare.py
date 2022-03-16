from sys import stdout


def main():
    myAns = open("heap.out", "r")
    stdAns = open("heap.ans", "r")
    result = open("heap.result", "w")

    myAnsContent = myAns.readlines()
    stdAnsContent = stdAns.readlines()

    # Remove all the appending line wrappers
    if len(myAnsContent) != 0:
        while myAnsContent[len(myAnsContent) - 1] == "\n":
            myAnsContent.pop(len(myAnsContent) - 1)
    if len(stdAnsContent) != 0:
        while stdAnsContent[len(stdAnsContent) - 1] == "\n":
            stdAnsContent.pop(len(stdAnsContent) - 1)

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
            if str(myAnsContent[i]) != str(stdAnsContent[i]):
                result.write("line " + str(i) + ": \n     " + str(myAnsContent[i]) + "     <->\n     " + str(stdAnsContent[i]) + "\n")
    myAns.close()
    stdAns.close()
    result.close()

if __name__ == "__main__":
    main()