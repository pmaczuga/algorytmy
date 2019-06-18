import sys
import re

def main():
    filename = sys.argv[1]
    if len(sys.argv) >= 3:
    	max_moves = int(sys.argv[2])
    else:
    	max_moves = 10
    f = open(filename)
    for i in range(3):
        f.readline()
    params = re.split("\s*:\s*", f.readline())
    dims = params[-1][:-1].split("x")
    width = int(dims[0])
    height = int(dims[1])
    for i in range(2):
        f.readline()
    content = re.split("\s*:\s*", f.readline())[-1][:-1]
    
    save_file = open(filename.split(".")[0] + ".txt", "w+")
    save_file.write("{} {}\n".format(height+2, width+2))
    save_file.write("{}\n".format(max_moves))

    for x in range(width + 2):
        save_file.write("#")
    save_file.write("\n")

    x = 0
    y = 0
    for char in content:
        if x == width:
            x = 0
            y += 1
            save_file.write("#\n")
        if x == 0:
            save_file.write("#")

        if char == "w":
            save_file.write("#")
        elif char == "b":
            save_file.write(" ")
        elif char == "g":
            save_file.write("+")
        elif char == "m":
            save_file.write("*")
        elif char == "s":
            save_file.write("O")
        elif char == "S":
            save_file.write(".")
        else:
            print("Problem!!!")
        x += 1
    
    save_file.write("#\n")
    for x in range(width + 2):
        save_file.write("#")

if __name__ == "__main__":
    main()