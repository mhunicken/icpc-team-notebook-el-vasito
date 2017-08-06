# tester for cf 101021A (guess a number, queries: is it >=k?)
import random
import subprocess as sp
seed = random.randint(0, sys.maxint);random.seed(seed)
n=random.randint(1,1000000)
try:
	p=sp.Popen(['./a.out'],stdin=sp.PIPE,stdout=sp.PIPE)
	it=0
	s=p.stdout.readline()
	while it<25 and s and s[0]!='!':
		k=int(s)
		assert k>=1 and k<=1000000
		if n>=k: p.stdin.write('>=\n')
		else: p.stdin.write('<\n')
		s=p.stdout.readline()
		it+=1
	assert s and s[0]=='!'
	k=int(s.split()[1])
	assert k==n
except:
	print 'failed with seed %s' % seed
	raise
