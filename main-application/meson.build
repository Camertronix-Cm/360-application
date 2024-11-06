project('gstreamer_opencv_app', 'cpp',
  version: '0.1',
  default_options: ['cpp_std=c++17'])

# Dependencies
gst_dep = dependency('gstreamer-1.0')
gst_app_dep = dependency('gstreamer-app-1.0')
opencv_dep = dependency('opencv4')

# Source files
src = files('src/main.cpp')

# Executable
executable('gstreamer_opencv_app',
  src,
  dependencies: [gst_dep, gst_app_dep, opencv_dep])