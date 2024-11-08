#include <gst/gst.h>
#include <opencv2/opencv.hpp>
#include <gst/app/gstappsrc.h>
#include <gst/app/gstappsink.h>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

GstElement *pipeline1, *pipeline2, *appsink1, *appsink2;
Mat frame1, frame2, concatenatedFrame;

void extract_frame(GstElement *appsink, Mat &frame)
{
    GstSample *sample;
    GstCaps *caps;
    GstBuffer *buffer;
    GstMapInfo map;
 // Start timing here
    auto start = high_resolution_clock::now();

    cout << "[DEBUG] Trying to pull sample from appsink..." << endl;
    sample = gst_app_sink_pull_sample(GST_APP_SINK(appsink));

    if (sample)
    {
        cout << "[DEBUG] Sample pulled successfully." << endl;
        caps = gst_sample_get_caps(sample);
        if (caps)
        {
            // Print out the caps information
            gchar *caps_str = gst_caps_to_string(caps);
            cout << "[DEBUG] Frame caps: " << caps_str << endl;
            g_free(caps_str);

            GstStructure *structure = gst_caps_get_structure(caps, 0);
            int width, height;
            const gchar *format = gst_structure_get_string(structure, "format");

            // Get the width, height, and format
            gst_structure_get_int(structure, "width", &width);
            gst_structure_get_int(structure, "height", &height);
            cout << "[DEBUG] Frame size: " << width << "x" << height << ", Format: " << format << endl;

            buffer = gst_sample_get_buffer(sample);
            if (buffer)
            {
                cout << "[DEBUG] Sample buffer found. Mapping buffer..." << endl;
                gst_buffer_map(buffer, &map, GST_MAP_READ);
                cout << "[DEBUG] Buffer mapped, creating Mat..." << endl;

                // Create Mat based on the format retrieved
                if (strcmp(format, "YUY2") == 0)
                {
                    Mat temp_frame(height, width, CV_8UC2, (void *)map.data);
                    cvtColor(temp_frame, frame, COLOR_YUV2BGR_YUY2);
                }
                else if (strcmp(format, "BGR") == 0)
                {
                    frame = Mat(height, width, CV_8UC3, (void *)map.data).clone();
                }
                else if (strcmp(format, "RGBA") == 0)
                {
                    frame = Mat(height, width, CV_8UC4, (void *)map.data).clone();

                    // Optional: Convert RGBA to BGR if you need BGR output
                    // cvtColor(frame, frame, COLOR_RGBA2BGR);
                }
                else
                {
                    cout << "[ERROR] Unsupported format: " << format << endl;
                    frame = Mat(); // Empty frame
                }

                gst_buffer_unmap(buffer, &map);
                cout << "[DEBUG] Frame extracted and copied." << endl;
            }
            else
            {
                cout << "[ERROR] No buffer found in the sample." << endl;
            }
        }
        else
        {
            cout << "[ERROR] No caps found in the sample." << endl;
        }
        gst_sample_unref(sample);
    }
    else
    {
        cout << "[ERROR] Failed to pull sample from appsink." << endl;
    }
    // End timing and calculate duration
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "[DEBUG] Frame extraction time: " << duration << " ms" << endl;
}



int main(int argc, char *argv[])
{
    cout << "[DEBUG] Initializing GStreamer..." << endl;
    gst_init(&argc, &argv);

    // Setting up pipelines
    cout << "[DEBUG] Setting up pipeline1 (camera)..." << endl;
    pipeline1 = gst_parse_launch(" v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=1920,height=1080 !  nvvidconv !  videoscale !  fisheye2equi   !   appsink name=appsink1", NULL);

    if (!pipeline1)
    {
        cout << "[ERROR] Failed to create pipeline1." << endl;
        return -1;
    }

    cout << "[DEBUG] Setting up pipeline2 (test pattern)..." << endl;
    pipeline2 = gst_parse_launch(" v4l2src device=/dev/video1 ! video/x-raw,format=YUY2,width=1920,height=1080  ! nvvidconv ! videoscale! fisheye2equi   !   appsink name=appsink2", NULL);
    if (!pipeline2)
    {
        cout << "[ERROR] Failed to create pipeline2." << endl;
        return -1;
    }

    // Getting appsinks
    cout << "[DEBUG] Getting appsink1 from pipeline1..." << endl;
    appsink1 = gst_bin_get_by_name(GST_BIN(pipeline1), "appsink1");
    g_object_set(G_OBJECT(appsink1), "sync", FALSE, "max-buffers", 1, "drop", TRUE, NULL);
    if (!appsink1)
    {
        cout << "[ERROR] Failed to get appsink1." << endl;
        return -1;
    }

    cout << "[DEBUG] Getting appsink2 from pipeline2..." << endl;
    appsink2 = gst_bin_get_by_name(GST_BIN(pipeline2), "appsink2");
    g_object_set(G_OBJECT(appsink2), "sync", FALSE, "max-buffers", 1, "drop", TRUE, NULL);
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
        auto loop_start = high_resolution_clock::now();
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
          // End timing for the main loop
        auto loop_end = high_resolution_clock::now();
        auto loop_duration = duration_cast<milliseconds>(loop_end - loop_start).count();
        cout << "[DEBUG] Main loop processing time: " << loop_duration << " ms" << endl;
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
