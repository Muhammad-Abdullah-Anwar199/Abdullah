numbers=int(input("Enter a number:"))
if numbers<=1:
    print("Not Prime!")
is_Prime=True
for i in range(2,numbers):
    if numbers%i==0:
        is_Prime=False
        break
if is_Prime:
    print("Prime")
else:
    print('Not')

print()
'''Task 2'''
arr=[1,2,3,4,5]
count =0
for i in arr:
    count+=1
print(f'there are {count} in given list of numbers.')
print('\n')

'''''Task 3'''

for i in range(-10,0):
    print(-i,end=' ')
print('\n')

'''Task 4'''

for i in range(1,numbers+1):
    print(f'{numbers} x {i} = {numbers*i}')
print('\n')

'''Task 5'''

sum=0
for i in range(1,101):
    sum+=i
print(sum)
print('\n')


