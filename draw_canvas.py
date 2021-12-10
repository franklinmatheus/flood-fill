import matplotlib.pyplot as plt

input = "data_canvas/data2.txt"
output = "data_canvas/3-3data2.txt"

indata = open(input, "r", encoding="utf8").read()
outdata = open(output, "r", encoding="utf8").read()

inmatrix = [list(map(int, line.strip().split())) for line in indata.split('\n') if line != ""]
outmatrix = [list(map(int, line.strip().split())) for line in outdata.split('\n') if line != ""]

fig, ax = plt.subplots(figsize=(5,5))
plt.imshow(inmatrix, cmap="gray", interpolation="none")
plt.axis('off')
fig.savefig("images_canvas/in" + input.split("/")[1].split(".")[0] + ".png", dpi=fig.dpi)

plt.imshow(outmatrix, cmap="gray", interpolation="none")
fig.savefig("images_canvas/out" + output.split("/")[1].split(".")[0] + ".png", dpi=fig.dpi)