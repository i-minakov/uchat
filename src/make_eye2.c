#include "uchat.h"

void make_vis2(GtkEntry            *entry,
               GtkEntryIconPosition icon_pos,
               GdkEvent            *event,
               t_eye *eye) {	   
	if (eye->sig2 == false) {
		eye->sig2 = true;
		gtk_entry_set_visibility (GTK_ENTRY(entry), TRUE);
	}
	else {
		eye->sig2 = false;
		gtk_entry_set_visibility (GTK_ENTRY(entry), FALSE);
	}
}
