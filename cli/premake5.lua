project "cli"
	kind "ConsoleApp"
	language "C"
	targetname "lord"

	includedirs {
		"inc",
		(BASE_DIR .. "/lord/inc")
	}
	files { "src/**.c" }
	links { "lord" }
