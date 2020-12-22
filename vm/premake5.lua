project "vm"
	kind "SharedLib"
	language "C"

	includedirs { "inc" }
	files { "src/**.c" }
