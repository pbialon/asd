import string, random
import subprocess

def generate_string():
	size = random.randint(1, 50)
	chars = string.ascii_uppercase + '********************************'
	return (''.join(random.choice(chars) for _ in range(size))).encode(encoding='UTF-8')

def print_error(other, my, input):
	print("Error on input: " + input)
	print("First output: " + other)
	print("Second output: " + my)


def test(i, n): 
	s = generate_string()
	my = subprocess.Popen(['./matryca2'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	my_output = my.communicate(s)[0].decode(encoding='UTF-8')
	other = subprocess.Popen(['./matryca-old'], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	other_output = other.communicate(s)[0].decode(encoding='UTF-8')
	s = s.decode(encoding='UTF-8')
	if other_output != my_output:
		print_error(other_output, my_output, s)
	elif i % 100 == 0:
		print(i)



if __name__ == "__main__":
	n = 10000
	for i in range(1, n):
		test(i, n)