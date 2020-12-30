# data types
# PROBLEMATIC

type Rectangle =
	width:  i64
	height: i64

fn Rectangle.area self =
	self.width * self.height

my_rect = Rectangle 5 5
printf "%d\n" my_rect.area
