import os
import random

minNum = -10000
maxNum = 10000
minLen = 0
maxLen = 1000
numTestPt = 10


def main():
    
    os.system("del data")
    os.system("mkdir data")

    # make a special test point where input list is empty
    fileIn = open("data/heap.in" + str(9), "w")  # input file
    fileOut = open("data/heap.ans" + str(9), "w")
    fileIn.write(str(0))
    fileOut.write("EMPTY HEAP\n")
    fileIn.close()
    fileOut.close()


    for idTestPt in range(numTestPt - 1):
        dataList = []
        fileIn = open("data/heap.in" + str(idTestPt), "w")  # input file
        fileOut = open("data/heap.ans" + str(idTestPt), "w")
        numElm = random.randint(minLen, maxLen)  # number of input elements
        fileIn.writelines([str(numElm), "\n"])
        if numElm == 0:
            fileOut.write("EMPTY HEAP")
        else:
            for i in range(numElm):
            # generate elements and put it in the list
                element = random.randint(minNum, maxNum)
                dataList.append(element)
                fileIn.write(str(element))
                fileIn.write("\n")

        # sort the generated data as the standard answer using sort(), descending
        dataList.sort(reverse=True)
        fileOut.write(str(dataList[0]) + "\n")  # the first element is the maximum
        # ↑↑↑ This is to test the correctness of function max() in the heap program ↑↑↑
        for i in range(numElm):
            fileOut.write(str(dataList[i]) + "\n")

        fileIn.close()
        fileOut.close()


if __name__ == "__main__":
    main()
