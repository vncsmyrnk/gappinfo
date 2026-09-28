#include <stdio.h>
#include <gio/gio.h>

// vim: set sw=4 ts=4 noet:

int main(int argc, char *argv[]) {
	gboolean rofi = FALSE;

	GOptionEntry entries[] = {
		{ "rofi", 'r', 0, G_OPTION_ARG_NONE, &rofi, "Output in a rofi-friendly format", NULL },
		{ NULL }
	};

	GOptionContext *context = g_option_context_new("- List all available applications via GNOME's GLib");
    g_option_context_add_main_entries(context, entries, NULL);

	g_autoptr(GError) error = NULL;
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
        g_printerr("Error parsing flags: %s\n", error->message);
        g_option_context_free(context);
        return 1;
    }

	GList* glist = g_app_info_get_all();
	for (GList *l = glist; l != NULL; l = l->next) {
		GAppInfo *app = G_APP_INFO(l->data);
		const char *name = g_app_info_get_name(app);
		if (rofi) {
			printf("%s\n", name);
		} else {
			const char *id = g_app_info_get_id(app);
			fputs(id, stdout);
			fputc('\0', stdout);
			GIcon *icon = g_app_info_get_icon(app);
			if (icon != NULL) {
				const char *icon_str = g_icon_to_string(icon);
				printf("display\x1f%s\x1ficon\x1f%s\x1fmeta\x1f%s\n", name, icon_str, name);
			} else {
				printf("display\x1f%s\x1fmeta\x1f%s\n", name, name);
			}
		}
	}

	g_list_free(glist);
    return 0;
}
