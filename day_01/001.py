import os
from pathlib import Path

class Lock:
    
    def __init__(self,starting = 0, hrange=99):
        self.range = hrange + 1
        self.val = starting
        self.password = 0
    def check(self):
        if self.val:
            return
        self.password += 1
    def inc(self, step = 1):
        self.val = (self.val + step) % self.range
    def dec(self, step = 1):
        self.val = (self.val - step) % self.range
    def l(self, step = 1): # type: ignore
        self.dec(step)
        self.check()
    def r(self, step = 1):
        self.inc(step)
        self.check()


def unlock(path:str):
    data:list[str] = []
    c = Lock(50)
    with open(path, "r") as file:
        data = file.read().strip().splitlines()
    for direction, *d in data:
        print(direction, d)
        if direction.lower() == "l":
            c.l(int(''.join(d)) or 1)
        else:
            c.r(int(''.join(d)) or 1)
    print(c.password)



if __name__ == "__main__":
    dir = os.path.dirname(__file__)
    
    unlock(dir + "/data.txt")
else:
    c = Lock(50)
    c.l(68)
    c.l(30)
    c.r(48)
    c.l(5)
    c.r(60)
    c.l(55)
    c.l(1)
    c.l(99)
    c.r(14)
    c.l(82)
    print(c.password)
