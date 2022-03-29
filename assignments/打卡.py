from pymouse import PyMouse
from time import sleep


def apply(m):
    sleep(0.1)
    m.click(1920-144,250)
    sleep(2)
    m.click(1920-293,383)
    sleep(0.1)

m=PyMouse()
x,y=(1920-599,350)
x1,y1=(x+100,y)
x3,y3=(x,y+100)
x2,y2=(x-100,y)
x4,y4=(x,y-100)

for __ in range(6):
    for _ in range(4):
        m.click(x1,y1)
        apply(m)
    for _ in range(4):
        m.click(x2,y2)
        apply(m)
    for _ in range(4):
        m.click(x3,y3)
        apply(m)
    for _ in range(4):
        m.click(x4,y4)
        apply(m)

        
