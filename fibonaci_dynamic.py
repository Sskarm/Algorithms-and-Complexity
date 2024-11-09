def fibonacci(n):
    fib = [0] * (n +1)
    fib [0] = fib [1] = 1
    print("1")
    print("1")
    for i in range(2,n+1):
        fib[i] = fib[i-1] + fib[i-2]
        print(fib[i])
    
    return fib[n]

def main():
    n = int(input("Enter the value of n: "))
    result = fibonacci(n-1)
    print(f"The {n}-th Fibonacci number is: {result}")

if __name__ == "__main__":
    main()

