#include <stdio.h>
#include <gio/gio.h>

// vim: set sw=4 ts=4 noet:

int main(void) {
	GList* glist = g_app_info_get_all();
	for (GList *l = glist; l != NULL; l = l->next) {
		GAppInfo *app = G_APP_INFO(l->data);
		const char *name = g_app_info_get_name(app);
		printf("%s\n", name);
	}
	g_list_free(glist);
    return 0;
}
