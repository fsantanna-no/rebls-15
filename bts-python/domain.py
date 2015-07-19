"""
Adapted from: https://metakatie.wordpress.com/2008/09/13/2d-animation-example-with-tkinter/
Adapted from: http://hopper.unco.edu/course/CS101/S07/lab7.html
"""

# Displays a circle bouncing around the canvas window.
from Tkinter import *
import math

from par import *
from seq import *

root = Tk()
canvas = Canvas(root, width = 400, height = 300)
canvas.pack()

def blend(a, b, f):
    return b * f + a * (1 - f)

def do_nothing():
    pass

class Tween:
    def __init__(self, canvas, tag, dest, duration):
        self.canvas = canvas
        self.tag = tag
        self.dest = dest
        self.duration = duration

    def start(self, done_callback):
        self.done_callback = done_callback
        self.start = self.canvas.coords(self.tag)
        self.fraction = 0.0

    def event(self, to_handle):
        assert to_handle == self.tag
        if self.fraction < 1.0:
            x0 = blend(self.start[0], self.dest[0], self.fraction)
            y0 = blend(self.start[1], self.dest[1], self.fraction)
            x1 = blend(self.start[2], self.dest[2], self.fraction)
            y1 = blend(self.start[3], self.dest[3], self.fraction)
            self.canvas.coords(self.tag, x0, y0, x1, y1)
            self.fraction += 0.033 / self.duration
        else:
            self.done_callback()
            self.done_callback = do_nothing

    def resources(self):
        return {self.tag: True}

canvas.create_oval(10, 50, 20, 60, fill = 'red', tag = 'red_ball')
canvas.create_oval(380, 280, 390, 290, fill = 'blue', tag = 'blue_ball')
canvas.update()


tree = Seq([
    Par({
        'left': Seq([
            Tween(canvas, 'blue_ball', (380, 20, 390, 30), 1.0),
            Tween(canvas, 'blue_ball', (50, 10, 60, 20), 1.0)
            ]),
        'right': Seq([
            Tween(canvas, 'red_ball', (380, 20, 390, 30), 1.0),
            Tween(canvas, 'red_ball', (10, 50, 20, 60), 1.0)
            ])
        }),
    Par({
        'left': Tween(canvas, 'blue_ball', (10, 50, 110, 150), 1.0),
        'right': Tween(canvas, 'red_ball', (50, 10, 150, 110), 1.0)
    }),
    Par({
        'left': Tween(canvas, 'red_ball', (10, 50, 20, 60), 1.0),
        'right': Tween(canvas, 'blue_ball', (50, 10, 60, 20), 1.0)
    }),
    Par({
        'left': Seq([
            Tween(canvas, 'blue_ball', (380, 20, 390, 30), 1.0),
            Tween(canvas, 'blue_ball', (380, 280, 390, 290), 1.0)
            ]),
        'right': Seq([
            Tween(canvas, 'red_ball', (380, 20, 390, 30), 1.0),
            Tween(canvas, 'red_ball', (10, 50, 20, 60), 1.0),
            Tween(canvas, 'red_ball', (380, 280, 390, 290), 1.0)
            ])
        }),
    ])

done = False

def all_done():
    global done
    done = True

tree.start(all_done)

def update_and_draw():
    global done
    if not done:
        tree.event('red_ball')
        tree.event('blue_ball')
        root.after(33, update_and_draw)
    else:
        canvas.create_text(200, 150, text='all done')
    canvas.update()

root.after(33, update_and_draw)
root.mainloop()
