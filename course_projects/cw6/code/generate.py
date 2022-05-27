import random
import string
import names


def randomword(length):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for j in range(length)) + ' '


my_file = open("test3.txt", "w+")

Letters = string.ascii_uppercase

for q in range(random.randint(10, 16)):
    rand = random.randint(1, 6)
    my_file.write(names.get_last_name() + ' ')
    OS = ["Windows", "MacOS", "Linux"]  # OS
    my_file.write(random.choice(OS) + ' ')
    my_file.write(str(rand * 2) + ' ')  # num_cpu
    my_file.write(randomword(random.randint(6, 8)))  # cpu_name
    my_file.write(str(1300 * rand) + ' ')  # cpu_freq
    gpu = ["Integrated", "Exterior", "AGP", "PCI"]  # gpu_name
    my_file.write(random.choice(gpu) + ' ')
    my_file.write(str(rand * 2000) + ' ')  # gpu_memory
    hdd = ["SCSI", "IDE", "ATA", "SATA"]
    num = random.randint(1, 6)  # num_hdd
    my_file.write(str(num) + ' ')
    for s in range(num):
        my_file.write(random.choice(hdd) + ' ')
        my_file.write(str(250 * rand) + ' ')
    my_file.write(str(rand * 4 + 2) + ' ')  # ram
    my_file.write(str(rand) + '\n')  # num_of_exterior_dev


my_file.close()
