import numpy as np
compareDic = {} # Record a set of elements which have been compared with their keys

def find(myList):   # Find the smallest and second smallest element
    if len(myList) == 1:    # The list contains only one element
        return myList[0]
    nextSublist = []
    for i in range(len(myList)):
        if i % 2 == 1:  # Pairing process always happens on even-index element
            continue
        else:
            if i+1==len(myList):    # Reaching the end of a list whose length is an odd number
                nextSublist.append(myList[i])
                continue
            
            # Record that the `$(i+1)$`-th element have been compared with the `$i$`-th
            # To reduce the memory space used by compareDic, we assume that a key is always larger than its entries.
            if myList[i] > myList[i+1]:
                nextSublist.append(myList[i+1])
                if myList[i+1] in compareDic.keys():
                    compareDic[myList[i+1]].append(myList[i])
                else:
                    compareDic[myList[i+1]] = [myList[i]]
            else:
                nextSublist.append(myList[i])
                if myList[i] in compareDic.keys():
                    compareDic[myList[i]].append(myList[i+1])
                else:
                    compareDic[myList[i]] = [myList[i+1]]
    return find(nextSublist)

# The main function only provides a testing environment
def main():
    np.random.seed(114514)
    listsize = 100
    random_list = np.random.randint(low=0, high=1000, size=listsize).tolist()

    smallest = find(random_list)

    se_sm = 1002 
    for log_n in compareDic[smallest]:
        if log_n < se_sm:
            se_sm=log_n

    print(random_list, smallest,se_sm)

if __name__ == "__main__":
    main()
