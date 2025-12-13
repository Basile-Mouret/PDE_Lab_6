#!/usr/bin/env python3

import numpy as np
import glob
import os
import matplotlib.pyplot as plt

domain_size = 150000
gravity = 9.81
bavg = -5000
method = 'rk4'

wave_speed = np.sqrt(gravity * np.abs(bavg))
period = domain_size / wave_speed

dofs_list = [64, 128, 256, 512, 1024]
errors_h = []
errors_v = []
dx_list = []

for num_dofs in dofs_list:
    for f in glob.glob('data/output_state_*.txt'):
        os.remove(f)

    cmd = './out/main --domain-size ' + str(domain_size) + ' --num-dofs ' + str(num_dofs) + ' --gravity ' + str(gravity) + ' --bavg ' + str(bavg) + ' --simtime ' + str(period) + ' --timestepping-method ' + method + ' --output-freq ' + str(period)
    os.system(cmd)

    files_h = sorted(glob.glob('data/output_state_h_*.txt'))
    files_v = sorted(glob.glob('data/output_state_v_*.txt'))

    h_init = np.genfromtxt(files_h[0], delimiter='\t')
    h_final = np.genfromtxt(files_h[-1], delimiter='\t')
    v_init = np.genfromtxt(files_v[0], delimiter='\t')
    v_final = np.genfromtxt(files_v[-1], delimiter='\t')

    x = h_init[:, 0]
    dx = x[1] - x[0]
    dx_list.append(dx)

    diff_h = h_final[:, 1] - h_init[:, 1]
    diff_v = v_final[:, 1] - v_init[:, 1]

    l2_h = np.sqrt(np.sum(diff_h**2) * dx)
    l2_v = np.sqrt(np.sum(diff_v**2) * dx)

    errors_h.append(l2_h)
    errors_v.append(l2_v)

    print("DOFs:", num_dofs, "dx:", dx, "L2 error h:", l2_h, "L2 error v:", l2_v)

print("\nConvergence orders:")
for i in range(1, len(dofs_list)):
    order_h = np.log(errors_h[i-1] / errors_h[i]) / np.log(2)
    order_v = np.log(errors_v[i-1] / errors_v[i]) / np.log(2)
    print("DOFs", dofs_list[i-1], "->", dofs_list[i], ": order h =", round(order_h, 2), ", order v =", round(order_v, 2))

# plot
plt.figure(figsize=(10, 7))
plt.loglog(dx_list, errors_h, 'o-', label='L2 error h')
plt.loglog(dx_list, errors_v, 's-', label='L2 error v')

# reference lines
dx_ref = np.array(dx_list)
plt.loglog(dx_ref, errors_h[0] * (dx_ref / dx_ref[0])**2, '--', color='gray', label='O(dx^2)')
plt.loglog(dx_ref, errors_h[-1] * (dx_ref / dx_ref[-1])**4, '--', color='black', label='O(dx^4)')

plt.xlabel('dx [m]')
plt.ylabel('L2 Error')
plt.title('Convergence Study - ' + method.upper())
plt.legend()
plt.grid(True)
plt.savefig('convergence.svg')
plt.show()
