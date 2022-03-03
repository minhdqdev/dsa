def search_triplets(arr):
  triplets = []
  arr.sort()

  for i in range(len(arr)-2):
    target = arr[i] * -1
    left = i + 1
    right = len(arr) - 1

    while left < right:
      s = arr[left] + arr[right]

      if s == target:
        triplets.append([arr[i], arr[left], arr[right]])
        left += 1
        right -= 1
      elif s > target:
        right -= 1
      else:
        left += 1

  return triplets


if __name__ == '__main__':
    triplets = search_triplets([-3, 0, 1, 2, -1, 1, -2])

    print(triplets)