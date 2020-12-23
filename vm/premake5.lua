project "vm"
	kind "SharedLib"
	language "C"

	includedirs { "src" }
	files { "src/**.c" }
