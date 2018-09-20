def bubble_sort(L):
    loop = 0
    for j in range(0, len(L)):
        for i in range(0, len(L)-1):
            if L[i] > L[i+1]:
                temp = L[i]
                L[i] = L[i+1]
                L[i+1] = temp
    return L

def selection_sort(L):
    U = []
    for i in range(0, len(L)):
        U.append(L[i])
    i = 0
    while(i < len(U)):
        min = L[0]
        for j in range(1, len(L)):
            if min > L[j]:
                min = L[j]
        for t in range(0, len(U)):
            index = U.index(min)
        L.remove(min)
        temp = U[i]
        U[i] = min
        U[index] = temp
        i = i+1
    return U

def insertion_sort(L):
    U = [L[0]]
    for k in range(1, len(L)):
        for j in range(0, k):
            if U[j] > L[k]:
                U.insert(j, L[k])
                break
            elif j == k-1:
                U.append(L[k])
    return U


