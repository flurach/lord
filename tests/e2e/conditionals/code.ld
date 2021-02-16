fn doSomething x y =
	x * y / 2

fn main =
	# if-else statements
	if doSomething 5 10 == 5
		print "First if"
	else if doSomething 10 10 == 5
		print "Second if"
	else
		pass
