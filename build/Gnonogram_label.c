/* Gnonogram_label.c generated by valac 0.11.6, the Vala compiler
 * generated from Gnonogram_label.vala, do not modify */

/*  Copyright (C) 2010-2011  Jeremy Wootten
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
 *
 * As a special exception, if you use inline functions from this file, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU Lesser General Public License.
 * 
 *  Author:
 * 	Jeremy Wootten <jeremwootten@gmail.com>
 */

#include <glib.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>


#define TYPE_GNONOGRAM_LABEL (gnonogram_label_get_type ())
#define GNONOGRAM_LABEL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_GNONOGRAM_LABEL, Gnonogram_label))
#define GNONOGRAM_LABEL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_GNONOGRAM_LABEL, Gnonogram_labelClass))
#define IS_GNONOGRAM_LABEL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_GNONOGRAM_LABEL))
#define IS_GNONOGRAM_LABEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), TYPE_GNONOGRAM_LABEL))
#define GNONOGRAM_LABEL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), TYPE_GNONOGRAM_LABEL, Gnonogram_labelClass))

typedef struct _Gnonogram_label Gnonogram_label;
typedef struct _Gnonogram_labelClass Gnonogram_labelClass;
typedef struct _Gnonogram_labelPrivate Gnonogram_labelPrivate;
#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))

struct _Gnonogram_label {
	GtkEventBox parent_instance;
	Gnonogram_labelPrivate * priv;
};

struct _Gnonogram_labelClass {
	GtkEventBoxClass parent_class;
};

struct _Gnonogram_labelPrivate {
	GtkLabel* l;
};


static gpointer gnonogram_label_parent_class = NULL;

GType gnonogram_label_get_type (void) G_GNUC_CONST;
#define GNONOGRAM_LABEL_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE ((o), TYPE_GNONOGRAM_LABEL, Gnonogram_labelPrivate))
enum  {
	GNONOGRAM_LABEL_DUMMY_PROPERTY
};
Gnonogram_label* gnonogram_label_new (const gchar* label_text, gboolean is_column);
Gnonogram_label* gnonogram_label_construct (GType object_type, const gchar* label_text, gboolean is_column);
void gnonogram_label_highlight (Gnonogram_label* self, gboolean is_highlight);
void gnonogram_label_set_markup (Gnonogram_label* self, const gchar* m);
gchar* gnonogram_label_get_text (Gnonogram_label* self);
static void gnonogram_label_finalize (GObject* obj);


Gnonogram_label* gnonogram_label_construct (GType object_type, const gchar* label_text, gboolean is_column) {
	Gnonogram_label * self = NULL;
	GtkLabel* _tmp0_ = NULL;
	GtkLabel* _tmp1_;
	g_return_val_if_fail (label_text != NULL, NULL);
	self = (Gnonogram_label*) g_object_new (object_type, NULL);
	_tmp0_ = (GtkLabel*) gtk_label_new (label_text);
	_tmp1_ = g_object_ref_sink (_tmp0_);
	_g_object_unref0 (self->priv->l);
	self->priv->l = _tmp1_;
	if (is_column) {
		gtk_label_set_angle (self->priv->l, (gdouble) 270);
		gtk_misc_set_alignment (GTK_MISC (self->priv->l), (gfloat) 0.0, (gfloat) 1.0);
		gtk_misc_set_padding (GTK_MISC (self->priv->l), 0, 5);
	} else {
		gtk_misc_set_alignment (GTK_MISC (self->priv->l), (gfloat) 1.0, (gfloat) 1.0);
		gtk_misc_set_padding (GTK_MISC (self->priv->l), 5, 0);
	}
	gtk_container_add (GTK_CONTAINER (self), GTK_WIDGET (self->priv->l));
	return self;
}


Gnonogram_label* gnonogram_label_new (const gchar* label_text, gboolean is_column) {
	return gnonogram_label_construct (TYPE_GNONOGRAM_LABEL, label_text, is_column);
}


void gnonogram_label_highlight (Gnonogram_label* self, gboolean is_highlight) {
	g_return_if_fail (IS_GNONOGRAM_LABEL (self));
	if (is_highlight) {
		gtk_widget_set_state (GTK_WIDGET (self), GTK_STATE_SELECTED);
	} else {
		gtk_widget_set_state (GTK_WIDGET (self), GTK_STATE_NORMAL);
	}
}


void gnonogram_label_set_markup (Gnonogram_label* self, const gchar* m) {
	g_return_if_fail (IS_GNONOGRAM_LABEL (self));
	g_return_if_fail (m != NULL);
	gtk_label_set_markup (self->priv->l, m);
}


gchar* gnonogram_label_get_text (Gnonogram_label* self) {
	gchar* result = NULL;
	const gchar* _tmp0_ = NULL;
	gchar* _tmp1_;
	g_return_val_if_fail (IS_GNONOGRAM_LABEL (self), NULL);
	_tmp0_ = gtk_label_get_text (self->priv->l);
	_tmp1_ = g_strdup (_tmp0_);
	result = _tmp1_;
	return result;
}


static void gnonogram_label_class_init (Gnonogram_labelClass * klass) {
	gnonogram_label_parent_class = g_type_class_peek_parent (klass);
	g_type_class_add_private (klass, sizeof (Gnonogram_labelPrivate));
	G_OBJECT_CLASS (klass)->finalize = gnonogram_label_finalize;
}


static void gnonogram_label_instance_init (Gnonogram_label * self) {
	self->priv = GNONOGRAM_LABEL_GET_PRIVATE (self);
}


static void gnonogram_label_finalize (GObject* obj) {
	Gnonogram_label * self;
	self = GNONOGRAM_LABEL (obj);
	_g_object_unref0 (self->priv->l);
	G_OBJECT_CLASS (gnonogram_label_parent_class)->finalize (obj);
}


GType gnonogram_label_get_type (void) {
	static volatile gsize gnonogram_label_type_id__volatile = 0;
	if (g_once_init_enter (&gnonogram_label_type_id__volatile)) {
		static const GTypeInfo g_define_type_info = { sizeof (Gnonogram_labelClass), (GBaseInitFunc) NULL, (GBaseFinalizeFunc) NULL, (GClassInitFunc) gnonogram_label_class_init, (GClassFinalizeFunc) NULL, NULL, sizeof (Gnonogram_label), 0, (GInstanceInitFunc) gnonogram_label_instance_init, NULL };
		GType gnonogram_label_type_id;
		gnonogram_label_type_id = g_type_register_static (GTK_TYPE_EVENT_BOX, "Gnonogram_label", &g_define_type_info, 0);
		g_once_init_leave (&gnonogram_label_type_id__volatile, gnonogram_label_type_id);
	}
	return gnonogram_label_type_id__volatile;
}



