#include "../inc/uchat.h"

GtkWidget *resize_image(const char *path_to_image, guint width, guint heigh) {
    GtkWidget *img;
    GdkPixbuf *pix;

    pix = gdk_pixbuf_new_from_file(path_to_image, NULL);
    pix = gdk_pixbuf_scale_simple(pix, width, heigh, GDK_INTERP_BILINEAR);
    img = gtk_image_new_from_pixbuf(pix);
    return img;
}
