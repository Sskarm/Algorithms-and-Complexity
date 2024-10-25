def interpolation_search(arr, target):
  """Performs interpolation search on a sorted array with print statements.

  Args:
    arr: The sorted array to search.
    target: The target element to search for.

  Returns:
    The index of the target element in the array, or -1 if not found.
  """

  low = 0
  high = len(arr) - 1

  while low <= high:
    pos = low + (target - arr[low]) * (high - low) // (arr[high] - arr[low])

    print(f"Low: {low}, High: {high}, Pos: {pos}")

    if arr[pos] == target:
      return pos
    elif arr[pos] < target:
      low = pos + 1
    else:
      high = pos - 1

  return -1

# Example usage
arr = [1, 2, 3, 4, 5, 100, 101, 102, 103, 104]
target = 102
index = interpolation_search(arr, target)

if index != -1:
  print("Element found at index:", index)
else:
  print("Element not found")