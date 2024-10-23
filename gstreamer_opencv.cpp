#include <gst/gst.h>
#include <opencv2/opencv.hpp>

using namespace cv;

GstElement *pipeline1, *pipeline2, *appsrc1, *appsrc2, *appsink1, *appsink2;
Mat frame1, frame2, concatenatedFrame;

/* Function to extract frames from GStreamer appsrc */
void extract_frame(GstElement *appsink, Mat &frame) {
    GstSample *sample;
    GstCaps *caps;
    GstBuffer *buffer;
    GstMapInfo map;

    sample = gst_app_sink_pull_sample(appsink);
    if (sample) {
        caps = gst_sample_get_caps(sample);
        buffer = gst_sample_get_buffer(sample);
        if (buffer) {
            gst_buffer_map(buffer, &map, GST_MAP_READ);

            // Convert the buffer to OpenCV Mat (assuming 640x480 resolution, modify as necessary)
            frame = Mat(480, 640, CV_8UC3, (char *)map.data).clone();

            gst_buffer_unmap(buffer, &map);
        }
        gst_sample_unref(sample);
    }
}

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    // Create two pipelines for capturing video from two different cameras
    pipeline1 = gst_parse_launch("autovideosrc ! video/x-raw,format=BGR,width=640,height=480 ! appsink name=appsink1", NULL);
    pipeline2 = gst_parse_launch("autovideosrc ! video/x-raw,format=BGR,width=640,height=480 ! appsink name=appsink2", NULL);

    // Get references to the appsink elements
    appsink1 = gst_bin_get_by_name(GST_BIN(pipeline1), "appsink1");
    appsink2 = gst_bin_get_by_name(GST_BIN(pipeline2), "appsink2");

    // Start the GStreamer pipelines
    gst_element_set_state(pipeline1, GST_STATE_PLAYING);
    gst_element_set_state(pipeline2, GST_STATE_PLAYING);

    // OpenCV window
    namedWindow("Concatenated Output", WINDOW_AUTOSIZE);

    while (true) {
        // Extract frames from both video streams
        extract_frame(appsink1, frame1);
        extract_frame(appsink2, frame2);

        if (!frame1.empty() && !frame2.empty()) {
            // Concatenate frames horizontally
            hconcat(frame1, frame2, concatenatedFrame);

            // Display the concatenated frame
            imshow("Concatenated Output", concatenatedFrame);

            // Break the loop on 'q' key press
            if (waitKey(10) == 'q') {
                break;
            }
        }
    }

    // Stop the pipelines and clean up
    gst_element_set_state(pipeline1, GST_STATE_NULL);
    gst_element_set_state(pipeline2, GST_STATE_NULL);
    gst_object_unref(pipeline1);
    gst_object_unref(pipeline2);
    destroyAllWindows();

    return 0;
}
