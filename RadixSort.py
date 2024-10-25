def radix_sort(arr):
    """Efficient radix sort implementation with print statements.

    Args:
        arr: The list of numbers to sort.

    Returns:
        The sorted list of numbers.
    """

    max_val = max(arr)
    exp = 1

    while max_val // exp > 0:
        print(f"Current exp: {exp}")
        counting_sort(arr, exp)
        print(f"After counting sort: {arr}")
        exp *= 10

    return arr

def counting_sort(arr, exp):
    """Counting sort helper function with print statements.

    Args:
        arr: The list of numbers to sort.
        exp: The current exponent for digit extraction.
    """

    n = len(arr)
    output = [0] * n
    count = [0] * 10

    print(f"Counting digits at position {exp}")
    for i in range(n):
        index = (arr[i] // exp) % 10
        count[index] += 1
        print(f"Counting {arr[i]} at index {index}")

    print(f"Counting array: {count}")

    for i in range(1, 10):
        count[i] += count[i - 1]

    print(f"Cumulative counting array: {count}")

    for i in range(n - 1, -1, -1):
        index = (arr[i] // exp) % 10
        output[count[index] - 1] = arr[i]
        count[index] -= 1

    for i in range(n):
        arr[i] = output[i]

# Example usage
arr = [170, 45, 75, 90, 802, 24, 2, 66]
print("Original array:", arr)
sorted_arr = radix_sort(arr)
print("Sorted array:", sorted_arr)