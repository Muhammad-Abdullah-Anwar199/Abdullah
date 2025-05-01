# Task 1: Check if a number is even or odd
def even(number):
    if number % 2 == 0:
        print('Even')
    else:
        print('Odd')


# Task 2: Find multiples of a given number
def multiples(num):
    for i in range(1, num + 1):  # Start from 1 to avoid division by zero
        if num % i == 0:
            print(i, "is a multiple of", num)


# Task 3: Count even numbers from 2 to the given number
def evenCount(number):
    count = 0
    for i in range(2, number + 1):
        if i % 2 == 0:
            count += 1
    print(count)


# Task 4: Print stars in a single line
def stars(num):
    for i in range(1, num + 1):
        print('*', end='')
    print()  # To move to the next line after printing stars


# Task 5: Sum of numbers from 0 to n-1
def sum_of_numbers(num):
    total = 0
    for i in range(0, num):
        total += i
    print(f'Total sum is = {total}')


# Task 6: Check if a year is a leap year
def leap(number):
    if (number % 4 == 0 and number % 100 != 0) or (number % 400 == 0):
        print("Leap")
    else:
        print('Not Leap')


# Task 7: Print numbers in reverse order from n to 1
def reverse(num):
    for i in range(num, 0, -1):
        print(i)


# Task 8: Check if a person is eligible to vote (age >= 18)
def vote(number):
    if number >= 18:
        print('Eligible')
    else:
        print('Not Eligible')


# Task 9: Calculate the factorial of a number
def factorial(number):
    result = 1
    if number == 0 or number == 1:
        return 1
    else:
        for i in range(2, number + 1):
            result *= i
    print(result)


# Task 10: Find the greatest of three numbers
def max_num(a, b, c):
    if a > b and a > c:
        print(f'{a} is greater')
    elif b > a and b > c:
        print(f'{b} is greater')
    else:
        print(f'{c} is greater')


# Task 11: Swap two numbers
def swap(a, b):
    temp = a
    a = b
    b = temp
    print(f'A is={a}, B is={b}')


# Task 12: Built-in max function
def max1(a, b, c):
    if a == b == c:  # Check if all values are equal first
        print("None is greater")
    else:
        print(f'{max(a, b, c)} is greater')


# Run the tasks directly without the main function
print("Task 1: Even or Odd")
even(10)

print("\nTask 2: Multiples of a number")
multiples(10)

print("\nTask 3: Count of even numbers")
evenCount(10)

print("\nTask 4: Print Stars")
stars(3)

print("\nTask 5: Sum of numbers")
sum_of_numbers(5)

print("\nTask 6: Leap Year Check")
leap(2024)

print("\nTask 7: Reverse Numbers")
reverse(5)

print("\nTask 8: Vote Eligibility")
vote(18)

print("\nTask 9: Factorial")
factorial(4)

print("\nTask 10: Find Maximum of Three Numbers")
max_num(4, 5, 6)

print("\nTask 11: Swap Numbers")
swap(10, 11)

print("\nTask 12: Built-in Max Function")
max1(13, 45, 12)
