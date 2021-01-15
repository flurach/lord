# data types

struct SampleStruct =
	_i8:  i8
	_i16: i16
	_i32: i32
	_i64: i64
	_u8:  u8
	_u16: u16
	_u32: u32
	_u64: u64
	_f32: f32
	_f64: f64
	_struct: SmallStruct

	builtin_ptr: [i8]
	custom_ptr:  [SmallStruct]

	arr:     i64[10]
	twoDarr: i64[10][10]
	pArr:    [i64][10][10]

	fnptr: [i64 -> i64]

fn SampleStruct.print self =
	self.fnptr self._i64 |> printf "%d\n"

struct SmallStruct =
	hey: [u8]

fn main =
	sample = SampleStruct { _i64: 10 }
	sample.print
