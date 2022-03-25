class Solution:
    def average(self, salary: List[int]) -> float:
        max_salary = salary[0]
        min_salary = salary[0]
        s = 0
        for i in range(len(salary)):
            if salary[i] > max_salary:
                max_salary = salary[i]
            elif salary[i] < min_salary:
                min_salary = salary[i]
            
            s += salary[i]
        
        return (s - max_salary - min_salary) / (len(salary)-2)
            