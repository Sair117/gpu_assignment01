import subprocess
import time
import matplotlib.pyplot as plt
import os

CPU_EXE = r"D:\STUDY\GPU\assignment01\task02\matrix_add.exe"
GPU_EXE = r"D:\STUDY\GPU\assignment01\task03\task03.exe"
# Define matrix sizes to test (N x N)
sizes = [128, 256, 512, 1024, 2048, 4096]
cpu_times = []
gpu_times = []

def generate_test_file(n):
    with open("temp_input.txt", "w") as f:
        # Matrix A header and data
        f.write(f"{n} {n}\n")
        f.write(" ".join(["1.0"] * (n * n)) + "\n")
        # Matrix B header and data
        f.write(f"{n} {n}\n")
        f.write(" ".join(["2.0"] * (n * n)) + "\n")

for n in sizes:
    print(f"Testing size: {n}x{n}...")
    generate_test_file(n)
    
    # Run CPU Task
    cpu_res = subprocess.check_output([CPU_EXE, "temp_input.txt"], shell=True)
    cpu_times.append(float(cpu_res.decode().strip()))
    
    # Run GPU Task
    gpu_res = subprocess.check_output([GPU_EXE, "temp_input.txt"], shell=True)
    gpu_times.append(float(gpu_res.decode().strip()))

# Plotting the results
plt.figure(figsize=(10, 6))
plt.plot(sizes, cpu_times, label='CPU (Task 02)', marker='o')
plt.plot(sizes, gpu_times, label='GPU (Task 03)', marker='s')
plt.xlabel('Matrix Size (N x N)')
plt.ylabel('Time (ms)')
plt.title('Matrix Addition: CPU vs GPU (RTX 2050)')
plt.legend()
plt.grid(True)
plt.savefig('performance_graph.png')
plt.show()