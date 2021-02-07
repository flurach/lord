# data types

struct SampleStruct =
	data: i64

fn SampleStruct.print self =
	result = self.sqr
	print result

fn SampleStruct.sqr self =
	result = self.data * self.data
	result

fn main args =
	sample = SampleStruct { data: 10 }
	sample.print
