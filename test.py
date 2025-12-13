#!/usr/bin/env python3

import subprocess
import numpy as np
import glob
import os

domain_size = 150000
gravity = 9.81
bavg = -5000
method = 'rk4'

wave_speed = np.sqrt(gravity * np.abs(bavg))
period = domain_size / wave_speed

print("Wave speed:", wave_speed)
print("Period:", period)

for f in glob.glob('data/output_state_*.txt'):
    os.remove(f)

cmd = './out/main --domain-size ' + str(domain_size) + ' --num-dofs 512 --gravity ' + str(gravity) + ' --bavg ' + str(bavg) + ' --simtime ' + str(period) + ' --timestepping-method ' + method + ' --output-freq ' + str(period)

print("Running:", cmd)
os.system(cmd)

files_h = sorted(glob.glob('data/output_state_h_*.txt'))
files_v = sorted(glob.glob('data/output_state_v_*.txt'))

h_init = np.genfromtxt(files_h[0], delimiter='\t')
h_final = np.genfromtxt(files_h[-1], delimiter='\t')
v_init = np.genfromtxt(files_v[0], delimiter='\t')
v_final = np.genfromtxt(files_v[-1], delimiter='\t')

x = h_init[:, 0]
dx = x[1] - x[0]

diff_h = h_final[:, 1] - h_init[:, 1]
diff_v = v_final[:, 1] - v_init[:, 1]

l2_h = np.sqrt(np.sum(diff_h**2) * dx)
l2_v = np.sqrt(np.sum(diff_v**2) * dx)

print("L2 error h:", l2_h)
print("L2 error v:", l2_v)