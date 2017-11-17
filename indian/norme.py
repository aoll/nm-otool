import re

def write_proto(src_file):
	m = re.findall('^[a-z].*',src_file.read(), re.MULTILINE)
	dest_h_file = open('ft_otool.test', 'w')
	for proto in m:
		dest_h_file.write(proto + ';\n')

def write_functions(src_file):

	on = False
	for line in src_file:
		m = re.search('^[a-z].*', line)
		if m:
			# print(m.group(0))
			t = m.group(0).split('(')[0].replace('*', '\t').replace(' ', '\t').split('\t')
			# print(t[len(t) - 1])
			f = open('src/'+t[len(t) - 1]+'.c', 'w')
			on = True
		if on == True:
			f.write(line)
		if line == '}':
			on = False

if __name__ == '__main__':
	src_file = open('main.c', 'r')
	''' write prototype '''
	# write_proto(src_file)
	write_functions(src_file)
