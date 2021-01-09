# data types


type SampleStruct =
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
	arr: i64[10]
	twoDarr: i64[10][10]


type SmallStruct =
	hey: [u8]


fn SampleStruct.area self =
	self._i8 * self._i8


sample = SampleStruct 5 5
printf "%d\n" (sample.area)
