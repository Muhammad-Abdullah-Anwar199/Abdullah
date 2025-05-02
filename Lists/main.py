#Task 1

reverse=[1,2,3,4,5]
for i in range(-5,0):
    print(-i,end=' ')
print()

#Task 2

maxMin=[1,2,3,4,5]
max1=maxMin[0]
for i in range(0,len(maxMin)):
    if maxMin[i]>max1:
        max1=maxMin[i]
print(max)
min1=maxMin[0]
for i in range(0,len(maxMin)):
    if maxMin[i]<min1:
        min1=maxMin[i]
print(min)
print()

#Task 3 min max using built-in functions
number=[45,76,23,34]
print(max(number))
print(min(number))

#Task 4
element=[1,2,3,4,5]
sum=0
for i in range(0,len(element)+1):
    sum+=i
print(f'sum is={sum}')

#Task 5

nu=[10, 21, 4, 45, 66, 93]
evenNum=[]
oddNum=[]
for i in range(0,len(nu)):
    if nu[i]%2==0:
        evenNum.append(nu[i])
    else:
        oddNum.append(nu[i])
print(evenNum)
print(oddNum)

#Task 6

nums = [10, 20, 30, 40, 50, 60, 70]

print("Every 2nd element:", nums[::2])
print("Every 3rd element:", nums[::3])
print("Reverse list:", nums[::-1])

#Task 7
def flatten_list(nested):
    flat = []
    for i in range(len(nested)):            # Loop through outer list
        for j in range(len(nested[i])):     # Loop through each inner list
            flat.append(nested[i][j])       # Append each element to flat list
    return flat

nested = [[1, 2, 3], [4, 5], [6, 7, 8]]
result = flatten_list(nested)
print("Flattened List:", result)

#Task 8 multidimesnional lsit
my=[[1,2,3],[['a','b','c'],[5,6]]]
print(my[1][1][1])