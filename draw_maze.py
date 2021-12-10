import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

index = 4

input = "data_maze/data"+str(index)+".txt"
output = "data_maze/outdata"+str(index)+".txt"

indata = open(input, "r", encoding="utf8").read().replace('.','0').replace('#','1').replace('@','2').replace('$','3')
outdata = open(output, "r", encoding="utf8").read().replace('.','0').replace('#','1').replace('@','2').replace('$','3').replace('*','4')

inmatrix = [list(map(int, line.strip().split())) for line in indata.split('\n') if line != ""]
outmatrix = [list(map(int, line.strip().split())) for line in outdata.split('\n') if line != ""]

cmap = ListedColormap(['white','black','red','green'])
fig, ax = plt.subplots(figsize=(5,5))
plt.imshow(inmatrix, cmap=cmap, interpolation="none")
#plt.axis('off')
plt.tick_params(axis='x',which='both',bottom=False,top=False,labelbottom=False)
plt.tick_params(axis='y',which='both',left=False,right=False,labelleft=False)
fig.savefig("images_maze/in" + input.split("/")[1].split(".")[0] + ".png", dpi=fig.dpi)


cmap = ListedColormap(['white','black','red','green','blue'])
plt.imshow(outmatrix, cmap=cmap, interpolation="none")
fig.savefig("images_maze/out" + output.split("/")[1].split(".")[0] + ".png", dpi=fig.dpi)