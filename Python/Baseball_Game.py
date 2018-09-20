#12131588 장수환

import random

def CreateCom():
    numlist = []
    while(len(numlist) != 3):
        x = random.randrange(1, 10)
        numlist.append(str(x))
        numlist = list(set(numlist))
    return numlist

def CreateUser():
    while(True):
        num = input("숫자 3자리를 입력하세요:")
        test = TestInput(num)
        if test == -1:
            break
        if test == 1:
            exit()
    userNum = list(num)
    return userNum

def TestInput(num):
    if num == "0":
        return 1
    elif len(num) != 3:
        print("3자리만 입력하세요")
    elif num.isdigit() != True:
        print("10진수 숫자만 입력하세요")
    elif num.count("0") > 0 :
        print("1 ~ 9에서만 입력하세요")
    elif len(set(num)) != 3:
        print("중복은 안됩니다.")
    else:
        return -1

def CompareNum():
    com = CreateCom()
    count = 0
    while (True):
        strike = 0
        ball = 0
        user = CreateUser()
        for i in range(3):
            if user[i] == com[i]:
                strike = strike + 1
            for j in range(3):
                if user[j] == com[i] and j != i:
                    ball = ball + 1
        count = count + 1
        Show_Result(strike, ball)
        if(strike == 3):
            print("--------------")
            print("%d번 만에 정답을 맞추셧습니다" % count)
            Game_Restart()
            CompareNum()

def Game_Restart():
    while(True):
        x = input("Do you want one more game? (Yes / No) ")
        if x.lower()=="yes":
            return
        elif x.lower() == "no":
            exit()


def Show_Result(strike, ball):
    print ("결과 : [%d] Strike [%d] Ball" % (strike, ball))

def Game_Start():
    print("숫자야구를 시작합니다!!")
    print("----------------------")

Game_Start()
CompareNum()

