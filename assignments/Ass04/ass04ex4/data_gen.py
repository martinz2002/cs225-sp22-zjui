import os
import random
from unicodedata import numeric

minNum = -10000
maxNum = 10000
minLen = 0
maxLen = 1000
numTestPt = 10


def main():
    os.system("rmdir data")
    for idTestPt in range(numTestPt):
        dataList = []
        fileIn = open("data/heap.in" + str(idTestPt), "w")  # input file
        fileOut = open("data/heap.ans" + str(idTestPt), "w")
        numElm = random.randint(minLen, maxLen)  # number of input elements
        fileIn.writelines([str(numElm), "\n"])
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
