project "lc"
	kind "SharedLib"
	language "C"

	includedirs {
		"inc",
		(BASE_DIR .. "/lp/inc")
	}
	files { "src/**.c" }
