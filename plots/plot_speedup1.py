import pandas as pd
import matplotlib.pyplot as plt


fname = "pt1.txt"
df = pd.read_csv(fname, comment="#")
print(df)

var_names = list(df.columns)

print("var names =", var_names)

# split the df into individual vars
# assumption: there are 3 columns of numbers in the input file

problem_sizes = df[var_names[0]].values.tolist()
O0 = df[var_names[1]].values.tolist()
O3 = df[var_names[2]].values.tolist()

plt.title("Basic MVM vs BLAS MVM")

xlocs = [i for i in range(len(problem_sizes))]

#Scientific Notation for X-axis
plt.xticks(xlocs, ['{:.3e}'.format(x) for x in problem_sizes])

plt.plot(O0, "r-+")
plt.plot(O3, "b-x")

#plt.xscale("log")
plt.yscale("log")

plt.xlabel("Problem Sizes")
plt.ylabel("MFlops per Second")

varNames = [var_names[1], var_names[2]]
plt.legend(varNames, loc="best")

plt.grid(axis='both')

plt.show()

# EOF
