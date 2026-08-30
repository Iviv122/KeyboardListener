with open("in", "r") as file:
    for line in file:
        parts = line.strip().split()
        if len(parts) >= 2 and parts[0] == "#define":
            print("NAME_ELEMENT("+parts[1]+"),")
