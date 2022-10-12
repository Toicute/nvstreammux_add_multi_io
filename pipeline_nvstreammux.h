#ifndef PIPELINE_NVSTREAMMUX_H
#define PIPELINE_NVSTREAMMUX_H
#include "gst/gst.h"
#include <QObject>
#define MAX_NUM_SOURCES 4

struct CustomData{
      gint g_num_sources = 0;
      gint g_source_id_list[MAX_NUM_SOURCES];
      GstElement *streammux = NULL;
      gboolean g_eos_list[MAX_NUM_SOURCES];
      gboolean g_source_enabled[MAX_NUM_SOURCES] = {FALSE, FALSE, FALSE, FALSE};
      GstElement **g_source_bin_list = NULL;
      GMutex eos_lock;
      GstElement *pipeline = NULL, *sink = NULL, *tiler = NULL;
      gchar *uri = NULL;
      GMainLoop *loop = NULL;
      guint i, num_sources, tiler_r, tiler_c;
      
};

class pipeline_nvstreammux : public QObject
{
Q_OBJECT
public:
    void PipelineNvstreammux(int argc, char*argv[]);
    static void stop_release_source (gint source_id);
    static void cb_newpad (GstElement * decodebin, GstPad * pad, gpointer data);
    GstElement *create_uridecode_bin (guint index, gchar * filename);
    gboolean delete_sources (gpointer data);
    gboolean add_sources (gpointer data);
private:
  CustomData dataNvstreammux;

public slots:
    void OnAddStream(QString source);
    void OnRemoveStream(QString source);
};

#endif // PIPELINE_NVSTREAMMUX_H
