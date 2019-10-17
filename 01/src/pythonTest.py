import subprocess

result = subprocess.run(['./calculator', 'calc 2+3'], stdout=subprocess.PIPE)
assert((result.stdout)==b'5')
assert(result.returncode == 0)
print('test 1 done')


result = subprocess.run(['./calculator', 'calc -2/2 +4--6'], stdout=subprocess.PIPE)
assert((result.stdout)==b'9')
assert(result.returncode == 0)
print('test 2 done')

result = subprocess.run(['./calculator', 'calc -2'], stdout=subprocess.PIPE)
assert((result.stdout)==b'-2')
assert(result.returncode == 0)
print('test 3 done')

result = subprocess.run(['./calculator', 'calc -2/0'], stdout=subprocess.PIPE)
assert((result.stdout)==b'-inf')
assert(result.returncode == 0)
print('test 4 done')

result = subprocess.run(['./calculator', 'calc 1+6/3 --4/2* 10-100'], stdout=subprocess.PIPE)
assert((result.stdout)==b'-77')
assert(result.returncode == 0)
print('test 5 done')

result = subprocess.run(['./calculator', '2+3'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 6 done')

result = subprocess.run(['./calculator', 'calc asd))'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 7 done')

result = subprocess.run(['./calculator', 'calc 2++3'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 8 done')

result = subprocess.run(['./calculator', 'calc 2---3'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 9 done')

result = subprocess.run(['./calculator', 'calc2+3'], stdout=subprocess.PIPE)
assert((result.returncode)!=0)
print('test 10 done')