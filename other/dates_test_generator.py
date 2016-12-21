from datetime import date
import random

ntest = 1000000

for i in range(ntest):
	x1=random.randint(1,3652000)
	x2=random.randint(1,3652000)
	d1=date.fromordinal(x1)
	d2=date.fromordinal(x2)
	print d1.year,d1.month,d1.day,d2.year,d2.month,d2.day,x2-x1

