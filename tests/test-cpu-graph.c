#include "rg-graph.h"
#include "rg-cpu-graph.h"
#include "rg-line-renderer.h"
#include "rg-step-renderer.h"
#include "rg-straight-renderer.h"

#include <stdlib.h>

#define CSS_DATA \
  "RgGraph {\n" \
  "  background-color: #f6f7f8;\n" \
  "  background-size: 8px 8px;\n" \
  "  background-image:repeating-linear-gradient(0deg, #f0f1f2, #f0f1f2 1px, transparent 1px, transparent 8px),repeating-linear-gradient(-90deg, #f0f1f2, #f0f1f2 1px, transparent 1px, transparent 8px);\n" \
  "}"

int
main (int argc,
      char *argv[])
{
  guint samples = 1;
  guint seconds = 60;
  guint runfor = 60;
  const GOptionEntry entries[] = {
    { "samples", 'm', 0, G_OPTION_ARG_INT, &samples, "Number of samples per second", "2" },
    { "seconds", 's', 0, G_OPTION_ARG_INT, &seconds, "Number of seconds to display", "60" },
    { "run-for", 'r', 0, G_OPTION_ARG_INT, &runfor, "Number of seconds to run", "60" },
    { NULL }
  };
  gint64 timespan;
  guint max_samples;
  GOptionContext *context;
  GtkWindow *window;
  GtkBox *box;
  RgGraph *graph;
  GtkCssProvider *provider;
  GError *error = NULL;

  context = g_option_context_new ("- a simple cpu graph");
  g_option_context_add_group (context, gtk_get_option_group (TRUE));
  g_option_context_add_main_entries (context, entries, NULL);

  if (!g_option_context_parse (context, &argc, &argv, &error))
    {
      g_printerr ("%s\n", error->message);
      return EXIT_FAILURE;
    }

  g_print ("%d samples per second over %d seconds running for %d seconds.\n",
           samples, seconds, runfor);

  timespan = (gint64)seconds * G_USEC_PER_SEC;
  max_samples = seconds * samples;

  provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_data (provider, CSS_DATA, -1, NULL);
  gtk_style_context_add_provider_for_screen (gdk_screen_get_default (), GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref (provider);

  window = g_object_new (GTK_TYPE_WINDOW,
                         "default-width", 1200,
                         "default-height", 650,
                         "title", "CPU Graph",
                         NULL);

  box = g_object_new (GTK_TYPE_BOX,
                      "orientation", GTK_ORIENTATION_VERTICAL,
                      "visible", TRUE,
                      "spacing", 3,
                      NULL);
  gtk_container_add (GTK_CONTAINER (window), GTK_WIDGET (box));

  for (int i = 0; i < 3; i++)
    {
      graph = g_object_new (RG_TYPE_CPU_GRAPH,
                            "visible", TRUE,
                            "vexpand", TRUE,
                            "timespan", timespan,
                            "max-samples", max_samples,
                            "renderer", (i%3==0)?RG_TYPE_LINE_RENDERER:(i%3==1)?RG_TYPE_STEP_RENDERER:RG_TYPE_STRAIGHT_RENDERER,
                            NULL);
      gtk_container_add (GTK_CONTAINER (box), GTK_WIDGET (graph));
    }

  g_signal_connect (window, "delete-event", gtk_main_quit, NULL);
  g_timeout_add_seconds (60, (GSourceFunc)gtk_main_quit, NULL);
  gtk_window_present (window);
  gtk_main ();

  return 0;
}
