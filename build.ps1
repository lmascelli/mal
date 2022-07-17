function build {
    New-Item -ItemType Directory -Path "build" -ErrorAction Ignore
    Push-Location "build"
    cmake .. -G"Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
    cmake --build .
    Copy-Item -Path "compile_commands.json" -Destination ".." -Force -ErrorAction Ignore
    Pop-Location
  }

function clean {
    Remove-Item -Path "build" -Recurse -Force
  }

function run {
    build
    ./build/mylisp
  }

if ($args[0]){
    switch($args[0]){
        "build" {build}
        "clean" {clean}
        "run"   {run}
        default {Write-Output "command not valid"}
      }
  }