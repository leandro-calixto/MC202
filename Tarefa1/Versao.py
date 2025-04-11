def busca(s, m, caracter, begin, good, max_value):
    max_value = 0
    new_m = list(m)
    new_m_combinations = []
    if caracter == '+':
        new_m.remove('+')
        new_m_combinations.append(''.join(new_m))
        if begin > 0 and s[begin - 1] == s[begin]:
            while s[begin + max_value - 1] == s[begin + max_value]:
                new_m.insert(m.index('+'), s[begin])
                new_m_combinations.append(''.join(new_m))
                max_value += 1
            good += 1
        max_value += 1
    return good, max_value, new_m_combinations

def busca_motivo(s, m):
    count = 0
    for i in range(len(s)):
        current_m, begin, j, loop, good, max_value, a = m, i, 0, 0, 1, 1, 0
        list = []
        while begin < len(s) and loop < max_value and good > 0:
            if 'a' <= current_m[j] <= 'z':
                if s[begin] == current_m[j] and (j + 1) == len(current_m):
                    good = 0
                    count += 1
                elif s[begin] == current_m[j] and (j + 1) < len(current_m):
                    begin += 1
                    j += 1
                elif s[begin] != current_m[j]:
                    if a > 0:
                        a -= 1
                        current_m = list[a]
                    else:
                        good = 0
            if current_m[j] == '+':
                good, max_value, list = busca(s, current_m, current_m[j], begin, good, max_value)
                a = len(list) - 1
                current_m = list[a]
    return count

s = "tccaaatcaattcatccccaa"
m = "tc+a"

s = s.lower()
result = busca_motivo(s, m)
print(result)
