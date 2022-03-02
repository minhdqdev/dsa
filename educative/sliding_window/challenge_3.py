def find_substring(str1, pattern):
    min_length = len(str1)+1
    min_pos = -1
    matched = 0
    dd = {}
    for i in range(len(pattern)):
        if pattern[i] not in dd:
            dd[pattern[i]] = 1
        else:
            dd[pattern[i]] += 1
    
    # print(dd)

    if str1[0] in dd:
        if dd[str1[0]] == 1:
            matched += 1
        dd[str1[0]] -= 1

    wstart, wend = 0, 0
    while wend < len(str1):
        # check
        if matched == len(dd):
            # print('before shrink: ', wstart, wend, dd, matched)
            if wend - wstart + 1 < min_length:
                min_length = wend - wstart + 1
                min_pos = wstart

            # shrink until not matched
            while wstart <= wend:
                if str1[wstart] in dd:
                    if dd[str1[wstart]] == 0:
                        matched -= 1
                    dd[str1[wstart]] += 1
                wstart += 1

                if matched != len(dd):
                    break
                
                if wend - wstart + 1 < min_length:
                    min_length = wend - wstart + 1
                    min_pos = wstart

            # print('after shrink: ', wstart, wend, dd, matched)
        else:
            if wend + 1 < len(str1):
                # append
                if str1[wend+1] in dd:
                    if dd[str1[wend+1]] == 1:
                        matched += 1
                    dd[str1[wend+1]] -= 1
            
                wend += 1
                # print('after append: ', wstart, wend, dd, matched)
            else:
                break

    if min_pos == -1:
        return ""

    return str1[min_pos: min_pos+min_length]


if __name__ == '__main__':
    str1 = "adcad"
    pattern = "abc"
    res = find_substring(str1, pattern)

    print(res)