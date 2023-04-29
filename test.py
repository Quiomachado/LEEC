def sum(a, b):
    return a+b


def sub(a, b):
    return a-b


def mul(a, b):
    return a*b


def div(a, b):
    return a/b if b != 0 else 0


def main():
    a = int(input("Enter a: "))
    b = int(input("Enter b: "))
    op = input("Enter operation: ")
    if op == "+":
        print(sum(a, b))
    elif op == "-":
        print(sub(a, b))
    elif op == "*":
        print(mul(a, b))
    elif op == "/":
        print(div(a, b))
    else:
        print("Invalid operation")


if __name__ == "__main__":
    main()
