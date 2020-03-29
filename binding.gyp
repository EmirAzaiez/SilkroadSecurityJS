{
  "targets": [
    {
      "target_name": "SilkroadSecurityJS",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./src/SilkroadSecurity/blowfish.cpp",
        "./src/SilkroadSecurity/silkroad_security.cpp",
        "./src/SilkroadSecurity/stream_utility.cpp",

        "./src/SilkroadSecurityJS.cpp",
        "./src/main.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "libraries": [],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}