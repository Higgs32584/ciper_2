import sys
import subprocess
import hashlib

result= subprocess.run(['gcc','-Wall','../challenge_2:KDB_files/final.c', '-o','final'],stdout=subprocess.PIPE)
if result.returncode != 0:
    print("GCC compilation failed. Exiting...")
    sys.exit(1)

result_out=subprocess.run(['./final',sys.argv[2],"t"],stdout=subprocess.PIPE)
if result_out.returncode != 0:
    print("Error running the compiled binary. Exiting...")
    sys.exit(1)
MAGIC_bytes = result_out.stdout.decode()
MAGIC_bytes = bytes(MAGIC_bytes, "utf-8")
print(MAGIC_bytes)



with open(sys.argv[1], "rb") as f:
    data = f.read()

start = 0
arr=[]
while True:
    try:
        start = data.index(MAGIC_bytes,start)
        print("found at",start)
    except ValueError:
        break;
    try:
        end = data.index(b"\xff\xd9", start) + 2
    except ValueError:
        break
    value=sys.argv[1].split("/")
    repaired_location= "./"+value[1]+"/"+str(start)+".jpeg"
    print("Size of Image:",end-start,"Location:",start)
    print(repaired_location)
    arr.append(repaired_location)
    with open(repaired_location, "wb") as f:
        f.write(b"\xff\xd8\xff" + data[start+3:end])
    start = end
def MD5_hash(file_name):
    with open(file_name,"rb") as f:
        data = f.read()
        md5hash = hashlib.md5(data).hexdigest()
        print("MD5hash of:",file_name,":",md5hash)

#for arr_file in arr:
  #MD5_hash(arr_file)
