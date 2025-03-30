class Solution:
    def countOfSubstrings(self, word: str, k: int) -> int:
        # sliding windows
        vowels = {"a": 0, "e": 0, "i": 0, "o": 0, "u": 0}
        count_consonants = 0
        vowel_set = vowels.keys()

        i, j = 0, 0
        n = len(word)
        res = 0

        def is_good():
            nonlocal k
            nonlocal vowels
            nonlocal count_consonants
            return count_consonants == k and all(v > 0 for v in vowels.values())

        def is_vowel(c):
            nonlocal vowel_set
            return c in vowel_set

        def pick(pos):
            nonlocal vowels
            nonlocal count_consonants

            if is_vowel(word[pos]):
                vowels[word[pos]] += 1
            else:
                count_consonants += 1

        def pop(pos):
            nonlocal vowels
            nonlocal count_consonants

            if is_vowel(word[pos]):
                vowels[word[pos]] -= 1
            else:
                count_consonants -= 1

        # precompute the index of the next consonant at pos i
        next_consonants = [0] * n
        next_consonant_index = n
        for e in range(n - 1, -1, -1):
            next_consonants[e] = next_consonant_index

            if not is_vowel(word[e]):
                next_consonant_index = e

        while j < n:
            pick(j)

            while count_consonants > k:
                # shrink
                pop(i)
                i += 1

            while is_good():
                res += next_consonants[j] - j

                # shrink
                pop(i)
                i += 1

            # expand
            j += 1

        return res
