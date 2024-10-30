#include <gst/gst.h>
#include <opencv2/opencv.hpp>
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>
#include <iostream>

using namespace cv;
using namespace std;

GstElement *pipeline1, *pipeline2, *appsink1, *appsink2;
Mat frame1, frame2, concatenatedFrame;

void extract_frame(GstElement *appsink, Mat &frame)
{
    GstSample *sample;
    GstCaps *caps;
    GstBuffer *buffer;
    GstMapInfo map;

    cout << "[DEBUG] Trying to pull sample from appsink..." << endl;
    sample = gst_app_sink_pull_sample(GST_APP_SINK(appsink));

    if (sample)
    {
        cout << "[DEBUG] Sample pulled successfully." << endl;
        caps = gst_sample_get_caps(sample);
        if (caps)
        {
            gchar *caps_str = gst_caps_to_string(caps);
            cout << "[DEBUG] Sample caps: " << caps_str << endl;
            g_free(caps_str);
        }
        buffer = gst_sample_get_buffer(sample);
        if (buffer)
        {
            cout << "[DEBUG] Sample buffer found. Mapping buffer..." << endl;
            gst_buffer_map(buffer, &map, GST_MAP_READ);
            cout << "[DEBUG] Buffer mapped, creating Mat..." << endl;
            frame = Mat(1000, 1000, CV_8UC4, (char *)map.data).clone();
            gst_buffer_unmap(buffer, &map);
            cout << "[DEBUG] Frame extracted and copied." << endl;
        }
        else
        {
            cout << "[ERROR] No buffer found in the sample." << endl;
        }
        gst_sample_unref(sample);
    }
    else
    {
        cout << "[ERROR] Failed to pull sample from appsink." << endl;
    }
}

int main(int argc, char *argv[])
{
    cout << "[DEBUG] Initializing GStreamer..." << endl;
    gst_init(&argc, &argv);

    // Setting up pipelines
    cout << "[DEBUG] Setting up pipeline1 (camera)..." << endl;
    pipeline1 = gst_parse_launch(" avfvideosrc device-index=1 !  videoconvert !  videoscale! video/x-raw! fisheye2equi !  videoconvert  !  appsink name=appsink1", NULL);

    if (!pipeline1)
    {
        cout << "[ERROR] Failed to create pipeline1." << endl;
        return -1;
    }

    cout << "[DEBUG] Setting up pipeline2 (test pattern)..." << endl;
    pipeline2 = gst_parse_launch(" avfvideosrc device-index=2 !  videoconvert !  videoscale! video/x-raw! fisheye2equi !  videoconvert  ! appsink name=appsink2", NULL);
    if (!pipeline2)
    {
        cout << "[ERROR] Failed to create pipeline2." << endl;
        return -1;
    }

    // Getting appsinks
    cout << "[DEBUG] Getting appsink1 from pipeline1..." << endl;
    appsink1 = gst_bin_get_by_name(GST_BIN(pipeline1), "appsink1");
    if (!appsink1)
    {
        cout << "[ERROR] Failed to get appsink1." << endl;
        return -1;
    }

    cout << "[DEBUG] Getting appsink2 from pipeline2..." << endl;
    appsink2 = gst_bin_get_by_name(GST_BIN(pipeline2), "appsink2");
    if (!appsink2)
    {
        cout << "[ERROR] Failed to get appsink2." << endl;
        return -1;
    }

    // Starting pipelines
    cout << "[DEBUG] Setting pipeline1 to PLAYING state..." << endl;
    GstStateChangeReturn ret1;
    ret1 = gst_element_set_state(pipeline1, GST_STATE_PLAYING);
    if (ret1 == GST_STATE_CHANGE_FAILURE)
    {
        cout << "[ERROR] Failed to start pipeline1 (camera)." << endl;
    }
    else
    {
        cout << "[DEBUG] Pipeline1 set to PLAYING state successfully." << endl;
    }
    cout << "[DEBUG] Setting pipeline2 to PLAYING state..." << endl;
    gst_element_set_state(pipeline2, GST_STATE_PLAYING);

    namedWindow("Concatenated Output", WINDOW_AUTOSIZE);

    // Main loop for extracting frames and displaying
    cout << "[DEBUG] Starting main loop..." << endl;
    while (true)
    {
        cout << "[DEBUG] Extracting frame1..." << endl;
        extract_frame(appsink1, frame1);
        cout << "[DEBUG] Extracting frame2..." << endl;
        extract_frame(appsink2, frame2);

        if (!frame1.empty() && !frame2.empty())
        {
            cout << "[DEBUG] Concatenating frames..." << endl;
            hconcat(frame1, frame2, concatenatedFrame);

            cout << "[DEBUG] Displaying concatenated frame..." << endl;
            imshow("Concatenated Output", concatenatedFrame);

            if (waitKey(10) == 'q')
            {
                cout << "[DEBUG] 'q' pressed, exiting loop." << endl;
                break;
            }
        }
        else
        {
            if (frame1.empty())
                cout << "[ERROR] Frame1 is empty." << endl;
            if (frame2.empty())
                cout << "[ERROR] Frame2 is empty." << endl;
        }
    }

    // Cleanup
    cout << "[DEBUG] Stopping pipelines and cleaning up..." << endl;
    gst_element_set_state(pipeline1, GST_STATE_NULL);
    gst_element_set_state(pipeline2, GST_STATE_NULL);
    gst_object_unref(pipeline1);
    gst_object_unref(pipeline2);
    destroyAllWindows();

    cout << "[DEBUG] Program finished." << endl;

    return 0;
}
