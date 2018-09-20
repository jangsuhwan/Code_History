def binary_search(L, K):
    index = []
    for j in range(0, len(L)):
        t = 0
        f = 0
        e = len(L[j]) - 1
        while (f <= e):
            m = (int)((f+e) /2)
            if K[j] == (L[j])[m]:
                index.append(m)
                t=1
                break
            elif K[j] < (L[j])[m]:
                e = m - 1
            elif K[j] > (L[j])[m]:
                f = m + 1
        if(t==1):
            continue
        else:
            index.append(-1)
    return index

def sequential_search(L, K):
    index = []
    t = 0
    for i in range(0, len(L)):
        search = K[i]
        for j in range(0, len(L[i])):
            if ((L[i])[j] == K[i]):
                t = 1
                index.append(j)
                break
        if(t != 1):
            index.append(-1)
    return index

