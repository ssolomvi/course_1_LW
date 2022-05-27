import string
import random

ref_file = open("deutsch", "r")
new_file = open("test.txt", "w+")

template = '{key} {data}\n'

entries = ref_file.readlines()
random_keys = [(''.join(random.choice(string.ascii_lowercase) for _ in range(6))) for i in range(len(entries))]
random_keys.sort()

for i in range(len(entries)):
    new_file.write(template.format(**{'key': ''.join(random_keys[i]),
                                      'data': ''.join(entries[i].replace(' ', '_').replace('\n', ''))}))

ref_file.close()
new_file.close()
