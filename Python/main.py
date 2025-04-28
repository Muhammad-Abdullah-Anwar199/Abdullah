number1=int(input("Enter 1st integer:"))
if (number1%400==0) or (number1%4==0 and number1%100!=0):
    print("Leap")
else:
    print('Not')