with open("input.bin", "rb") as f:
    data = f.read()

start = 0
while True:
    try:
        start = data.index(b"\x4d\x42\x4b", start)
    except ValueError:
        break

    try:
        end = data.index(b"\xff\xd9", start) + 2
    except ValueError:
        break

    with open(f"output_{start}.jpeg", "wb") as f:
        #print(data[start-3:end])
        f.write(b"\xff\xd8\xff" + data[start+3:end])

    start = end


