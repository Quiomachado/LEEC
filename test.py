def sub(a, b):
    return a - b


def sum(a, b):
    return a + b


def mul(a, b):
    return a * b


def div(a, b):
    return a / b


def modu(a, b):
    return a % b


def calc(a, b, op):
    if op == '+':
        return sum(a, b)
    elif op == '-':
        return sub(a, b)
    elif op == '*':
        return mul(a, b)
    elif op == '/':
        return div(a, b)
    elif op == '%':
        return modu(a, b)
    else:
        # if invalid op loop until valid op is entered
        while op != '+' or op != '-' or op != '*' or op != '/' or op != '%':
            print("Invalid operator")
            op = input("Enter valid operator: ")
            if op == '+' or op == '-' or op == '*' or op == '/' or op == '%':
                break


def main():
    a = int(input("Enter first number: "))
    b = int(input("Enter second number: "))
    op = input("Enter operator: ")
    print(calc(a, b, op))


if __name__ == '__main__':
    main()
