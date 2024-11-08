GST_DEBUG=3 gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=1920,height=1080 !   videoconvert ! "video/x-raw,format=RGBA" ! videoscale!  fisheye2equi ! nvvidconv ! "video/x-raw(memory:NVMM),format=NV12" ! nvoverlaysink

