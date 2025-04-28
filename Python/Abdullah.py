
# Python Practice - If-Else Problems

## 1. Even or Odd
```python
number = int(input("Enter an integer: "))
if number == 1 or number == 0:
    print("Invalid input")
elif number % 2 == 0:
    print("Even")
else:
    print("Odd")
```

## 2. Positive, Negative, or Zero
```python
number = int(input("Enter an integer: "))
if number == 0:
    print("Zero")
elif number > 0:
    print("Positive")
else:
    print("Negative")
```

## 3. Vowel or Consonant
```python
number1 = input("Enter a character: ")
if number1 in 'aeiou':
    print("Vowel")
else:
    print("Consonant")
```

## 4. Leap Year Checker
```python
number1 = int(input("Enter a year: "))
if (number1 % 400 == 0) or (number1 % 4 == 0 and number1 % 100 != 0):
    print("Leap Year")
else:
    print("Not a Leap Year")
```

