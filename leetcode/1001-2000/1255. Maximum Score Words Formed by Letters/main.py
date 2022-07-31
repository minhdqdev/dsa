class Solution:
    def __init__(self):
        self.max_score = 0
    
    def build_backtrack(self, words, score, index, avail, s):
            if index == len(words):
                if s > self.max_score:
                    self.max_score = s
                
                return

            word_score = 0
            need = {}
            for i in words[index]:
                if i not in need:
                    need[i] = 1
                else:
                    need[i] += 1
                
                word_score += score[ord(i)-ord('a')]
            
            # check if can use the word
            can_use = True
            for i in need:
                if i not in avail or need[i] > avail[i]:
                    can_use = False
                    break
            
            if can_use:
                # update new avail
                new_avail = avail.copy()
                
                for i in need:
                    new_avail[i] -= need[i]
                
                self.build_backtrack(words, score, index+1, new_avail, s+word_score)
            self.build_backtrack(words, score, index+1, avail, s)
    
    def maxScoreWords(self, words: List[str], letters: List[str], score: List[int]) -> int:
        avail = {}
        for l in letters:
            if l not in avail:
                avail[l] = 1
            else:
                avail[l] += 1
        
        self.build_backtrack(words, score, 0, avail, 0)
        
        return self.max_score