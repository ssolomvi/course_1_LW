import random

my_file = open("test1.txt", "w+")
height = random.randint(2, 10)
width = random.randint(2, 10)

variety = random.randint(15, 21)

mat = [[str(random.choices([0, (random.randint(1, 10))], weights=[100 - variety, variety]))
        for j in range(width)] for i in range(height)]

for row in mat:
    row = str(row).replace("[", "").replace("]", "").replace("'", "").replace(",", "")
    my_file.write(row + "\n")

my_file.close()
