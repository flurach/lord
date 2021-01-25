# data types

struct SampleStruct =
	data: i64

fn SampleStruct.print self =
	print (self.sqr)

fn SampleStruct.sqr self =
	self.data * self.data

fn main args =
	sample = SampleStruct { data: 10 }
	sample.print
