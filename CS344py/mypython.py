import random
def generate_random():
    x = "";
	#initializes the values of ascii integers
    arr = [0,0,0,0,0,0,0,0,0,0];
	#sets all of the ascii values to be converted to strings later
    for i in range(10):
        y = random.randint(97,122);
        arr[i] = y;
	#appends the character conversions of the ascii integers to a string
    newstr = x.join([chr(y) for y in arr]);
    return newstr;

def create_files():
	#creates and opens a file object, generates a random string of size 10, and writes it to the file.
    fileobj = open("file1", "w");
    a = generate_random();
    fileobj.write(a);
    fileobj.close();
	#creates and opens a file object, generates a random string of size 10, and writes it to the file.
    fileobj2 = open("file2", "w");
    b = generate_random();
    fileobj2.write(b);
    fileobj2.close();
	#creates and opens a file object, generates a random string of size 10, and writes it to the file.
    fileobj3 = open("file3", "w");
    c = generate_random();
    fileobj3.write(c);
    fileobj3.close();
    #prints contents of the files
    print(a);
    print(b);
    print(c);
def intprods():
	#sets 2 random integers between 1 and 42
    a = random.randint(1,42);
    b = random.randint(1,42);
	#prints out the integers  
    print(a);
    print(b);
	#takes the integers and computes their product and prints it out 
    c = a * b;
    print("product:", c);
#function calls
create_files();
intprods();