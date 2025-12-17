import os


def parse(raw: str) -> list[list[int]]:
    out:list[list[int]] = []
    data = raw.split(',')
    for d in data:
        a,b = d.split('-')
        out.append([int(a),int(b)])

    return out
def is_twise(d:int) -> bool:   
    sd = str(d)
    if len(sd) & 1:
        return False
    mid = len(sd) // 2
    if sd[mid:] == sd[:mid]:
        return True
    return False
def part1(data:list[list[int]]):
    total = 0
    for ranges in data:
        for r in range(ranges[0],ranges[1] +1):
            if is_twise(r):
                total += r
    print(total)

def is_repeating(data:int) -> bool:
    sd = str(data)
    if len(sd) == 1:
        return False
    if len(sd) == 2 and sd == sd[::-1]:
        return True
    elif len(sd) ==2:
        return False

    sd_len = len(sd)
    search = sd[0]

    for i in range(1,sd_len):
        # if sd_len % i != 0:
        #     return False
        if (search * (sd_len//i)) == sd:
            return True
        search += sd[i]
    # print({last_match, search, sd})
    return False


def part2(data:list[list[int]]):
    # print([is_repeating(x) for x in (1,1212,2,44,55,234234234,234234234,432423432,12312)])

    total = 0
    for ranges in data:
        for r in range(ranges[0],ranges[1] +1):
            if is_repeating(r):
                # print(f"invalid: {r:15}")
                total += r
            else:
                # print(f"valid  : {r:15}")
                ...
    print(f'{total}')
    



if __name__ == "__main__":
    dir = os.path.dirname(__file__) + "/data.txt"
    with open(dir, "r") as file:
        part2(parse(file.read()))
else:
    test = (
        "11-22,95-115,998-1012,1188511"
        "880-1188511890,222220-222224,"
        "1698522-1698528,446443-446449"
        ",38593856-38593862,565653-565"
        "659,824824821-824824827,21212"
        "12118-2121212124"
    )
    d = (parse(test))
    part2(d)
