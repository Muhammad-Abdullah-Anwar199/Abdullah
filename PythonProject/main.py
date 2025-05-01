from symbol import return_stmt
#task 1
numbers=100
for i in range(1,numbers+1):
    if i%2==0:
        print(f'{i} is = Even')
    else:
        print(f'{i} is = Odd')
#task 2
sum=0
for i in range(1,6):
    sum+=i
print(f'sum is = {sum} ')
#task 3
count=int(input())
result=1
for i in range(1,count+1):
    result*=i
print(result)
#task 4
for i in range(1,5):
    for j in range(i):
        print('*',end='')
    print()
#task 5
first=0
second=1
number=int(input('Enter the u want to generate:'))
for i in range(number):
    print(f'Sequence---->{first}')
    next=first+second
    first=second
    second=next
#task 6
number=int(input('Enter a number:'))
reversed=0
for i in range(len(str(number))):
    digit=number%10
    reversed=reversed*10 + digit
    number//=10
print(f'Reversed is {reversed}')

#task 7
for i in range(1,5): #No of rows
    for j in range(5-i): #Print spaces
        print(' ',end='')
    for k in range(2*i-1): # not nested in j but in i that print stars
        print('*',end='')
    print()

#task 8
for i in range(1,5): #rows
    for j in range(1,5): # for cols
        if i==1 or i==4 or j==1 or j==4:
            print('*',end='')
        else:
            print(" ",end='')
    print()