function build($step) {
    New-Item -ItemType Directory -Path "build" -ErrorAction Ignore
    Push-Location "build"
    cmake .. -G"Ninja" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DSTEP="$step"
    cmake --build .
    Copy-Item -Path "compile_commands.json" -Destination ".." -Force -ErrorAction Ignore
    Pop-Location
  }

function clean {
    Remove-Item -Path "build" -Recurse -Force
  }

function run($step) {
    build($step)
    ./build/mylisp
  }

if ($args[0]){
    switch($args[0]){
        "build" {
          if ($args[1]) {
            build($args[1])
          }
        }
        "clean" {clean}
        "run"   {
          if ($args[1]) {
             run($args[1])
          }
        }
        default {Write-Output "command not valid"}
      }
    }
  
