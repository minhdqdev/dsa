class Solution:
    def partitionLabels(self, s: str) -> List[int]:
        # last_appears[char] = pos
        last_appears = {}

        n = len(s)
        for i in range(n - 1, -1, -1):
            if s[i] not in last_appears:
                last_appears[s[i]] = i

        start = 0

        res = []

        while start < n:
            # build partition [start, end]
            i = start
            end = last_appears[s[start]]
            i += 1

            while i < end:
                if last_appears[s[i]] > end:
                    end = last_appears[s[i]]
                i += 1

            res.append(end - start + 1)
            start = end + 1

        return res
