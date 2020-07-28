#include "../inc/uchat.h"

void icon_entr_set(t_main *m) {
    GdkPixbuf *pix;
    GdkPixbuf *pix1;
    GdkPixbuf *pix2;
    GdkPixbuf *pix3;

    pix = gdk_pixbuf_new_from_file(MX_ICON_ENTRY_PR(m->style->color), NULL);
    pix = gdk_pixbuf_scale_simple(pix, 50, 50, GDK_INTERP_BILINEAR);
    pix1 = gdk_pixbuf_new_from_file(MX_ICON_ENTRY_SEC(m->style->color), NULL);
    pix1 = gdk_pixbuf_scale_simple(pix1, 50, 50, GDK_INTERP_BILINEAR);
    gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(m->sms), 
        GTK_ENTRY_ICON_PRIMARY, pix);
    gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(m->sms), 
        GTK_ENTRY_ICON_SECONDARY, pix1);
    gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(m->edit_entry), 
        GTK_ENTRY_ICON_SECONDARY, pix1);

    pix2 = gdk_pixbuf_new_from_file(MX_ICON_ENTRY_LOOP(m->style->color), NULL);
    pix2 = gdk_pixbuf_scale_simple(pix2, 50, 50, GDK_INTERP_BILINEAR);
    pix3 = gdk_pixbuf_new_from_file(MX_ICON_ENTRY_CANS(m->style->color), NULL);
    pix3 = gdk_pixbuf_scale_simple(pix3, 50, 50, GDK_INTERP_BILINEAR);
    gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(m->search), 
        GTK_ENTRY_ICON_PRIMARY, pix2);
    gtk_entry_set_icon_from_pixbuf(GTK_ENTRY(m->search), 
        GTK_ENTRY_ICON_SECONDARY, pix3);
}
