def sum(n):

    sum = 0
    while n > 0:
        digit = n % 10
        sum += digit * digit
        n //= 10
    return sum

def ishappy(n):
    19
    seen = set()
    while n != 1 and n not in seen:
        seen.add(n)
        n = sum(n)
    return n == 1


n = int(input("Input:"))
print("Output:",ishappy(n))