import matplotlib.pyplot as plt
import numpy as np

# Define the input size (n)
n = np.linspace(1, 100, 100)

# Define the Big O functions
O_1 = np.ones(len(n))
O_logn = np.log2(n)
O_n = n
O_nlogn = n * np.log2(n)
O_n2 = n**2
O_2n = 2**n

# Create the plot
plt.figure(figsize=(10, 8))
plt.plot(n, O_2n, label='O(2^n)', linestyle=(0,(5,10)))
plt.plot(n, O_n2, label='O(n^2)', linestyle='solid')
plt.plot(n, O_nlogn, label='O(n log n)', linestyle='dashdot')
plt.plot(n, O_n, label='O(n)', linestyle='dashed')
plt.plot(n, O_logn, label='O(log n)', linestyle='dotted')
plt.plot(n, O_1, label='O(1)', linestyle='solid')

# Customize the plot
plt.xlabel('Input size (n)')
plt.ylabel('Time complexity')
plt.title('Comparison of Algorithm Complexities in Big O Notation')
plt.legend()
plt.ylim(0, 100)
plt.grid(True)
# plt.yscale('log')  # Use logarithmic scale for better visualization

# Display the plot
# plt.tight_layout()
plt.savefig("complexity_graph.png")
plt.show()