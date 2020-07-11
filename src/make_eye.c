#include "../inc/uchat.h"

void make_vis(GtkEntry            *entry,
               GtkEntryIconPosition icon_pos,
               GdkEvent            *event,
               t_eye *eye) {	   
	if (eye->log == false) {
		eye->log = true;
		gtk_entry_set_visibility (GTK_ENTRY(entry), TRUE);
	}
	else {
		eye->log = false;
		gtk_entry_set_visibility (GTK_ENTRY(entry), FALSE);
	}
}
