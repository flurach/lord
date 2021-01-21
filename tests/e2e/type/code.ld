# data types

struct SampleStruct =
	_i64: i64

fn SampleStruct.print self =
	self._i64 * self._i64 |> printf "%d\n"

fn main =
	sample = SampleStruct { _i64: 10 }
	sample.print
