import csv
from algorithm.sort import *
from algorithm.search import *
# ---- 패키지 안의 모듈을 import ----#

# ----------------------------------#

result = []
key = []
with open("unsorted.csv", 'r') as p_file:
    csv_data = csv.reader(p_file)  # Open한 파일을 csv 객체를 사용해서 읽기
    for row in csv_data:
        row = [int(i) for i in row]
        key.append(row[len(row)-1])
        row.pop()
        row = insertion_sort(row)
        result.append(row)
    print(result)
    key = binary_search(result, key)
    for i in range(0, len(key)):
        result[i].append(key[i])

with open("sorted.csv", 'w') as i_p_file:
    writer = csv.writer(i_p_file, delimiter=',', lineterminator='\n')
    for data in result:
        writer.writerow(data)