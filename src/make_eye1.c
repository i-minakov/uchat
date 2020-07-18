#include "uchat.h"

void make_vis1(GtkEntry            *entry,
               GtkEntryIconPosition icon_pos,
               GdkEvent            *event,
               t_eye *eye) {	   
	if (eye->sig == false) {
		eye->sig = true;
		gtk_entry_set_visibility (GTK_ENTRY(entry), TRUE);
	}
	else {
		eye->sig = false;
		gtk_entry_set_visibility (GTK_ENTRY(entry), FALSE);
	}
}
