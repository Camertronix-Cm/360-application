#include <gst/gst.h>
#include <gst/video/video.h>
#include <cairo/cairo.h>
#include <cairo/cairo-gobject.h>
#include <gtk/gtk.h>
#include <ctime>

class AppData {
public:
    GstElement *pipeline;
    GstElement *sink;
    GtkWidget *drawing_area;

    AppData() : pipeline(nullptr), sink(nullptr), drawing_area(nullptr) {}
};

static gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    // Get the current time
    time_t now = time(nullptr);
    struct tm *tm_info = localtime(&now);
    char time_string[9];  // Format: HH:MM:SS
    strftime(time_string, sizeof(time_string), "%H:%M:%S", tm_info);

    // Draw the background
    cairo_set_source_rgb(cr, 0, 0, 0);  // Black background
    cairo_paint(cr);

    // Draw the clock text
    cairo_set_source_rgb(cr, 1, 1, 1);  // White text
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 48);
    cairo_move_to(cr, 100, 100);
    cairo_show_text(cr, time_string);

    return FALSE;
}

static void start_pipeline(AppData *app_data) {
    app_data->pipeline = gst_pipeline_new("clock-pipeline");
    app_data->sink = gst_element_factory_make("ximagesink", "sink");

    // Create a test video source
    GstElement *source = gst_element_factory_make("videotestsrc", "source");
    g_object_set(source, "pattern", 0, NULL);  // Solid color

    gst_bin_add_many(GST_BIN(app_data->pipeline), source, app_data->sink, NULL);
    gst_element_link(source, app_data->sink);

    gst_element_set_state(app_data->pipeline, GST_STATE_PLAYING);
}

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);
    gtk_init(&argc, &argv);

    AppData app_data;
    GtkWidget *window;

    // Create a GTK window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Clock Overlay");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a drawing area
    app_data.drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), app_data.drawing_area);
    g_signal_connect(app_data.drawing_area, "draw", G_CALLBACK(on_draw), NULL);

    start_pipeline(&app_data);

    // Update the clock every second
    g_timeout_add(1000, (GSourceFunc)gtk_widget_queue_draw, app_data.drawing_area);

    gtk_widget_show_all(window);
    gtk_main();

    gst_element_set_state(app_data.pipeline, GST_STATE_NULL);
    gst_object_unref(app_data.pipeline);

    return 0;
}
