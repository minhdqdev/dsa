class Solution:
    def sampleStats(self, count: List[int]) -> List[float]:
        min_val = 2 ** 31 - 1
        max_val = -2 ** 31
        mean = 0
        median = -1
        mode = 0
        
        total_count = 0
        
        max_c = 0
        
        # calculate min, max, mode
        for i, c in enumerate(count):
            if c > max_c:
                mode = i
                max_c = c
            
            if c != 0:
                total_count += c
                
                if i < min_val:
                    min_val = i
                if i > max_val:
                    max_val = i
        
        # calculate mean, median
        median_index = (total_count - 1) // 2
        index = -1
        is_odd = total_count % 2 != 0
        prev_i = -1
        
        for i, c in enumerate(count):
            if c != 0:
                mean += i * c / total_count
                
                if median == -1:
                    index += c
                    
                    if is_odd:
                        if index >= median_index:
                            median = i
                    else:
                        if index == median_index:
                            prev_i = i
                        elif index > median_index:
                            if prev_i == -1:
                                median = i
                            else:
                                median = (prev_i + i) / 2

        
        return [min_val, max_val, mean, median, mode]