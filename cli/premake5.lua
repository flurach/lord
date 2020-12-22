project "cli"
	kind "ConsoleApp"
	language "C"
	targetname "lord"

	includedirs {
		"inc",
		(BASE_DIR .. "/lc/inc"),
		(BASE_DIR .. "/vm/inc"),
	}
	files { "src/**.c" }
	links { "lc", "vm" }
