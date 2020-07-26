#include "../inc/uchat.h"

static void s_bigger_w(guint width, guint heigh, guint *best_w, guint *best_h) {
	if (heigh > (*best_h)) {
			while(heigh > (*best_h) && width > (*best_w)) {
				(*best_h)++;
				(*best_w) = (*best_h) / 1.4;
			}
		}
		else {
			while(heigh != (*best_h)) {
				(*best_h)--;
				(*best_w) = (*best_h) / 1.4;
			}
		}
}

static void S_bigger(guint width, guint heigh, guint *best_w, guint *best_h) {
	if (width > (*best_w)) {
		s_bigger_w(width, heigh, best_w, best_h);
	}
	else {
		if (heigh > (*best_h)) {
			while(width < (*best_w)) {
				(*best_h)--;
				(*best_w) = (*best_h) / 1.4;
			}
		}
	}
}

static void S_less(guint width, guint heigh, guint *best_w, guint *best_h) {
	if (width > (*best_w)) {
			while(heigh < (*best_h)) {
					(*best_h)--;
					(*best_w) = (*best_h) / 1.4;
			}
		}
	else {
		while(heigh < (*best_h) || width < (*best_w)) {
				(*best_h)--;
				(*best_w) = (*best_h) / 1.4;
		}
	}
}

static void get_size(guint width, guint heigh, t_sizefoto *s) {
	guint best_w = 500;
	guint best_h = 700;

	if(width*heigh >= best_h*best_w)
		S_bigger(width, heigh, &best_w, &best_h);
	else 
		S_less(width, heigh, &best_w, &best_h);
	s->x = (width - best_w)/2;
	s->y = (heigh - best_h)/2;
	s->w = best_w;
	s->h = best_h;
}

GtkWidget *resize_image_correct(const char *path_to_image) {
    GtkWidget *img;
    GdkPixbuf *pix;
	t_sizefoto *s = (t_sizefoto *)malloc(sizeof(t_sizefoto) * 4);

	pix = gdk_pixbuf_new_from_file(path_to_image, NULL);
	if (pix != NULL) {
		get_size(gdk_pixbuf_get_width(pix), gdk_pixbuf_get_height(pix), s);
		pix = gdk_pixbuf_new_subpixbuf (pix, s->x, s->y, s->w, s->h);
		pix = gdk_pixbuf_scale_simple(pix, 500, 700, GDK_INTERP_BILINEAR);						
		img = gtk_image_new_from_pixbuf(pix);
		free(s);
		return img;
	}
	free(s);
	return NULL;
}
