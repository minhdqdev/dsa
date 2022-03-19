def search_quadruplets(arr, target):
  quadruplets = []
  arr.sort()

  prev_w = arr[0]
  for w in range(len(arr)-3):
    if w > 0:
      if arr[w] == prev_w:
        continue
      else:
        prev_w = arr[w]
    
    prev_z = arr[w+1]
    for z in range(w+1, len(arr)-2):
      if arr[z] == arr[w]:
        continue

      if z > w+1:
        if arr[z] == prev_z:
          continue
        else:
          prev_z = arr[z]
      
      # find pairs
      left, right = z + 1, len(arr) - 1
      sub_target = target - arr[w] - arr[z]
      prev_l, prev_r = arr[left], arr[right]

      while left < right:
        print(arr[w], arr[z], arr[left], arr[right], sub_target, left, right)

        if arr[left] == arr[right]:
          break # there is no pair to check
        if arr[left] == arr[z]:
          left += 1
          continue
        
        if left > z + 1:
          if arr[left] == prev_l:
            left += 1
            continue
          else:
            prev_l = arr[left]
        
        if right < len(arr) - 1:
          if arr[right] == prev_r:
            right -= 1
            continue
          else:
            prev_r = arr[right]

        ss = arr[left] + arr[right]

        if ss == sub_target:
          quadruplets.append([arr[w], arr[z], arr[left], arr[right]])
          left += 1
          right -= 1
        elif ss > sub_target:
          right -= 1
        elif ss < sub_target:
          left -= 1

  return quadruplets


if __name__ == '__main__':
  quadruplets = search_quadruplets([4, 1, 2, -1, 1, -3], 1) 
  quadruplets = search_quadruplets([2, 0, -1, 1, -2, 2], 2)

  print(quadruplets)
