{
  "targets": [
    {
      "target_name": "libpoppler",
      "type": "static_library",
      "cflags": [ "-w" ],
      "defines": [
        "BUILDING_POPPLER=1"
      ],
      "sources": [
        # From PODOFO_BASE_SOURCES
        "poppler/cpp/poppler-document.cpp",
        "poppler/cpp/poppler-embedded-file.cpp",
        "poppler/cpp/poppler-font.cpp",
        "poppler/cpp/poppler-global.cpp",
        "poppler/cpp/poppler-image.cpp",
        "poppler/cpp/poppler-page-renderer.cpp",
        "poppler/cpp/poppler-page-transition.cpp",
        "poppler/cpp/poppler-page.cpp",
        "poppler/cpp/poppler-private.cpp",
        "poppler/cpp/poppler-rectangle.cpp",
        "poppler/cpp/poppler-toc.cpp",
        "poppler/cpp/poppler-version.cpp",
        "poppler/goo/gfile.cc",
        "poppler/goo/gmempp.cc",
        "poppler/goo/GooHash.cc",
        "poppler/goo/GooList.cc",
        "poppler/goo/GooTimer.cc",
        "poppler/goo/GooString.cc",
        "poppler/goo/gmem.cc",
        "poppler/goo/FixedPoint.cc",
        "poppler/goo/NetPBMWriter.cc",
        "poppler/goo/PNGWriter.cc",
        "poppler/goo/TiffWriter.cc",
        "poppler/goo/JpegWriter.cc",
        "poppler/goo/ImgWriter.cc",
        "poppler/goo/gstrtod.cc",
        "poppler/goo/grandom.cc",
        "poppler/goo/glibc.cc",
        "poppler/fofi/FoFiBase.cc",
        "poppler/fofi/FoFiEncodings.cc",
        "poppler/fofi/FoFiTrueType.cc",
        "poppler/fofi/FoFiType1.cc",
        "poppler/fofi/FoFiType1C.cc",
        "poppler/fofi/FoFiIdentifier.cc",
        "poppler/poppler/Annot.cc",
        "poppler/poppler/Array.cc",
        "poppler/poppler/BuiltinFont.cc",
        "poppler/poppler/BuiltinFontTables.cc",
        "poppler/poppler/CachedFile.cc",
        "poppler/poppler/Catalog.cc",
        "poppler/poppler/CharCodeToUnicode.cc",
        "poppler/poppler/CMap.cc",
        "poppler/poppler/DateInfo.cc",
        "poppler/poppler/Decrypt.cc",
        "poppler/poppler/Dict.cc",
        "poppler/poppler/Error.cc",
        "poppler/poppler/FileSpec.cc",
        "poppler/poppler/FontEncodingTables.cc",
        "poppler/poppler/Form.cc",
        "poppler/poppler/FontInfo.cc",
        "poppler/poppler/Function.cc",
        "poppler/poppler/Gfx.cc",
        "poppler/poppler/GfxFont.cc",
        "poppler/poppler/GfxState.cc",
        "poppler/poppler/GlobalParams.cc",
        "poppler/poppler/Hints.cc",
        "poppler/poppler/JArithmeticDecoder.cc",
        "poppler/poppler/JBIG2Stream.cc",
        "poppler/poppler/Lexer.cc",
        "poppler/poppler/Link.cc",
        "poppler/poppler/Linearization.cc",
        "poppler/poppler/LocalPDFDocBuilder.cc",
        "poppler/poppler/MarkedContentOutputDev.cc",
        "poppler/poppler/NameToCharCode.cc",
        "poppler/poppler/Object.cc",
        "poppler/poppler/OptionalContent.cc",
        "poppler/poppler/Outline.cc",
        "poppler/poppler/OutputDev.cc",
        "poppler/poppler/Page.cc",
        "poppler/poppler/PageTransition.cc",
        "poppler/poppler/Parser.cc",
        "poppler/poppler/PDFDoc.cc",
        "poppler/poppler/PDFDocEncoding.cc",
        "poppler/poppler/PDFDocFactory.cc",
        "poppler/poppler/PopplerCache.cc",
        "poppler/poppler/ProfileData.cc",
        "poppler/poppler/PreScanOutputDev.cc",
        "poppler/poppler/PSTokenizer.cc",
        "poppler/poppler/SignatureInfo.cc",
        "poppler/poppler/Stream.cc",
        "poppler/poppler/StructTreeRoot.cc",
        "poppler/poppler/StructElement.cc",
        "poppler/poppler/strtok_r.cpp",
        "poppler/poppler/UnicodeMap.cc",
        "poppler/poppler/UnicodeTypeTable.cc",
        "poppler/poppler/UTF.cc",
        "poppler/poppler/XRef.cc",
        "poppler/poppler/PSOutputDev.cc",
        "poppler/poppler/TextOutputDev.cc",
        "poppler/poppler/PageLabelInfo.cc",
        "poppler/poppler/SecurityHandler.cc",
        "poppler/poppler/StdinCachedFile.cc",
        "poppler/poppler/StdinPDFDocBuilder.cc",
        "poppler/poppler/Sound.cc",
        "poppler/poppler/ViewerPreferences.cc",
        "poppler/poppler/XpdfPluginAPI.cc",
        "poppler/poppler/Movie.cc",
        "poppler/poppler/Rendition.cc"
      ],
      "conditions": [
        ["OS=='win'", {
          "cflags": [
            "/EHsc"
          ]
        }],
        ["OS=='linux'", {
          "cflags_cc!": [
            "-fno-exceptions",
            "-fno-rtti"
          ],
          "cflags_cc": [
            "-fpermissive",
          ]
        }],
        ["OS=='mac'", {
          "OTHER_CPLUSPLUSFLAGS" : [ "-std=c++11", "-stdlib=libc++" ],
          "OTHER_LDFLAGS": [ "-stdlib=libc++" ],
          "cflags_cc!": [
            "-fno-exceptions"
          ],
          "xcode_settings": {
           "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
           "GCC_ENABLE_CPP_RTTI": "YES"
          }
        }]
      ],
      "configurations": {
        "Release": {
          "msvs_settings": {
            "VCCLCompilerTool": {
              "RuntimeTypeInfo": "true"
            }
          }
        }
      },
      "msvs_settings": {
        "VCCLCompilerTool": {
          "ExceptionHandling": 1
        }
      },
      "include_dirs": [
        "poppler/poppler/",
        "poppler/cpp/",
        "poppler/goo",
        "poppler/fofi",
        "poppler/",
        "overrides/<(OS)/<(target_arch)/"
      ],
      "direct_dependent_settings": {
        "include_dirs": [
          "poppler/poppler/",
          "poppler/cpp/",
          "poppler/goo",
          "poppler/fofi",
          "poppler/",
          "overrides/<(OS)/<(target_arch)/"
        ]
      }
    }
  ]
}