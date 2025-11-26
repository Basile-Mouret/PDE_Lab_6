#! /usr/bin/env python3

import sys
import glob
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation


files = glob.glob('data/output_state_h_*.txt')
files.sort()


# Get figure handle
fig, ax = plt.subplots(1, 1, figsize=(12, 8))

# Create dummy line
line1, = ax.plot([], [], color='tab:blue',  label='$h(x)$: Perturbed surface height')
line2, = ax.plot([], [], color='tab:red',   label='$v(x)$: Velocity', linestyle='--')
line3, = ax.plot([], [], color='tab:green', label='$b(x)$: Bathymetry')

title = ax.set_title('XXX')

ax.set(xlabel='$x [m]$', ylabel='numerical approximation of $h(x)$, $v(h) [m]$')
ax.legend(loc='lower left')
fig.tight_layout()


def extend_xlim(x):
    """
    Extend the xlimits to be able to represent all values in x
    """
    min_x = np.min(x)
    max_x = np.max(x)

    min_x -= (max_x-min_x)*0.1
    max_x += (max_x-min_x)*0.1

    ax.set_xlim(min(min_x, ax.get_xlim()[0]), max(max_x, ax.get_xlim()[1]))


def extend_ylim(y):
    """
    Extend the ylimits to be able to represent all values in y
    """
    min_y = np.min(y)
    max_y = np.max(y)


    delta = (max_y-min_y)*0.1
    if delta == 0:
        delta = max(np.max(np.abs(min_y)), np.max(np.abs(max_y)))*0.1

    assert delta >= 0

    min_y -= delta
    max_y += delta

    max_y = max(max_y, ax.get_ylim()[1])
    min_y = min(min_y, ax.get_ylim()[0])

    ax.set_ylim(min_y, max_y)


def load_data(filename, frame):

    data_h = np.genfromtxt(filename, delimiter='\t')
    data_v = np.genfromtxt(filename.replace('state_h', 'state_v'), delimiter='\t')
    data_b = np.genfromtxt(filename.replace('state_h', 'state_b'), delimiter='\t')

    data_h_mabs = np.max(np.abs(data_h[:,1]))
    data_v_mabs = np.max(np.abs(data_v[:,1]))
    data_b_mabs = np.max(np.abs(data_b[:,1]))

    if data_h_mabs == 0:
        data_h_mabs = 1e-10
    if data_v_mabs == 0:
        data_v_mabs = 1e-10
    if data_b_mabs == 0:
        data_b_mabs = 1e-10

    # Render 'h', 'v', 'b' fields
    xs = data_h[:,0], data_v[:,0], data_b[:,0]
    ys = data_h[:,1], data_v[:,1], data_b[:,1]



    # Amlify h, v perturbation fields to keep things visible
    y_h, y_v, _ = ys
    y_h *= data_b_mabs / data_h_mabs * 0.5
    y_v *= data_b_mabs / data_v_mabs * 0.5

    for x, y, line in zip(xs, ys, [line1, line2, line3]):
        line.set_data(x, y)
        extend_xlim(x)
        extend_ylim(y)

    # update title
    time_text = filename.replace('data/output_state_h_', '').replace('.txt', '')
    title.set_text(f'$t=${float(time_text):.2f} s')


# Initialize empty line
def init_func():
    filename = files[0]

    load_data(filename, 0)

    return line1, line2, line3, title,


# Animation function
def animate(i):
    filename = files[i]

    load_data(filename, i)

    return line1, line2, line3, title,



num_frames = len(files)

# Create animation
anim = animation.FuncAnimation(
        fig,
        animate,
        init_func=init_func,
        frames=num_frames,
        interval=int(1000/30),
        blit=False,
        repeat=False
)

plt.show()

