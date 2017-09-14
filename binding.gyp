{
  "targets": [
    {
      "target_name": "popplonode",
      "sources": [
        "getTextFromPageAsync.cpp",
        "popplonode.cpp",
      ],
      "cflags_cc!": [
        "-fno-exceptions",
      ],
      "cflags_cc": [
        "-fpermissive",
      ],
      "dependencies": [
        "lib/poppler.gypi:libpoppler"
      ],
      "conditions": [
        ["OS=='win'", {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "ExceptionHandling": 1
            }
          },
          "link_settings": {
            "libraries": ["ws2_32.lib"]
          }
        }],
        ["OS=='mac'", {
          "xcode_settings": {
           "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
           'GCC_ENABLE_CPP_RTTI': 'YES'
          }
        }]
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}