import os
from typing import Any, SupportsIndex, overload

def parse(raw: str) -> list[str]:
    return raw.strip().splitlines()


def part1(back_array: list[str]):
    
    total = 0
    for banks in back_array:
        l_largest_index = 0

        for i in range(len(banks)-1):
            
            if banks[i] > banks[l_largest_index]:
                l_largest_index = i

        r_largest_index = l_largest_index + 1
        for i in range(l_largest_index,len(banks)):
            if i == l_largest_index:
                continue
            if banks[i] > banks[r_largest_index]:
                r_largest_index = i
        total += int(banks[l_largest_index]+ banks[r_largest_index])

    print(total)

def part2(bank_array: list[str]):
    def optimize_bank(bank:str, size=12) -> str:
        if size == 0:
            return ""
        max_val = max(bank[:len(bank) - size + 1])
        return max_val + optimize_bank(bank[bank.index(max_val)+1:],size-1)
    total = 0

    for bank in bank_array:
        total += int(optimize_bank(bank))

    print(total)



test = 0
if __name__ == "__main__" and not test:
    dir = os.path.dirname(__file__) + "/data.txt"
    with open(dir, "r") as file:
        data = parse(file.read())
        part2(data)
else:
    data = parse("987654321111111\n"+
    "811111111111119\n"+
    "234234234234278\n"+
    "818181911112111")
    part2(data)


