

import numpy as np
compare_dic = {}



def find(list_name):
    if len(list_name) == 1:
        return list_name[0]
    next_sub_list = []
    for i in range(len(list_name)):
        if i % 2 == 1:
            continue
        else:
            if i+1==len(list_name):
                next_sub_list.append(list_name[i])
                continue

            if list_name[i] > list_name[i+1]:
                next_sub_list.append(list_name[i+1])
                if list_name[i+1] in compare_dic.keys():
                    compare_dic[list_name[i+1]].append(list_name[i])
                else:
                    compare_dic[list_name[i+1]] = [list_name[i]]
            else:
                next_sub_list.append(list_name[i])
                if list_name[i] in compare_dic.keys():
                    compare_dic[list_name[i]].append(list_name[i+1])
                else:
                    compare_dic[list_name[i]] = [list_name[i+1]]
    return find(next_sub_list)


np.random.seed(114514)
listsize = 100
random_list = np.random.randint(low=0, high=1000, size=listsize).tolist()

smallest = find(random_list)

se_sm = 1002 
for log_n in compare_dic[smallest]:
    if log_n < se_sm:
        se_sm=log_n

print(random_list, smallest,se_sm)
