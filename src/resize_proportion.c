#include "uchat.h"

static void s_bigger_w(guint width, guint heigh, t_size *s) {
	if (heigh > s->h) {
			while(heigh > s->h && width > s->w) {
				s->h++;
				s->w = s->h / (s->ys/s->xs);
			}
		}
		else {
			while(heigh != s->h) {
				s->h--;
                s->w = s->h / (s->ys/s->xs);
			}
		}
}

static void S_bigger(guint width, guint heigh, t_size *s) {
	if (width > s->w) {
		s_bigger_w(width, heigh, s);
	}
	else {
		if (heigh > s->h) {
			while(width < s->w) {
				s->h--;
				s->w = s->h / (s->ys/s->xs);
            }
		}
	}
}

static void S_less(guint width, guint heigh, t_size *s) {
	if (width > s->w) {
			while(heigh < s->h) {
                s->h--;
                s->w = s->h / (s->ys/s->xs);
			}
		}
	else {
		while(heigh < s->h || width < s->w) {
				s->h--;
				s->w = s->h / (s->ys/s->xs);
		}
	}
}

static void get_size(guint width, guint heigh, t_size *s) {
	s->w = s->xs;
	s->h = s->ys;

	if(width*heigh >= s->h*s->w)
		S_bigger(width, heigh, s);
	else 
		S_less(width, heigh, s);
	s->x = (width - s->w)/2;
	s->y = (heigh - s->h)/2;
}

GtkWidget *resize_proportion(const char *path_to_image, int xs, int ys) {
    GtkWidget *img;
    GdkPixbuf *pix;
	t_size *s = (t_size *)malloc(sizeof(t_size) * 6);
    s->xs = xs;
    s->ys = ys;

	pix = gdk_pixbuf_new_from_file(path_to_image, NULL);
	if (pix != NULL) {
		get_size(gdk_pixbuf_get_width(pix), gdk_pixbuf_get_height(pix), s);
		pix = gdk_pixbuf_new_subpixbuf (pix, s->x, s->y, s->w, s->h);
		pix = gdk_pixbuf_scale_simple(pix, xs, ys, GDK_INTERP_BILINEAR);						
		img = gtk_image_new_from_pixbuf(pix);
		free(s);
		return img;
	}
	free(s);
	return NULL;
}
