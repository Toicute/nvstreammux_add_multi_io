#include "pipeline_nvstreammux.h"
#include "gst/gst.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>


void pipeline_nvstreammux::PipelineNvstreammux(int argc, char *argv[])
{
    dataNvstreammux.loop = g_main_loop_new(NULL, FALSE);
    if (argc < 3) {
    g_printerr ("Usage: %s <uri1> <commandline> \n", argv[0]);
    }
    dataNvstreammux.num_sources = argc - 1;
    char *command_line =  argv[argc-1];
    printf("day la argc la %d \n", argc);

    // if (strcmp( command_line, "start") == 0){

    gst_init(&argc, &argv);
    g_mutex_init (&dataNvstreammux.eos_lock);

    dataNvstreammux.pipeline = gst_pipeline_new("add_remove_stream");
    dataNvstreammux.streammux = gst_element_factory_make("nvstreammux", "streammux");
    g_object_set(dataNvstreammux.streammux, "width", 1280,
                                "height", 720,
                                "batch-size", 4, 
                                NULL);
    if (!dataNvstreammux.pipeline || !dataNvstreammux.streammux){
        g_printerr("Khong khoi tao duoc element \n");
    }

    gst_bin_add(GST_BIN(dataNvstreammux.pipeline), dataNvstreammux.streammux);
    // g_object_set(streammux, "live-source", 1, NULL);

    dataNvstreammux.g_source_bin_list = static_cast<GstElement**>(g_malloc0(sizeof (GstElement *) * MAX_NUM_SOURCES));
    dataNvstreammux.uri = g_strdup (argv[1]);
    for (dataNvstreammux.i = 0; dataNvstreammux.i < dataNvstreammux.num_sources-1; dataNvstreammux.i++) {
        
        g_printerr("Day la i trong main %d \n", dataNvstreammux.i);
        // GstElement *source_bin = create_uridecode_bin (dataNvstreammux.i, argv[dataNvstreammux.i + 1]);
        // if (!source_bin) {
        // g_printerr ("Failed to create source bin. Exiting.\n");
        // }
        // dataNvstreammux.g_source_bin_list[dataNvstreammux.i] = source_bin;
        // gst_bin_add (GST_BIN (dataNvstreammux.pipeline), source_bin);
        add_sources(&dataNvstreammux);
    }

    dataNvstreammux.g_num_sources = dataNvstreammux.num_sources;
    dataNvstreammux.tiler = gst_element_factory_make ("nvmultistreamtiler", "tiler");
    dataNvstreammux.sink = gst_element_factory_make("nveglglessink", "sink");

    if (!dataNvstreammux.tiler || !dataNvstreammux.sink){
        g_printerr("Khong khoi tao duoc element \n");
    }
    g_object_set (G_OBJECT (dataNvstreammux.tiler), "rows", 2, "columns", 2,
        "width", 400, "height", 300, NULL);

    gst_bin_add_many (GST_BIN (dataNvstreammux.pipeline), dataNvstreammux.tiler, dataNvstreammux.sink, NULL);

    if (!gst_element_link_many (dataNvstreammux.streammux, dataNvstreammux.tiler, dataNvstreammux.sink, NULL)) {
        g_printerr ("Elements could not be linked.\n");
        gst_object_unref (dataNvstreammux.pipeline);
    }
    g_print ("Now playing: %s\n", argv[1]);
    if (gst_element_set_state (dataNvstreammux.pipeline,
            GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        g_printerr ("Failed to set pipeline to playing. Exiting.\n");
    }
    //GST_DEBUG_BIN_TO_DOT_FILE_WITH_TS (GST_BIN (pipeline), GST_DEBUG_GRAPH_SHOW_ALL, "ds-app-playing");

    /* Wait till pipeline encounters an error or EOS */
    g_print ("Running...\n");
    // add_sources((gpointer) dataNvstreammux.g_source_bin_list);
    g_main_loop_run (dataNvstreammux.loop);


    g_print ("Returned, stopping playback\n");
    gst_element_set_state (dataNvstreammux.pipeline, GST_STATE_NULL);
    g_print ("Deleting pipeline\n");
    gst_object_unref (GST_BIN (dataNvstreammux.pipeline));
    g_main_loop_unref (dataNvstreammux.loop);
    g_free (dataNvstreammux.g_source_bin_list);
    g_free (dataNvstreammux.uri);
    g_mutex_clear (&dataNvstreammux.eos_lock);
}

void pipeline_nvstreammux::stop_release_source (gint source_id)
{
// GstStateChangeReturn state_return;
// gchar pad_name[16];
// GstPad *sinkpad = NULL;
// state_return =
//     gst_element_set_state (g_source_bin_list[source_id], GST_STATE_NULL);
// switch (state_return) {
// case GST_STATE_CHANGE_SUCCESS:
//     g_print ("STATE CHANGE SUCCESS\n\n");
//     g_snprintf (pad_name, 15, "sink_%u", source_id);
//     sinkpad = gst_element_get_static_pad (streammux, pad_name);
//     gst_pad_send_event (sinkpad, gst_event_new_flush_stop (FALSE));
//     gst_element_release_request_pad (streammux, sinkpad);
//     g_print ("STATE CHANGE SUCCESS %p\n\n", sinkpad);
//     gst_object_unref (sinkpad);
//     gst_bin_remove (GST_BIN (pipeline), g_source_bin_list[source_id]);
//     source_id--;
//     g_num_sources--;
//     break;
// case GST_STATE_CHANGE_FAILURE:
//     g_print ("STATE CHANGE FAILURE\n\n");
//     break;
// case GST_STATE_CHANGE_ASYNC:
//     g_print ("STATE CHANGE ASYNC\n\n");
//     g_snprintf (pad_name, 15, "sink_%u", source_id);
//     sinkpad = gst_element_get_static_pad (streammux, pad_name);
//     gst_pad_send_event (sinkpad, gst_event_new_flush_stop (FALSE));
//     gst_element_release_request_pad (streammux, sinkpad);
//     g_print ("STATE CHANGE ASYNC %p\n\n", sinkpad);int strncmp(const char *s1, const char *s2, size_t n); not only compares for equality, it also check for order. So it needs at least 3 different return values.
//     gst_object_unref (sinkpad);
//     gst_bin_remove (GST_BIN (pipeline), g_source_bin_list[source_id]);
//     source_id--;
//     g_num_sources--;
//     break;
// case GST_STATE_CHANGE_NO_PREROLL:
//     g_print ("STATE CHANGE NO PREROLL\n\n");
//     break;
// default:
//     break;
//   }
}

void pipeline_nvstreammux::cb_newpad (GstElement * decodebin, GstPad * pad, gpointer data){
    std::cout <<__LINE__<<" "<< __PRETTY_FUNCTION__<< std::endl;
    GstCaps *caps = gst_pad_query_caps (pad, NULL);
    const GstStructure *str = gst_caps_get_structure (caps, 0);
    const gchar *name = gst_structure_get_name (str);
    std::pair<int, CustomData*> *merge_source_id = static_cast<std::pair<int, CustomData*> *> (data);
    gint source_id_data = merge_source_id->first;
    std::cout << __LINE__ <<" "<< merge_source_id->first <<std::endl;
    g_print ("decodebin new pad %s\n", name);
    if (!strncmp (name, "video", 5)) {
        g_printerr("Day la source id cb_newpad %u \n", merge_source_id->first);
        gint source_id = 1;
        gchar pad_name[16] = { 0 };
        GstPad *sinkpad = NULL;
        g_snprintf (pad_name, 15, "sink_%u", source_id);
        g_printerr("Day la source id cb_newpad cho streammux %u \n", source_id);
        sinkpad = gst_element_get_request_pad (merge_source_id->second->streammux, pad_name);
        if (gst_pad_link (pad, sinkpad) != GST_PAD_LINK_OK) {
        g_print ("Failed to link decodebin to pipeline\n");
        } else {
        g_print ("Decodebin linked to pipeline\n");
        }
        gst_object_unref (sinkpad);
    }else{
        g_print ("decodebin new pad %s not video, pass this \n ", name);
    }
}


GstElement *pipeline_nvstreammux::create_uridecode_bin (guint index, gchar * filename){
    g_printerr("Day la index trong URIdecodebin %d \n", index);
    GstElement *bin = NULL;
    gchar bin_name[16] = { };
    // dataNvstreammux newdata;
    g_print ("creating uridecodebin for [%s]\n", filename);
    dataNvstreammux.g_source_id_list[index] = index;
    g_snprintf (bin_name, 15, "source-bin-%02d", index);
    bin = gst_element_factory_make ("uridecodebin", bin_name);
    g_object_set (G_OBJECT (bin), "uri", filename, NULL);
    std::pair<int, CustomData*> mergeData(3, &dataNvstreammux);
    g_printerr("Day la first value mergeData %d \n", mergeData.first);
    g_signal_connect (G_OBJECT (bin), "pad-added",
        G_CALLBACK (cb_newpad), &mergeData);
    // g_signal_connect (G_OBJECT (bin), "child-added",
    //     G_CALLBACK (decodebin_child_added), &g_source_id_list[index]);
    dataNvstreammux.g_source_enabled[index] = TRUE;
    return bin;
}

gboolean pipeline_nvstreammux::delete_sources (gpointer data){
    gint source_id;
    CustomData *dataNvstreammux = (CustomData *)data;
    g_mutex_lock (&dataNvstreammux->eos_lock);
    for (source_id = 0; source_id < MAX_NUM_SOURCES; source_id++) {
        if (dataNvstreammux->g_eos_list[source_id] == TRUE && dataNvstreammux->g_source_enabled[source_id] == TRUE) {
        dataNvstreammux->g_source_enabled[source_id] = FALSE;
        stop_release_source (source_id);
        }
    }
    g_mutex_unlock (&dataNvstreammux->eos_lock);

    if (dataNvstreammux->g_num_sources == 0) {
        g_main_loop_quit (dataNvstreammux->loop);
        g_print ("All sources Stopped quitting\n");
        return FALSE;
    }

    do {
        source_id = rand () % MAX_NUM_SOURCES;
    } while (!dataNvstreammux->g_source_enabled[source_id]);
    dataNvstreammux->g_source_enabled[source_id] = FALSE;
    g_print ("Calling Stop %d \n", source_id);
    stop_release_source (source_id);

    if (dataNvstreammux->g_num_sources == 0) {
        g_main_loop_quit (dataNvstreammux->loop);
        g_print ("All sources Stopped quitting\n");
        return FALSE;
  }

  return TRUE;
}

gboolean pipeline_nvstreammux::add_sources (gpointer data){
    GstElement *source_bin;
    GstStateChangeReturn state_return;
    CustomData *dataNvstreammux = (CustomData *)data;
    gint source_id_data = dataNvstreammux->g_num_sources;
    g_printerr("Source id in add_sources %d \n", source_id_data);
    do {
        source_id_data = rand () % MAX_NUM_SOURCES;
    } while (dataNvstreammux->g_source_enabled[source_id_data]);
    dataNvstreammux->g_source_enabled[source_id_data] = TRUE;

    g_print ("Calling Start %d \n", source_id_data);
    source_bin = create_uridecode_bin (source_id_data, dataNvstreammux->uri);
    g_print ("Da tao xong source bin \n");
    if (!source_bin) {
        g_printerr ("Failed to create source bin. Exiting.\n");
    }
    dataNvstreammux->g_source_bin_list[source_id_data] = source_bin;
    gst_bin_add (GST_BIN (dataNvstreammux->pipeline), source_bin);
    // state_return =
    //     gst_element_set_state (dataNvstreammux->g_source_bin_list[dataNvstreammux->source_id_data], GST_STATE_PLAYING);
    // switch (state_return) {
    //     case GST_STATE_CHANGE_SUCCESS:
    //     g_print ("STATE CHANGE SUCCESS\n\n");
    //     dataNvstreammux->source_id_data++;
    //     break;
    //     case GST_STATE_CHANGE_FAILURE:
    //     g_print ("STATE CHANGE FAILURE\n\n");
    //     break;
    //     case GST_STATE_CHANGE_ASYNC:
    //     g_print ("STATE CHANGE ASYNC\n\n");
    //     state_return =
    //         gst_element_get_state (dataNvstreammux->g_source_bin_list[dataNvstreammux->source_id_data], NULL, NULL,
    //         GST_CLOCK_TIME_NONE);
    //     dataNvstreammux->source_id_data++;
    //     break;
    //     case GST_STATE_CHANGE_NO_PREROLL:
    //     g_print ("STATE CHANGE NO PREROLL\n\n");
    //     break;
    //     default:
    //     break;
    // }
    dataNvstreammux->g_num_sources++;


    if (dataNvstreammux->g_num_sources == MAX_NUM_SOURCES) {
        g_printerr("Da day source, xoa source de them moi \n");
        // g_timeout_add_seconds (20, delete_sources, (gpointer) g_source_bin_list);

        return FALSE;
        
    }

    return TRUE;
}
void pipeline_nvstreammux::OnAddStream(QString source){

}

void pipeline_nvstreammux::OnRemoveStream(QString source){
    
}